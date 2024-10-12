#include "tests.h"

int main() {
  int failed = 0;
  Suite *s21_matrix_test[] = {test_calc_complements(), test_calc_credit(),
                              test_calc_dep(), NULL};

  for (int i = 0; s21_matrix_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_matrix_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
