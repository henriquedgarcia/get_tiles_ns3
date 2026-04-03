#include "types.hpp"
#include "utils.hpp"
#include <cmath>
#include <vector>

// Slerp (Spherical linear interpolation) interpolação esférica (linear) entre
// dois pontos unitários
// https://en.wikipedia.org/wiki/Spherical_linear_interpolation
Point3D slerp(const Point3D &p0, const Point3D &p1, double t) {
  double dotp =
      dot(p0, p1); // Angulo entre p0 e p1 (é o quanto andou no grande círculo)
  double theta = acos(dotp);

  // Caso especial: pontos iguais
  if (theta < 1e-8) {
    return cv::normalize(p0); // ou p1, são equivalentes
  }

  double sin_theta = sin(theta); // Para evitar divisão por zero
  double w0 = sin((1 - t) * theta) / sin_theta;
  double w1 = sin(t * theta) / sin_theta;

  Point3D result = {w0 * p0[0] + w1 * p1[0],  // x
                    w0 * p0[1] + w1 * p1[1],  // y
                    w0 * p0[2] + w1 * p1[2]}; // z
  return cv::normalize(result);
}

std::vector<Point3D> predict_future(const std::vector<Point3D> &past,
                                    int n_future,
                                    int n_window = 5) {

  // Calcula o deslocamento angular médio entre os últimos pontos
  double total_angle = 0.0;
  int count = 0;
  for (int i = past.size() - n_window; i < (int)past.size() - 1; ++i) {
    double angle = acos(dot(past[i], past[i + 1]));
    total_angle += angle;
    count++;
  }
  double mean_angle = total_angle / count;

  // Os últimos dois pontos definem a direção
  Point3D p0 = past[past.size() - 2];
  Point3D p1 = past.back();

  // Extrapolar ao longo do mesmo grande círculo
  std::vector<Point3D> future;
  for (int i = 1; i <= n_future; ++i) {
    double t = 1.0 + (i * mean_angle / acos(dot(p0, p1)));
    Point3D next = slerp(p0, p1, t);
    future.push_back(next);
  }
  return future;
}