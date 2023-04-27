#include "s21_3Dviewer.h"

void s21_rotate(s21_double_matrix *vertexes, s21_double_matrix *vertexes_base,
                size_t vertexes_count, double x_angle, double y_angle,
                double z_angle, double x_shift, double y_shift,
                double z_shift) {
  x_angle *= -1.0;
  y_angle *= -1.0;
  z_angle *= -1.0;
  double matrix_multiplier[4][4] = {
      {cos(y_angle) * cos(z_angle), -sin(z_angle) * cos(y_angle), sin(y_angle),
       0},
      {sin(x_angle) * sin(y_angle) * cos(z_angle) + sin(z_angle) * cos(x_angle),
       -sin(x_angle) * sin(y_angle) * sin(z_angle) +
           cos(x_angle) * cos(z_angle),
       -sin(x_angle) * cos(y_angle), 0},
      {sin(x_angle) * sin(z_angle) - sin(y_angle) * cos(x_angle) * cos(z_angle),
       sin(x_angle) * cos(z_angle) + sin(y_angle) * sin(z_angle) * cos(x_angle),
       cos(x_angle) * cos(y_angle), 0},
      {0, 0, 0, 1}};
  s21_mul_matrixes(vertexes, vertexes_base, matrix_multiplier, vertexes_count);
  s21_move(vertexes, vertexes_count, x_shift, y_shift, z_shift);
}

void s21_move(s21_double_matrix *vertexes, size_t vertexes_count,
              double x_shift, double y_shift, double z_shift) {
  double matrix_multiplier[4][4] = {
      {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {x_shift, y_shift, z_shift, 1}};
  s21_mul_matrixes(vertexes, vertexes, matrix_multiplier, vertexes_count);
}

void s21_rescale(s21_double_matrix *vertexes, s21_double_matrix *vertexes_base,
                 size_t vertexes_count, double scale, double x_angle,
                 double y_angle, double z_angle, double x_shift, double y_shift,
                 double z_shift) {
  double matrix_multiplier[4][4] = {
      {scale, 0, 0, 0}, {0, scale, 0, 0}, {0, 0, scale, 0}, {0, 0, 0, 1}};
  s21_mul_matrixes(vertexes_base, vertexes_base, matrix_multiplier,
                   vertexes_count);
  s21_rotate(vertexes, vertexes_base, vertexes_count, x_angle, y_angle, z_angle,
             x_shift, y_shift, z_shift);
}

void s21_mul_matrixes(s21_double_matrix *matrix1,
                      s21_double_matrix *base_matrix, double matrix2[4][4],
                      size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    double sub_res[4] = {0};
    for (int j = 0; j < 4; j++) {
      sub_res[j] += base_matrix->matrix[i][0] * matrix2[0][j];
      sub_res[j] += base_matrix->matrix[i][1] * matrix2[1][j];
      sub_res[j] += base_matrix->matrix[i][2] * matrix2[2][j];
      sub_res[j] += 1 * matrix2[3][j];
    }
    matrix1->matrix[i][0] = sub_res[0];
    matrix1->matrix[i][1] = sub_res[1];
    matrix1->matrix[i][2] = sub_res[2];
  }
}
