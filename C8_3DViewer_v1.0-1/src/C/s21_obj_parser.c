#include "s21_3Dviewer.h"

int s21_get_arrays(char *filename, s21_list **vertexes,
                   size_t *vertexes_coords_read, s21_list **indexes,
                   size_t *indexes_points_read, double *min_x, double *max_x,
                   double *min_y, double *max_y, double *min_z, double *max_z) {
  int error_code = 0;
  size_t len = 0;
  ssize_t symbols_read = 0;
  char *line = NULL;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    *min_x = *max_x = *min_y = *max_y = *min_z = *max_z = 0.0 / 0.0;
    while ((symbols_read = getline(&line, &len, file)) > 0) {
      if (symbols_read > 2) {
        if ((line[0] == 'v' || line[0] == 'f') && line[1] == ' ') {
          s21_parse_line(line, vertexes, vertexes_coords_read, indexes,
              indexes_points_read, min_x, max_x, min_y, max_y, min_z, max_z);
        }
      }
    }
    if (line != NULL) {
      free(line);
    }
    fclose(file);
  } else {
    error_code = 2;  // no such file
  }
  return error_code;
}

void s21_parse_line(char *line, s21_list **vertexes,
                    size_t *vertexes_coords_read, s21_list **indexes,
                    size_t *indexes_points_read, double *min_x, double *max_x,
                    double *min_y, double *max_y, double *min_z, double *max_z) {
  if (line[0] == 'v') {
    s21_parse_v_line(line + 1, vertexes, vertexes_coords_read, min_x,
                     max_x, min_y, max_y, min_z, max_z);
  } else if (line[0] == 'f') {
    s21_parse_f_line(line + 1, indexes, indexes_points_read);
  }
}

void s21_parse_v_line(char *line, s21_list **vertexes,
                      size_t *vertexes_coords_read, double *min_x, double *max_x,
                      double *min_y, double *max_y, double *min_z,
                      double *max_z) {
  s21_value value;
  value.s21_vertex = 0.0;
  while (*line == ' ') {
      line++;
  }
  for(int i = 0; i < 3; i++) {
    value.s21_vertex = strtod(line, &line);
    s21_add(vertexes, value);
    if (i == 0) {
      s21_check_borders(min_x, max_x, value.s21_vertex);
    } else if (i == 1) {
      s21_check_borders(min_y, max_y, value.s21_vertex);
    } else {
      s21_check_borders(min_z, max_z, value.s21_vertex);
    }
    while (*line && *line != ' ') {
      line++;
    }
    while (*line == ' ') {
      line++;
    }
    *vertexes_coords_read = *vertexes_coords_read + 1;
  }
}

void s21_parse_f_line(char *line, s21_list **indexes,
                      size_t *indexes_points_read) {
  int got_nums = 0;
  int got_nums_total = 0;
  s21_value value;
  value.s21_index = 0;
  while (*line == ' ') {
      line++;
  }
  while (*line) {
    double tmp = strtod(line, &line);
    if (tmp < 0) {
      value.s21_index = 0;
    } else {
      value.s21_index = (unsigned int) tmp;
    }
    if (value.s21_index > 0) {
      if (got_nums == 2) {
        s21_value tmp_value;
        tmp_value = (*indexes)->value;
        s21_add(indexes, tmp_value);
        *indexes_points_read = *indexes_points_read + 1;
        got_nums = 1;
      }
      s21_add(indexes, value);
      got_nums++;
      *indexes_points_read = *indexes_points_read + 1;
      got_nums_total++;
    }
    while (*line && *line != ' ') {
      line++;
    }
    while (*line == ' ') {
      line++;
    }
  }
  if (got_nums_total == 1) {
    *indexes_points_read = *indexes_points_read + 1;
    s21_add(indexes, (*indexes)->value);
  } else if (got_nums_total > 2) {
    value = (*indexes)->value;
    s21_add(indexes, value);
    s21_list *tmp_elem = *indexes;
    for (int i = 0; i < (got_nums_total - 1) * 2; i++) {
      tmp_elem = tmp_elem->next;
    }
    value = tmp_elem->value;
    s21_add(indexes, value);
    *indexes_points_read = *indexes_points_read + 2;
  }
}

