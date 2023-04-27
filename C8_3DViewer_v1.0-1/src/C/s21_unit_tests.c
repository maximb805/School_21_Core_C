#include <check.h>

#include "s21_3Dviewer.h"

START_TEST(test1) {
  s21_list *vertexes_list = NULL;
  s21_list *indexes_list = NULL;
  s21_uint_matrix indexes;
  indexes.matrix = NULL;
  unsigned int *indexes_array;
  s21_double_matrix vertexes;
  s21_double_matrix vertexes_base;
  vertexes.matrix = NULL;
  vertexes_base.matrix = NULL;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  int xR = 0, yR = 0, zR = 0, xM = 0, yM = 0, zM = 0;
  int scale = 1, scale_prev = 1;
  s21_get_arrays("./obj/ball.obj", &vertexes_list, &vertexes_coords_count,
                 &indexes_list, &indexes_points_count, &min_x, &max_x, &min_y,
                 &max_y, &min_z, &max_z);
  s21_lists_to_matrixes(
      vertexes_list, &vertexes, &vertexes_base, vertexes_coords_count,
      indexes_list, &indexes, indexes_points_count, &indexes_array,
      (max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2);
  size_t real_vertexes_count = 0;
  s21_calc_verts_count(indexes_array, indexes_points_count,
                       &real_vertexes_count);
  size_t real_edges_count = 0;
  s21_calc_edges_count(indexes, indexes_points_count / 2, &real_edges_count);
  s21_rotate(&vertexes, &vertexes_base, vertexes_coords_count / 3, xR, yR, zR,
             xM, yM, zM);
  s21_rescale(&vertexes, &vertexes_base, vertexes_coords_count / 3,
              scale / scale_prev, xR, yR, zR, xM, yM, zM);
  free(indexes.matrix[0]);
  free(indexes.matrix);
  free(vertexes.matrix[0]);
  free(vertexes.matrix);
  free(vertexes_base.matrix[0]);
  free(vertexes_base.matrix);
  ck_assert_double_eq(max_y, 1.929437);
}
END_TEST

START_TEST(test2) {
  double test = s21_get_max_range(-1.5, 2, -2, 1.5, -5.1, 4);
  ck_assert_double_eq(test, 9.1);
}

START_TEST(test3) {
  s21_list *vertexes_list = NULL;
  s21_list *indexes_list = NULL;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  int error_code = s21_get_arrays("./obj/no_such_filezxc123.obj",
                                  &vertexes_list, &vertexes_coords_count,
                                  &indexes_list, &indexes_points_count, &min_x,
                                  &max_x, &min_y, &max_y, &min_z, &max_z);
  ck_assert_int_eq(error_code, 2);
}

START_TEST(test4) {
  s21_list *vertexes_list = NULL;
  s21_list *indexes_list = NULL;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  s21_get_arrays("./obj/test2.obj", &vertexes_list, &vertexes_coords_count,
                 &indexes_list, &indexes_points_count, &min_x, &max_x, &min_y,
                 &max_y, &min_z, &max_z);
  s21_destroy_list(vertexes_list);
  s21_destroy_list(indexes_list);
  ck_assert_int_eq((int)indexes_points_count, 2);
}

START_TEST(test5) {
  s21_list *vertexes_list = NULL;
  s21_list *indexes_list = NULL;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  int error_code = s21_get_arrays(
      "./obj/test3.obj1", &vertexes_list, &vertexes_coords_count, &indexes_list,
      &indexes_points_count, &min_x, &max_x, &min_y, &max_y, &min_z, &max_z);
  s21_destroy_list(vertexes_list);
  s21_destroy_list(indexes_list);
  ck_assert_int_eq(error_code, 2);
}

START_TEST(test6) {
  s21_list *vertexes_list = NULL;
  s21_list *indexes_list = NULL;
  size_t vertexes_coords_count = 0;
  size_t indexes_points_count = 0;
  double min_x = 0, max_x = 0, min_y = 0, max_y = 0, min_z = 0, max_z = 0;
  int error_code = s21_get_arrays(
      "./obj/test3.obj", &vertexes_list, &vertexes_coords_count, &indexes_list,
      &indexes_points_count, &min_x, &max_x, &min_y, &max_y, &min_z, &max_z);
  s21_destroy_list(vertexes_list);
  s21_destroy_list(indexes_list);
  ck_assert_int_eq(error_code, 0);
}

Suite *suite_insert(void) {
  Suite *s = suite_create("start_tests");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, test1);
  tcase_add_test(tc, test2);
  tcase_add_test(tc, test3);
  tcase_add_test(tc, test4);
  tcase_add_test(tc, test5);
  tcase_add_test(tc, test6);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  Suite *s1;
  SRunner *sr;
  s1 = suite_insert();
  sr = srunner_create(s1);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);
  return 0;
}
