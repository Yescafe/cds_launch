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
  Stack stack;
  Queue queue;
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