void s21_check_borders(double *min, double *max, double value) {
  if (*min != *min) {
    *min = value;
  } else if (*min > value) {
    *min = value;
  }
  if (*max != *max) {
    *max = value;
  } else if (*max < value) {
    *max = value;
  }
}

int s21_lists_to_matrixes(s21_list *vertexes_list, s21_double_matrix *vertexes,
                          s21_double_matrix *vertexes_base,
                          size_t vertexes_coords_count, s21_list *indexes_list,
                          s21_uint_matrix *indexes, size_t indexes_points_count,
                          unsigned int **indexes_array, double x_shift,
                          double y_shift, double z_shift) {
  int error_code = 0;
  size_t lines_count = indexes_points_count / 2;
  size_t vertexes_count = vertexes_coords_count / 3;
  if (vertexes_coords_count > 0 && indexes_points_count > 0) {
    vertexes->matrix = (double **) malloc(vertexes_count * sizeof(double *));
    vertexes_base->matrix = (double **) malloc(vertexes_count * sizeof(double *));
    indexes->matrix = (unsigned int **) malloc(lines_count * sizeof(unsigned int *));

    if (vertexes->matrix != NULL && vertexes_base->matrix != NULL &&
        indexes->matrix != NULL) {

        vertexes->matrix[0] = (double *) calloc(vertexes_coords_count, sizeof(double));
        vertexes_base->matrix[0] = (double *) calloc(vertexes_coords_count, sizeof(double));
        if (vertexes->matrix[0] != NULL && vertexes_base->matrix[0] != NULL) {
          for (size_t i = 1; i < vertexes_count; i++) {
            vertexes->matrix[i] = vertexes->matrix[0] + i * 3;
            vertexes_base->matrix[i] = vertexes_base->matrix[0] + i * 3;
          }
          s21_fill_vertexes(vertexes_list, vertexes, vertexes_base, vertexes_count,
                            x_shift, y_shift, z_shift);
        } else {
          if (vertexes->matrix[0] != NULL) {
            free(vertexes->matrix[0]);
          }
          if (vertexes_base->matrix[0] != NULL) {
            free(vertexes_base->matrix[0]);
          }
          free(vertexes->matrix);
          free(vertexes_base->matrix);
          error_code = 1;
        }

      if (!error_code) {
        *indexes_array = (unsigned int *) calloc(indexes_points_count, sizeof(unsigned int));
        indexes->matrix[0] = (unsigned int *) calloc(indexes_points_count, sizeof(unsigned int));
        if (indexes->matrix[0] != NULL && *indexes_array != NULL) {
          for (size_t i = 1; i < lines_count; i++) {
            indexes->matrix[i] = indexes->matrix[0] + i * 2;
          }
          s21_fill_indexes(indexes_list, indexes, indexes_array, lines_count, vertexes_count);
          s21_sort_indexes(indexes, 0, lines_count - 1);
        } else {
          if (*indexes_array != NULL) {
            free(*indexes_array);
          }
          if (indexes->matrix[0] != NULL) {
            free(indexes->matrix[0]);
          }
          free(indexes->matrix);
          error_code = 1;
        }
      }
    } else {
      error_code = 1;
    }
  } else {
    *indexes_array = NULL;
    error_code = 3;
  }
  return error_code;
}

void s21_fill_vertexes(s21_list *vertexes_list, s21_double_matrix *vertexes,
                       s21_double_matrix *vertexes_base, size_t vertexes_count,
                       double x_shift, double y_shift, double z_shift) {
  s21_list *tmp_vertexes_list = vertexes_list->last;
  for (size_t i = 0; i < vertexes_count; i++) {
    vertexes->matrix[i][0] = vertexes_base->matrix[i][0] =
        tmp_vertexes_list->value.s21_vertex - x_shift;
    tmp_vertexes_list = tmp_vertexes_list->prev;
    vertexes->matrix[i][1] = vertexes_base->matrix[i][1] =
        tmp_vertexes_list->value.s21_vertex - y_shift;
    tmp_vertexes_list = tmp_vertexes_list->prev;
    vertexes->matrix[i][2] = vertexes_base->matrix[i][2] =
        tmp_vertexes_list->value.s21_vertex - z_shift;
    tmp_vertexes_list = tmp_vertexes_list->prev;
  }
  s21_destroy_list(vertexes_list);
}

