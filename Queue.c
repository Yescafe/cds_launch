#include "Queue.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

bool QueueInit(Queue* qe)
{
  if (qe->__lst) return true;
  qe->__lst = (List*) malloc(sizeof(List));
  return ListInit(qe->__lst);
}

bool QueuePush(Queue* qe, int i)
{
  return ListPushBack(qe->__lst, i);
}

bool QueuePop(Queue* qe, int* pI)
{
  return ListPopFront(qe->__lst, pI);
}

const int* QueueHead(Queue* qe)
{
  if (qe->__lst->length == 0)
    return NULL;
  return &qe->__lst->head->next->data;
}

const int* QueueTail(Queue* qe)
{
  if (qe->__lst->length == 0)
    return NULL;
  return &qe->__lst->tail->data;
}

void QueueDestruct(Queue* qe)
{
  ListDestruct(qe->__lst);
  qe->__lst = NULL;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
