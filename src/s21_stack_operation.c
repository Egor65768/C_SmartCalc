#include <stdio.h>
#include <stdlib.h>

#include "s21_calc.h"

STAC* create(double value, int priority, int operation) {
  STAC* node = (STAC*)calloc(1, sizeof(STAC));
  node->value = value;
  node->priority = priority;
  node->operation = operation;
  node->next = NULL;
  return node;
}

void destroy(STAC* stac_notation) {
  while (stac_notation != NULL) {
    STAC* ptr = stac_notation->next;
    free(stac_notation);
    stac_notation = ptr;
  }
}

void push_back(STAC** stac_notation, double value, int priority,
               int operation) {
  STAC* new_elem = create(value, priority, operation);
  if (*stac_notation != NULL) {
    STAC* ptr = *stac_notation;
    while (ptr->next != NULL) {
      ptr = ptr->next;
    }
    ptr->next = new_elem;
  } else {
    *stac_notation = new_elem;
  }
}

void push_front(STAC** stac_notation, double value, int priority,
                int operation) {
  STAC* new_element = create(value, priority, operation);
  new_element->next = *stac_notation;
  *stac_notation = new_element;
}

void insert_into_stack_at_position(STAC** stac_notation, double value,
                                   int priority, int operation, int position) {
  int i = 0;
  STAC* new_elem = create(value, priority, operation);
  if (*stac_notation != NULL) {
    STAC* ptr = *stac_notation;
    while (ptr->next != NULL && i < position) {
      ptr = ptr->next;
      i++;
    }
    STAC* buf = ptr->next;
    ptr->next = new_elem;
    new_elem->next = buf;
  } else {
    *stac_notation = new_elem;
  }
}

STAC* remove_element_at_position(STAC* stac_notation, int position) {
  STAC* head = stac_notation;
  STAC* ptr = stac_notation;
  STAC* ptr_before = stac_notation;
  for (int i = 0; i < position; i++) {
    ptr_before = ptr;
    ptr = ptr->next;
  }
  if (ptr_before != ptr) {
    ptr_before->next = ptr->next;
    free(ptr);
  } else {
    ptr = stac_notation->next;
    free(stac_notation);
    head = ptr;
  }
  return head;
}

STAC* get_element_at_position(STAC* stac_notation, int position) {
  STAC* ptr = stac_notation;
  for (int i = 0; i < position; i++) {
    ptr = ptr->next;
  }
  return ptr;
}