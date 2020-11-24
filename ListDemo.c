#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void __info_lst(List* lst, const char* info)
{
  printf("\n%s", info);
  printf(": \n");
  printf("seq {            \n");
  printf("  head = %p      \n", (void*) lst->head);
  printf("  tail = %p      \n", (void*) lst->tail);
  printf("  length = %zd   \n", lst->length);
  printf("}                \n");
  printf("list items:");
  int output_limit = 20, i = 0;
  if (lst->head) {
    for (ListNode* it = lst->head->next; it != NULL && i < output_limit; it = it->next, ++i)
      printf(" %d", it->data);
    printf("\n");
  } else {
    printf(" (null)\n");
  }
}

int main(void)
{
  List* lst = (List*) malloc(sizeof(List));
  ListInit(lst);

  for (int i = 0; i < 5; ++i)
    ListPushBack(lst, i + 6);
  __info_lst(lst, "Push back 5 elems");

  for (int i = 5; i > 0; --i)
    ListPushFront(lst, i);
  __info_lst(lst, "Push front 5 elems");

  for (int i = 0; i < 5; ++i) {
    int n;
    ListRemoveAt(lst, lst->length / 2 - 1, &n);
    printf("%d ", n);
  }
  printf("\n");
  __info_lst(lst, "Remove at middle of lst 5 times");

  ListRemoveAt(lst, 1, NULL);
  __info_lst(lst, "Remove the second element");

  for (int i = 0; i < 3; ++i)
    ListInsert(lst, lst->length - 1, i + 11);
  __info_lst(lst, "Insert 3 elems at the righter side");

  for (int i = 0; i < 3; ++i)
    ListInsert(lst, 1, i + 11);
  __info_lst(lst, "Insert 3 elems at the lefter side");

  ListDestruct(lst);
  __info_lst(lst, "Destrcut list");
  free(lst);
}
