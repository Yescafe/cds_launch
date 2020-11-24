#ifndef IVAN_FORWARD_LIST_H_
#define IVAN_FORWARD_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdbool.h>

typedef struct ForwardListNode {
  int data;
  struct ForwardListNode* next;
} ForwardListNode;

typedef struct ForwardList {
  ForwardListNode* head;
  ForwardListNode* tail;
  size_t length;
} ForwardList;

bool ForwardListInit(ForwardList*);
bool ForwardListPush(ForwardList*, int);
bool ForwardListInsert(ForwardList*, size_t, int);
bool ForwardListPop(ForwardList*, int*);
bool ForwardListRemoveAt(ForwardList*, size_t, int*);
void ForwardListClear(ForwardList*);
ForwardListNode* ForwardListIterBegin(ForwardList*);
ForwardListNode* ForwardListIterEnd(ForwardList*);
ForwardListNode* ForwardListIterAdvance(ForwardListNode*, size_t);
void ForwardListDestruct(ForwardList*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_FORWARD_LIST_H_ */
