#ifndef IVAN_LIST_H_
#define IVAN_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>
#include <stdbool.h>

typedef struct ListNode {
    int data;
    struct ListNode* prev;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
    ListNode* tail;
    size_t length;
} List;

bool ListInit(List*);
bool ListPushBack(List*, int);
bool ListPushFront(List*, int);
bool ListInsert(List*, size_t, int);
bool ListPopBack(List*, int*);
bool ListPopFront(List*, int*);
bool ListRemoveAt(List*, size_t, int*);
void ListDestruct(List*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_LIST_H_ */
