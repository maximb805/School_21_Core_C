#ifndef S21_3DVIEWER_H_
#define S21_3DVIEWER_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_DIGIT(ch) ((ch) >= '0' && (ch) <= '9')

typedef union {
  double s21_vertex;
  unsigned int s21_index;
} s21_value;

typedef struct s21_list {
  s21_value value;
  struct s21_list *next;
  struct s21_list *prev;
  struct s21_list *last;
} s21_list;

typedef struct {
  double **matrix;
} s21_double_matrix;

typedef struct {
  unsigned int **matrix;
} s21_uint_matrix;

int s21_get_arrays(char *filename, s21_list **vertexes,
                   size_t *vertexes_coords_read, s21_list **indexes,
                   size_t *indexes_points_read, double *min_x, double *max_x,
                   double *min_y, double *max_y, double *min_z, double *max_z);
void s21_parse_line(char *line, s21_list **vertexes,
                   size_t *vertexes_coords_read, s21_list **indexes,
                   size_t *indexes_points_read, double *min_x, double *max_x,
                   double *min_y, double *max_y, double *min_z, double *max_z);
double s21_str_to_double(char *str, char **end);
double s21_get_double(const char *str, int *pos);
void s21_parse_v_line(char *line, s21_list **vertexes,
                     size_t *vertexes_coords_read, double *min_x, double *max_x,
                     double *min_y, double *max_y, double *min_z,
                     double *max_z);
void s21_parse_f_line(char *line, s21_list **indexes,
                     size_t *indexes_points_read);
int s21_lists_to_matrixes(s21_list *vertexes_list, s21_double_matrix *vertexes,
                          s21_double_matrix *vertexes_base,
                          size_t vertexes_coords_count, s21_list *indexes_list,
                          s21_uint_matrix *indexes, size_t indexes_points_count,
                          unsigned int **indexes_array, double x_shift,
                          double y_shift, double z_shift);
void s21_fill_vertexes(s21_list *vertexes_list, s21_double_matrix *vertexes,
                       s21_double_matrix *vertexes_base, size_t vertexes_count,
                       double x_shift, double y_shift, double z_shift);
void s21_fill_indexes(s21_list *indexes_list, s21_uint_matrix *indexes,
                      unsigned int **indexes_array, size_t lines_count, size_t vertexes_count);
void s21_check_borders(double *min, double *max, double value);
double s21_get_max_range(double min_x, double max_x, double min_y, double max_y,
                         double min_z, double max_z);
void s21_calc_verts_count(unsigned int *array, size_t elems, size_t *vertexes);
void s21_sort_array(unsigned int *array, size_t left, size_t right);
size_t s21_partition(unsigned int *array, size_t left, size_t right,
                     unsigned int pivot);
void s21_manual_sort(unsigned int *array, size_t left, size_t right);
unsigned int s21_get_pivot(unsigned int *array, size_t left, size_t right);
void s21_swap(unsigned int *array, size_t A, size_t B);

void s21_sort_indexes(s21_uint_matrix *indexes, size_t left, size_t right);
size_t s21_partition_in_matrix(s21_uint_matrix *matrix, size_t left,
                               size_t right, unsigned int pivot);
void s21_manual_sort_in_matrix(s21_uint_matrix *matrix, size_t left,
                               size_t right);
unsigned int s21_get_pivot_from_matrix(s21_uint_matrix *matrix, size_t left,
                                       size_t right);
void s21_swap_in_matrix(s21_uint_matrix *matrix, size_t A, size_t B);
void s21_calc_edges_count(s21_uint_matrix indexes, size_t rows, size_t *edges);

// s21_list.c
void s21_add(s21_list **list, s21_value value);
void s21_destroy_list(s21_list *list);
s21_list *s21_create_node();
void s21_remove(s21_list **list);

// s21_affine_transformations1.c
void s21_mul_matrixes(s21_double_matrix *matrix1,
                      s21_double_matrix *base_matrix, double matrix2[4][4],
                      size_t rows);
void s21_rescale(s21_double_matrix *vertexes, s21_double_matrix *vertexes_base,
                 size_t vertexes_count, double scale, double x_angle,
                 double y_angle, double z_angle, double x_shift, double y_shift,
                 double z_shift);
void s21_move(s21_double_matrix *vertexes, size_t vertexes_count,
              double x_shift, double y_shift, double z_shift);
void s21_rotate(s21_double_matrix *vertexes, s21_double_matrix *vertexes_base,
                size_t vertexes_count, double x_angle, double y_angle,
                double z_angle, double x_shift, double y_shift, double z_shift);

#endif /* S21_3DVIEWER_H_ */
