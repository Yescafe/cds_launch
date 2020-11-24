#ifndef IVAN_STACK_H_
#define IVAN_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "List.h"        // for List
#include <stddef.h>
#include <stdbool.h>

typedef struct Stack {
  List* __lst;
} Stack;

bool StackInit(Stack*);
bool StackPush(Stack*, int);
bool StackPop(Stack*, int*);
const int* StackTop(Stack*);
void StackDestruct(Stack*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_STACK_H_ */
