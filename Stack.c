#include "Stack.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

bool StackInit(Stack* sk)
{
  if (sk->__lst) return true;
  sk->__lst = (List*) malloc(sizeof(List));
  return ListInit(sk->__lst);
}

bool StackPush(Stack* sk, int i)
{
  return ListPushBack(sk->__lst, i);
}

bool StackPop(Stack* sk, int* pI)
{
  return ListPopBack(sk->__lst, pI);
}

const int* StackTop(Stack* sk)
{
  if (sk->__lst->head)
    return &sk->__lst->tail->data;
  return NULL;
}

void StackDestruct(Stack* sk)
{
  ListDestruct(sk->__lst);
  sk->__lst = NULL;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
