#include <stdio.h>
#include "ForwardList.h"
#include <stdlib.h>

static void __info_lst(ForwardList* lst, const char* info)
{
  printf("\n%s", info);
  printf(": \n");
  printf("seq {            \n");
  printf("  head = %p      \n", (void*) lst->head);
  printf("  tail = %p      \n", (void*) lst->tail);
  printf("  length = %zd   \n", lst->length);
  printf("}                \n");
  printf("list items:");
  for (ForwardListNode* it = ForwardListIterBegin(lst); it != ForwardListIterEnd(lst); it = ForwardListIterAdvance(it, 1))
    printf(" %d", it->data);
  printf("\n");
}

int main(void)
{
  ForwardList* lst = (ForwardList*) malloc(sizeof(ForwardList));
  ForwardListInit(lst);
  for (int i = 0; i < 5; ++i)
    ForwardListPush(lst, i + 1);
  __info_lst(lst, "push back 5 elems");

  for (int i = 0; i < 5; ++i)
    ForwardListInsert(lst, 0, i + 1);
  __info_lst(lst, "insert 5 elems at front");

  int size = lst->length;
  for (int i = 0; i < size; ++i) {
    int i;
    ForwardListRemoveAt(lst, lst->length / 2, &i);
    printf("removed %d\n", i);
  }
  __info_lst(lst, "remove all items in the middle");

  ForwardListInsert(lst, 0, 100);
  __info_lst(lst, "insert at front of a empty forward list");

  //! bug here
  //! 经过排查和考究，destruct -> clear -> remove_at -> pop -> insert
  //! 问题应该出在 insert 插入元素时没有考虑原单链表中有无元素，是否需要设置尾节点指针
  ForwardListDestruct(lst);
  __info_lst(lst, "destruct");

  free(lst);
  return 0;
}
