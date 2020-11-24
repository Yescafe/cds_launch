#ifndef IVAN_QUEUE_H_
#define IVAN_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "List.h"        // for List
#include <stddef.h>
#include <stdbool.h>

typedef struct Queue {
  List* __lst;
} Queue;

bool QueueInit(Queue*);
bool QueuePush(Queue*, int);
bool QueuePop(Queue*, int*);
const int* QueueHead(Queue*);
const int* QueueTail(Queue*);
void QueueDestruct(Queue*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_QUEUE_H_ */
