#include "s21_calc.h"

#define MAX_FUNCTION_NAME_LENGTH 4

int validashion(char* input_expression) {
  int bracket = 0;
  int flag_error = 0;
  char final_expression[MAX_SIZE_EXPRESSION];
  int number_of_symbols = 0;
  for (int i = 0; i < (int)strlen(input_expression) && flag_error == 0; i++) {
    if (input_expression[i] != ' ') {
      final_expression[number_of_symbols] = input_expression[i];
      number_of_symbols++;
    }
    if (number_of_symbols > MAX_SIZE_EXPRESSION - 4) {
      flag_error = 1;
    }
  }
  final_expression[number_of_symbols] = '\0';
  for (int i = 0; i < (int)strlen(final_expression) && flag_error == 0; i++) {
    if (strchr("+-()*/^", final_expression[i]) != NULL) {
      flag_error = check_math_syntax(final_expression, i, &bracket);
      if (bracket < 0) {
        flag_error = 1;
      }
    } else if (final_expression[i] == 'm' && final_expression[i + 1] == 'o' &&
               final_expression[i + 2] == 'd') {
      i = i + 2;
    } else if (final_expression[i] >= 'a' && final_expression[i] <= 'z' &&
               final_expression[i] != 'x') {
      flag_error = validate_function_operator_name(final_expression, &i);
    } else if ((final_expression[i] >= '0' && final_expression[i] <= '9') ||
               final_expression[i] == 'x') {
      flag_error = validate_expression_segment(final_expression, &i);
    }
  }

  return flag_error;
}

int check_for_x(char* input_expression) {
  int res = 0;
  for (int i = 0; i < (int)strlen(input_expression) && res == 0; i++) {
    if (input_expression[i] == 'x') {
      res = 1;
    }
  }
  return res;
}

int validate_expression_segment(char* str, int* char_position) {
  int flag_error = 0;
  int flag_end = 0;
  int flag_x = 0;
  int flag_num = 0;
  while (str[*char_position] != '\0') {
    if (strchr("0123456789.", str[*char_position]) == NULL &&
        str[*char_position] != 'x') {
      break;
    }
    if (str[*char_position] == 'x') {
      flag_x = 1;
      *char_position = *char_position + 1;
      break;
    } else {
      flag_num = 1;
    }
    *char_position = *char_position + 1;
    if (str[*char_position] == '\0') {
      flag_end = 1;
    }
  }
  if (strchr("+-*/^)", str[*char_position]) == NULL && flag_end == 0) {
    flag_error = 1;
  }
  if ((int)strlen(str) >= *char_position + 3) {
    if (str[*char_position] == 'm' && str[*char_position + 1] == 'o' &&
        str[*char_position + 2] == 'd') {
      flag_error = 0;
      *char_position = *char_position - 1;
    }
  }
  if (flag_num && flag_x) {
    flag_error = 1;
  }
  return flag_error;
}

int validate_function_operator_name(char* str, int* char_position) {
  int flag_error = 0, flag_stop = 0;
  for (int number_of_symbols = 0;
       number_of_symbols < MAX_FUNCTION_NAME_LENGTH && flag_stop == 0;
       number_of_symbols++) {
    if (str[*char_position] >= 'a' && str[*char_position] <= 'z') {
      *char_position = *char_position + 1;
    } else {
      flag_stop = 1;
    }
    if (str[*char_position] == 'x') {
      *char_position = *char_position + 1;
      break;
    }
  }
  *char_position = *char_position - 1;
  if (str[*char_position + 1] != '(' && str[*char_position] != 'd') {
    flag_error = 1;
  }

  return flag_error;
}

int check_math_syntax(char* str, int char_position, int* bracket) {
  int flag_error = 0;
  if (strchr("*/^)", str[char_position]) != NULL && char_position == 0) {
    flag_error = 1;
  } else if (strchr("+-*/^", str[char_position]) != NULL &&
             char_position != 0) {
    if (strchr("+-*/^", str[char_position - 1]) != NULL) {
      flag_error = 1;
    }
  } else if (str[char_position] == '(') {
    if (str[char_position + 1] == ')') {
      flag_error = 1;
    }
    *bracket = *bracket + 1;
  } else if (str[char_position] == ')') {
    *bracket = *bracket - 1;
  }
  return flag_error;
}

int validate_stack_conditions(STAC* stack_notation) {
  int flag_error = 0;
  STAC* ptr = stack_notation;
  if (ptr->priority == 1 || ptr->priority == 2 || ptr->priority == 3) {
    flag_error = 1;
  }
  while (ptr != NULL && flag_error == 0) {
    if (ptr->priority == 1 || ptr->priority == 2 || ptr->priority == 3) {
      ptr = ptr->next;
      if (ptr == NULL) {
        flag_error = 1;
      } else if (ptr->priority != 4 && ptr->priority != 0 &&
                 ptr->operation != openbracket) {
        flag_error = 1;
      }
    } else if (ptr->priority == 0) {
      ptr = ptr->next;
      if (ptr != NULL &&
          (ptr->priority == 4 || ptr->operation == openbracket)) {
        flag_error = 1;
      }
    } else {
      ptr = ptr->next;
    }
  }

  return flag_error;
}