void s21_fill_indexes(s21_list *indexes_list, s21_uint_matrix *indexes,
                      unsigned int **indexes_array, size_t lines_count, size_t vertexes_count) {
  s21_list *tmp_indexes_list = indexes_list->last;
  unsigned int *temp_pointer = *indexes_array;
  for (size_t i = 0; i < lines_count; i++) {
    if (tmp_indexes_list->value.s21_index <= vertexes_count && tmp_indexes_list->prev->value.s21_index <= vertexes_count
        &&
            tmp_indexes_list->value.s21_index > 0 && tmp_indexes_list->prev->value.s21_index > 0) {
      indexes->matrix[i][0] = tmp_indexes_list->value.s21_index - 1;
      tmp_indexes_list = tmp_indexes_list->prev;
      if (tmp_indexes_list->value.s21_index - 1 < indexes->matrix[i][0]) {
        indexes->matrix[i][1] = indexes->matrix[i][0];
        indexes->matrix[i][0] = tmp_indexes_list->value.s21_index - 1;
      } else {
        indexes->matrix[i][1] = tmp_indexes_list->value.s21_index - 1;
      }
      tmp_indexes_list = tmp_indexes_list->prev;
    } else {
      tmp_indexes_list = tmp_indexes_list->prev->prev;
    }
    *temp_pointer = indexes->matrix[i][0];
    temp_pointer++;
    *temp_pointer = indexes->matrix[i][1];
    temp_pointer++;
  }
  s21_destroy_list(indexes_list);
}

double s21_get_max_range(double min_x, double max_x, double min_y, double max_y,
                         double min_z, double max_z) {
  double max_range = max_x - min_x;
  max_range = max_range < max_y - min_y ? max_y - min_y : max_range;
  max_range = max_range < max_z - min_z ? max_z - min_z : max_range;
  return max_range;
}

void s21_sort_indexes(s21_uint_matrix *indexes, size_t left, size_t right) {
  if (right - left + 1 <= 3) {
    s21_manual_sort_in_matrix(indexes, left, right);
  } else {
    unsigned int pivot = s21_get_pivot_from_matrix(indexes, left, right);
    size_t partition = s21_partition_in_matrix(indexes, left, right, pivot);
    s21_sort_indexes(indexes, left, partition - 1);
    s21_sort_indexes(indexes, partition + 1, right);
  }
}

void s21_swap_in_matrix(s21_uint_matrix *matrix, size_t A, size_t B) {
  unsigned int temp[2] = {matrix->matrix[A][0], matrix->matrix[A][1]};
  matrix->matrix[A][0] = matrix->matrix[B][0];
  matrix->matrix[A][1] = matrix->matrix[B][1];
  matrix->matrix[B][0] = temp[0];
  matrix->matrix[B][1] = temp[1];
}

unsigned int s21_get_pivot_from_matrix(s21_uint_matrix *matrix, size_t left,
                                       size_t right) {
  size_t med = (left + right) / 2;
  if (matrix->matrix[left][0] > matrix->matrix[med][0]) {
    s21_swap_in_matrix(matrix, left, med);
  }
  if (matrix->matrix[left][0] > matrix->matrix[right][0]) {
    s21_swap_in_matrix(matrix, left, right);
  }
  if (matrix->matrix[med][0] > matrix->matrix[right][0]) {
    s21_swap_in_matrix(matrix, med, right);
  }
  s21_swap_in_matrix(matrix, med, right - 1);
  return matrix->matrix[right - 1][0];
}

