#include "coord_map.hpp"
#include "projection.hpp"
#include <cmath>

Point3D ae2xyz(const AePoint &ae) {
  // Convert from a horizontal coordinate system in radians to a cartesian
  // system. ISO/IEC JTC1/SC29/WG11/N17197l: Algorithm descriptions of
  // projection format conversion and video quality metrics in 360Lib Version 5

  // X axis point to front, Y axis point to up and Z axis point to right.

  double x = cos(ae[0]) * cos(ae[1]);
  double y = sin(ae[1]);
  double z = -cos(ae[1]) * sin(ae[0]);
  return Point3D(x, y, z);
};

AePoint xyz2ae(const Point3D &xyz) {
  double r = std::hypot(xyz[0], xyz[1], xyz[2]);

  double elevation = asin(xyz[1] / r);
  double azimuth = atan2(-xyz[2], xyz[0]);
  return AePoint(azimuth, elevation);
};

/////////////// ERP coordinate transformations ////////////////////
PointUV erp_space::mn2uv(const PointMN &mn, const Resolution &resolution) {
  double u = (mn[0] + 0.5) / (resolution[0]);
  double v = (mn[1] + 0.5) / (resolution[1]);
  return PointUV(u, v);
};

PointMN erp_space::uv2mn(const PointUV &uv, const Resolution &resolution) {
  // PS. Isso aqui obriga a usar interopolação por vizinho mais próximo.
  ushort m = std::floor(uv[0] * resolution[0]);
  ushort n = std::floor(uv[1] * resolution[1]);

  // Clausula de guarda. Se o valor de m ou n for igual ou maior que a
  // resolução, é porque ele deu a volta no circulo. Isso nunca deve acontecer.
  // É a mesma coisa do angulo 0 e 360 serem o mesmo ponto. Os pontos são só de
  // 0 até (resolution - 1). Posteriormente a função cv::remap vai lidar com
  // isso.
  m = m >= resolution[0] ? 0 : m;
  n = n >= resolution[1] ? 0 : n;
  return PointMN(m, n);
};

AePoint erp_space::uv2ae(const PointUV &uv) {
  double a = uv[0] * (2. * PI) - PI;
  double e = uv[1] * (-PI) + PI_2;
  return AePoint(a, e);
};

PointUV erp_space::ae2uv(const AePoint &ae) {
  double u = ae[0] / (TWO_PI) + 0.5;
  double v = -ae[1] / PI + 0.5;
  return PointUV(u, v);
};
