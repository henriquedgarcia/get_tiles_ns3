#include <fstream>  // std::ofstream, std::ifstream
#include <iostream>
#include <numeric>  // std::iota
#include <sstream>  // std::stringstream
#include <vector>   // std::vector

#include "types.hpp"
#include "utils.hpp"

std::pair<double, double> linear_regression(const std::vector<double>& y) {
  int n = (int)y.size();
  std::vector<double> x(n);
  std::iota(x.begin(), x.end(), 0);

  double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
  double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
  double sum_x2 = 0.0, sum_xy = 0.0;

  for (int i = 0; i < n; ++i) {
    sum_x2 += x[i] * x[i];
    sum_xy += x[i] * y[i];
  }

  double denom = n * sum_x2 - sum_x * sum_x;
  double a = (n * sum_xy - sum_x * sum_y) / denom;
  double b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;

  return {a, b};
}

std::vector<Point3D> predict_future(const std::vector<Point3D>& data,
                                    int n_future) {
  int n_input = (int)data.size();

  // extrair cada coordenada
  std::vector<double> xs(n_input), ys(n_input), zs(n_input);
  for (int i = 0; i < n_input; ++i) {
    xs[i] = data[i].x;
    ys[i] = data[i].y;
    zs[i] = data[i].z;
  }

  // regressão linear separada
  auto [ax, bx] = linear_regression(xs);
  auto [ay, by] = linear_regression(ys);
  auto [az, bz] = linear_regression(zs);

  // prever próximos 30 pontos
  std::vector<Point3D> future;
  int start = n_input, end = n_input + n_future;

  for (int i = start; i < end; ++i) {
    double fx = ax * i + bx;
    double fy = ay * i + by;
    double fz = az * i + bz;
    future.push_back({fx, fy, fz});
  }

  return future;
}

cv::Mat linspace(const double start, const double end, const int num_points) {
  double step = (end - start) / (num_points - 1);
  cv::Mat output(1, num_points, CV_64F);
  for (int i = 0; i < num_points; ++i) {
    output.at<double>(0, i) = start + i * step;
  }
  return output;
}

cv::Mat applyRotation(const cv::Mat& input_points, const cv::Mat& mat_rot) {
  /*
  De acordo com o chat GPT, não dá pra multiplicar uma matriz por um array 3D
  diretamente, então a gente tem que "flattenar" o array, multiplicar e depois
  voltar pro formato original. O código abaixo faz isso usando OpenCV. A
  multiplicação vetorial do OpenCV é otimizada e deve ser mais rápida do que
  iterar manualmente sobre os pontos. O reshape é eficiente e não copia os
  dados, então o custo de performance deve ser baixo.
  */

  // Confere se o input é double com 3 canais e se a matriz de rotação é 3x3 do
  // tipo double (um canal)
  CV_Assert(input_points.type() == CV_64FC3);
  CV_Assert(mat_rot.rows == 3 && mat_rot.cols == 3 && mat_rot.type() == CV_64F);
  
  // Pré aloca uma matriz para os pontos rotacionados com o formato
  cv::Mat output = input_points.clone();
  
  // Converte para Nx3. "flatten", entre aspas porque cada canal vira uma coluna e cada linha passa a ter 3 colunas.
  int n_points = input_points.rows * input_points.cols;
  cv::Mat reshaped = input_points.reshape(1, n_points);  // Nx3, CV_64F

  // Multiplica todos os pontos de uma vez pela transporta da matriz de rotação
  cv::Mat rotated_flat = reshaped * mat_rot.t();  // Nx3

  // Volta para MxNx3
  output = rotated_flat.reshape(3, input_points.rows);

  return output;
}