void s21_manual_sort_in_matrix(s21_uint_matrix *matrix, size_t left,
                               size_t right) {
  size_t size = right - left + 1;
  if (size == 2) {
    if (matrix->matrix[left][0] > matrix->matrix[right][0]) {
      s21_swap_in_matrix(matrix, left, right);
    }
  } else if (size == 3) {
    if (matrix->matrix[left][0] > matrix->matrix[right - 1][0]) {
      s21_swap_in_matrix(matrix, left, right - 1);
    }
    if (matrix->matrix[left][0] > matrix->matrix[right][0]) {
      s21_swap_in_matrix(matrix, left, right);
    }
    if (matrix->matrix[left + 1][0] > matrix->matrix[right][0]) {
      s21_swap_in_matrix(matrix, left + 1, right);
    }
  }
}

size_t s21_partition_in_matrix(s21_uint_matrix *matrix, size_t left,
                               size_t right, unsigned int pivot) {
  size_t leftB = left;
  size_t rightB = right - 1;
  int stop = 0;
  while (!stop) {
    while (matrix->matrix[++leftB][0] < pivot);
    while (matrix->matrix[--rightB][0] > pivot);
    if (rightB <= leftB) {
      stop = 1;
    } else {
      s21_swap_in_matrix(matrix, leftB, rightB);
    }
  }
  s21_swap_in_matrix(matrix, leftB, right - 1);
  return leftB;
}

void s21_calc_edges_count(s21_uint_matrix indexes, size_t rows, size_t *edges) {
  if (rows > 0) {
    for (size_t i = 0; i < rows; i++) {
      int got_equal = 0;
      if (indexes.matrix[i][0] == indexes.matrix[i][1]) {
        got_equal = 1;
      }
      for (size_t j = i + 1;
           j < rows && indexes.matrix[i][0] == indexes.matrix[j][0] &&
               !got_equal;
           j++) {
        if (indexes.matrix[i][1] == indexes.matrix[j][1]) {
          got_equal = 1;
        }
      }
      if (!got_equal) {
        *edges = *edges + 1;
      }
    }
  }
}

void s21_swap(unsigned int *array, size_t A, size_t B) {
  unsigned int temp = array[A];
  array[A] = array[B];
  array[B] = temp;
}

unsigned int s21_get_pivot(unsigned int *array, size_t left, size_t right) {
  size_t med = (left + right) / 2;
  if (array[left] > array[med]) {
    s21_swap(array, left, med);
  }
  if (array[left] > array[right]) {
    s21_swap(array, left, right);
  }
  if (array[med] > array[right]) {
    s21_swap(array, med, right);
  }
  s21_swap(array, med, right - 1);
  return array[right - 1];
}

void s21_manual_sort(unsigned int *array, size_t left, size_t right) {
  size_t size = right - left + 1;
  if (size == 2) {
    if (array[left] > array[right]) {
      s21_swap(array, left, right);
    }
  } else if (size == 3) {
    if (array[left] > array[right - 1]) {
      s21_swap(array, left, right - 1);
    }
    if (array[left] > array[right]) {
      s21_swap(array, left, right);
    }
    if (array[left + 1] > array[right]) {
      s21_swap(array, left + 1, right);
    }
  }
}

size_t s21_partition(unsigned int *array, size_t left, size_t right,
                     unsigned int pivot) {
  size_t leftB = left;
  size_t rightB = right - 1;
  int stop = 0;
  while (!stop) {
    while (array[++leftB] < pivot);
    while (array[--rightB] > pivot);
    if (rightB <= leftB) {
      stop = 1;
    } else {
      s21_swap(array, leftB, rightB);
    }
  }
  s21_swap(array, leftB, right - 1);
  return leftB;
}

void s21_sort_array(unsigned int *array, size_t left, size_t right) {
  if (right - left + 1 <= 3) {
    s21_manual_sort(array, left, right);
  } else {
    unsigned int pivot = s21_get_pivot(array, left, right);
    size_t partition = s21_partition(array, left, right, pivot);
    s21_sort_array(array, left, partition - 1);
    s21_sort_array(array, partition + 1, right);
  }
}

void s21_calc_verts_count(unsigned int *array, size_t elems, size_t *vertexes) {
  if (elems > 0) {
    s21_sort_array(array, 0, elems - 1);
    *vertexes = 1;
    for (size_t i = 1; i < elems; i++) {
      if (array[i] != array[i - 1]) {
        *vertexes = *vertexes + 1;
      }
    }
    free(array);
  }
}
