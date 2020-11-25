#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

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
  // 紧急修复这里的 bug，
  // 因为之前的测试都是在堆区开辟的区域，变量内元素被赋初值 0，
  // 而这次将变量分在程序栈区，初值未定，导致 Init 的失败。
  Stack stack = {NULL};
  Queue queue = {NULL};
  StackInit(&stack);
  QueueInit(&queue);

  for (int i = 0; i < 10; ++i) {
    StackPush(&stack, i);
    QueuePush(&queue, i);
  }

  __info_lst(stack.__lst, "internal list of stack: ");
  __info_lst(queue.__lst, "internal list of queue: ");

  puts("stack pop order: ");
  for (int i = 0; i < 10; ++i) {
    int n;
    StackPop(&stack, &n);
    printf("%d ", n);
  }
  putchar('\n');

  puts("queue pop order: ");
  for (int i = 0; i < 10; ++i) {
    int n;
    QueuePop(&queue, &n);
    printf("%d ", n);
  }
  putchar('\n');

  StackDestruct(&stack);
  QueueDestruct(&queue);
}
