#include "s21_calc.h"

#include <stdio.h>
#include <stdlib.h>

int calculator(char* str, double* result) {
  int flag_error = 0;
  flag_error = validashion(str);
  if (flag_error == 0) {
    flag_error = calculate_from_expression(str, result);
  }
  return flag_error;
}

int calculate_from_expression(char* str, double* result) {
  int flag_error = 0;
  STAC* head = NULL;
  flag_error = parsing(&head, str, *result);
  if (flag_error == 0) {
    flag_error = validate_stack_conditions(head);
  }
  if (flag_error != 0) {
    destroy(head);
  }
  if (flag_error == 0) {
    STAC* ready = convert_to_postfix_notation(head);
    *result = calculate_postfix_expression(ready);
    if (isnan(*result)) {
      flag_error = 2;
    }
  }
  return flag_error;
}

STAC* convert_to_postfix_notation(STAC* stac_notation) {
  STAC* initial_stack = stac_notation;
  STAC* postfix_stack = NULL;
  STAC* operator_stack = NULL;
  STAC* next_node = NULL;
  int flag = 0;
  while (stac_notation != NULL) {
    if (stac_notation->priority == 0) {
      push_back(&postfix_stack, stac_notation->value, 0,
                stac_notation->operation);
    } else {
      flag = 0;
      if (operator_stack == NULL ||
          operator_stack->priority < stac_notation->priority ||
          stac_notation->operation == openbracket ||
          (operator_stack->priority == 3 && stac_notation->priority == 3)) {
        push_front(&operator_stack, stac_notation->value,
                   stac_notation->priority, stac_notation->operation);
      } else if (stac_notation->operation == closebracket) {
        while (operator_stack->operation != openbracket) {
          push_back(&postfix_stack, operator_stack->value,
                    operator_stack->priority, operator_stack->operation);
          next_node = operator_stack->next;
          free(operator_stack);
          operator_stack = next_node;
        }
        next_node = operator_stack->next;
        free(operator_stack);
        operator_stack = next_node;

      } else {
        while (operator_stack && flag == 0) {
          push_back(&postfix_stack, operator_stack->value,
                    operator_stack->priority, operator_stack->operation);
          next_node = operator_stack->next;
          free(operator_stack);
          operator_stack = next_node;
          if (operator_stack != NULL) {
            if (operator_stack->priority < stac_notation->priority ||
                operator_stack->operation == openbracket) {
              flag = 1;
            }
          }
        }
        push_front(&operator_stack, stac_notation->value,
                   stac_notation->priority, stac_notation->operation);
      }
    }
    stac_notation = stac_notation->next;
  }
  while (operator_stack != NULL) {
    push_back(&postfix_stack, operator_stack->value, operator_stack->priority,
              operator_stack->operation);
    next_node = operator_stack->next;
    free(operator_stack);
    operator_stack = next_node;
  }
  destroy(initial_stack);
  return postfix_stack;
}

double calculate_postfix_expression(STAC* stac_notation) {
  double result;
  int is_processing = 1;
  int operand_count;
  STAC* ptr = stac_notation;
  STAC* start = stac_notation;
  while (start->next != NULL) {
    is_processing = 1;
    operand_count = 0;
    while (is_processing) {
      if (ptr->priority != 0) {
        is_processing = 0;
        break;
      }
      ptr = ptr->next;
      operand_count++;
    }
    if (ptr->priority == 4) {
      ptr = start;
      start = calculate_math_function_from_stack(ptr, operand_count);
    } else {
      ptr = start;
      start = calculate_binary_operation(ptr, operand_count);
    }
    ptr = start;
  }
  result = start->value;
  free(start);
  return result;
}

STAC* calculate_binary_operation(STAC* stac_notation, int n) {
  STAC* ptr = stac_notation;
  double operand1 = 0.0, operand2 = 0.0, res = 0.0;
  ptr = get_element_at_position(ptr, n - 2);
  operand1 = ptr->value;
  ptr = get_element_at_position(ptr, 1);
  operand2 = ptr->value;
  ptr = get_element_at_position(ptr, 1);

  if (ptr->operation == calc_add) {
    res = operand1 + operand2;
  } else if (ptr->operation == calc_sub) {
    res = operand1 - operand2;
  } else if (ptr->operation == calc_mul) {
    res = operand1 * operand2;
  } else if (ptr->operation == calc_div) {
    res = operand1 / operand2;
  } else if (ptr->operation == calc_mod) {
    res = fmod(operand1, operand2);
  } else if (ptr->operation == calc_pow) {
    res = pow(operand1, operand2);
  }
  ptr = stac_notation;
  for (int i = 0; i < 3; i++) {
    ptr = remove_element_at_position(ptr, n - 2);
  }
  if (n > 2) {
    insert_into_stack_at_position(&ptr, res, 0, number, n - 3);
  } else {
    push_front(&ptr, res, 0, number);
  }
  return ptr;
}

STAC* calculate_math_function_from_stack(STAC* stac_notation, int position) {
  STAC* ptr = stac_notation;
  double result = 0.0;
  ptr = get_element_at_position(ptr, position - 1);
  result = ptr->value;
  ptr = get_element_at_position(ptr, 1);

  if (ptr->operation == calc_sin) {
    result = sin(result);
  } else if (ptr->operation == calc_cos) {
    result = cos(result);
  } else if (ptr->operation == calc_tan) {
    result = tan(result);
  } else if (ptr->operation == calc_acos) {
    result = acos(result);
  } else if (ptr->operation == calc_asin) {
    result = asin(result);
  } else if (ptr->operation == calc_atan) {
    result = atan(result);
  } else if (ptr->operation == calc_ln) {
    result = log(result);
  } else if (ptr->operation == calc_log) {
    result = log10(result);
  } else if (ptr->operation == calc_sqrt) {
    result = sqrt(result);
  }
  ptr = stac_notation;
  for (int i = 0; i < 2; i++) {
    ptr = remove_element_at_position(ptr, position - 1);
  }
  if (position > 1) {
    insert_into_stack_at_position(&ptr, result, 0, number, position - 2);
  } else {
    push_front(&ptr, result, 0, number);
  }
  return ptr;
}