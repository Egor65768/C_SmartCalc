#include "s21_calc.h"

int parsing(STAC** stac_notation, char* str, double result) {
  int flag_error = 0;
  int number_char = 0;
  int bracket = 0;
  int last_oper = 0;
  while (*(str + number_char) != '\n' && *(str + number_char) != '\0' &&
         flag_error == 0) {
    if ((*(str + number_char) >= '0' && *(str + number_char) <= '9') ||
        *(str + number_char) == 'x') {
      double element_value;
      if (*(str + number_char) != 'x') {
        element_value =
            read_number_with_error_check(str, &number_char, &flag_error);
      } else {
        element_value = result;
        number_char++;
      }
      push_back(stac_notation, element_value, 0, number);
      last_oper = 1;
    } else if (*(str + number_char) >= 'a' && *(str + number_char) <= 'z') {
      flag_error = parse_and_push_function(stac_notation, &number_char, str);
      last_oper = 1;
    } else if (strchr("+-()*/^ ", str[number_char]) != NULL) {
      parse_operator_and_brackets(stac_notation, str, number_char, &bracket,
                                  &last_oper);
      number_char++;
    } else {
      flag_error = 1;
      break;
    }
  }
  if (bracket != 0) {
    flag_error = 1;
  }
  return flag_error;
}

double read_number_with_error_check(char* str, int* number_char,
                                    int* flag_error) {
  double number;
  char* start = str + *number_char;
  short flag_end = 1;
  int flag_pointer = 1;
  while (flag_end && str[*number_char] != '\0') {
    if (strchr("0123456789", str[*number_char]) == NULL) {
      if (strchr(".", str[*number_char]) != NULL && flag_pointer == 1) {
        flag_pointer = 0;
        *number_char = *number_char + 1;
      } else if (strchr(".", str[*number_char]) != NULL && flag_pointer == 0) {
        *flag_error = 1;
        flag_end = 0;

      } else {
        flag_end = 0;
      }
    } else {
      *number_char = *number_char + 1;
    }
  }
  sscanf(start, "%lf", &number);
  return number;
}

int parse_and_push_function(STAC** stac_notation, int* number_char, char* str) {
  int status = 0;
  char* start = str + *number_char;
  if (*start == 'm' || *start == 'c' || *start == 't') {
    if (strncmp(start, "cos", 3) == 0) {
      push_back(stac_notation, 0.0, 4, calc_cos);
    } else if (strncmp(start, "mod", 3) == 0) {
      push_back(stac_notation, 0.0, 2, calc_mod);
    } else if (strncmp(start, "tan", 3) == 0) {
      push_back(stac_notation, 0.0, 4, calc_tan);
    } else {
      status = 1;
    }
    *number_char = *number_char + 3;
  } else if (*start == 's') {
    if (strncmp(start, "sin", 3) == 0) {
      push_back(stac_notation, 0.0, 4, calc_sin);
      *number_char = *number_char + 3;
    } else if (strncmp(start, "sqrt", 4) == 0) {
      push_back(stac_notation, 0.0, 4, calc_sqrt);
      *number_char = *number_char + 4;
    } else {
      status = 1;
    }
  } else if (*start == 'a') {
    if (strncmp(start, "acos", 4) == 0) {
      push_back(stac_notation, 0.0, 4, calc_acos);
    } else if (strncmp(start, "asin", 4) == 0) {
      push_back(stac_notation, 0.0, 4, calc_asin);
    } else if (strncmp(start, "atan", 4) == 0) {
      push_back(stac_notation, 0.0, 4, calc_atan);
    } else {
      status = 1;
    }
    *number_char = *number_char + 4;
  } else if (*start == 'l') {
    if (strncmp(start, "ln", 2) == 0) {
      push_back(stac_notation, 0.0, 4, calc_ln);
      *number_char = *number_char + 2;
    } else if (strncmp(start, "log", 3) == 0) {
      push_back(stac_notation, 0.0, 4, calc_log);
      *number_char = *number_char + 3;
    } else {
      status = 1;
    }
  } else if (*start == 'x') {
    push_back(stac_notation, 0.0, 0, calc_x);
    *number_char = *number_char + 1;
  } else {
    status = 1;
  }
  return status;
}

void parse_operator_and_brackets(STAC** stac_notation, char* str,
                                 int number_char, int* bracket,
                                 int* last_oper) {
  if (*(str + number_char) == '+') {
    if (*last_oper == 0) {
      push_back(stac_notation, 0.0, 0, number);
    }
    push_back(stac_notation, 0.0, 1, calc_add);
  } else if (*(str + number_char) == '-') {
    if (*last_oper == 0) {
      push_back(stac_notation, 0.0, 0, number);
    }
    push_back(stac_notation, 0.0, 1, calc_sub);
  } else if (*(str + number_char) == '(') {
    push_back(stac_notation, 0.0, -5, openbracket);
    *bracket = *bracket + 1;
    *last_oper = 0;
  } else if (*(str + number_char) == ')') {
    push_back(stac_notation, 0.0, -5, closebracket);
    *last_oper = 1;
    *bracket = *bracket - 1;
  } else if (*(str + number_char) == '*') {
    push_back(stac_notation, 0.0, 2, calc_mul);
  } else if (*(str + number_char) == '/') {
    push_back(stac_notation, 0.0, 2, calc_div);
  } else if (*(str + number_char) == '^') {
    push_back(stac_notation, 0.0, 3, calc_pow);
  }
}
