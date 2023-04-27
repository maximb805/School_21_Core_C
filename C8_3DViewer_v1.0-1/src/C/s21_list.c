#include "s21_3Dviewer.h"

s21_list *s21_create_node() {
  s21_list *new_node = (s21_list *)malloc(sizeof(s21_list));
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->last = NULL;
  return new_node;
}

void s21_destroy_list(s21_list *list) {
  while (list != NULL) {
    s21_list *next = list->next;
    free(list);
    list = next;
  }
}

void s21_add(s21_list **list, s21_value value) {
  if (list != NULL) {
    if (*list != NULL) {
      s21_list *new_node = s21_create_node();
      if (new_node != NULL) {
        new_node->value = value;
        new_node->next = *list;
        new_node->last = new_node->next->last;
        new_node->next->prev = new_node;
        *list = new_node;
      }
    } else {
      *list = s21_create_node();
      if (*list != NULL) {
        s21_list *tmp = *list;
        tmp->value = value;
        tmp->last = *list;
      }
    }
  }
}
