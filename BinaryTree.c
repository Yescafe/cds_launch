#include "BinaryTree.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>              // bool, true, false
#include <stdlib.h>               // malloc, calloc
#include "utils/Utilities.h"      // _Error, _Assert
#include <stdio.h>                // printf

typedef void (*IntPrinter)(int);

void printInt(int i)
{
  printf("%d, ", i);
  fflush(stdout);
}

static void BinaryTreePreorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  if (!nde) return ;
  print(nde->data);
  BinaryTreePreorderTraversalAuxWithPrinter(nde->left, print);
  BinaryTreePreorderTraversalAuxWithPrinter(nde->right, print);
}

void BinaryTreePreorderTraversal(BinaryTree* tr)
{
  BinaryTreePreorderTraversalAuxWithPrinter(tr->root, printInt);
}

static void BinaryTreeInorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  if (!nde) return ;
  BinaryTreeInorderTraversalAuxWithPrinter(nde->left, print);
  print(nde->data);
  BinaryTreeInorderTraversalAuxWithPrinter(nde->right, print);
}

void BinaryTreeInorderTraversal(BinaryTree* tr)
{
  BinaryTreeInorderTraversalAuxWithPrinter(tr->root, printInt);
}

static void BinaryTreePostorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  if (!nde) return ;
  BinaryTreePostorderTraversalAuxWithPrinter(nde->left, print);
  BinaryTreePostorderTraversalAuxWithPrinter(nde->right, print);
  print(nde->data);
}

void BinaryTreePostorderTraversal(BinaryTree* tr)
{
  BinaryTreePostorderTraversalAuxWithPrinter(tr->root, printInt);
}

void BinaryTreeLayerorderTraversalAuxWithPrinter(BinaryTree* tr, IntPrinter print)
{
  if (!tr->root) return ;
  typedef struct BinaryTreeNodeQueueNode {
    BinaryTreeNode* data;
    struct BinaryTreeNodeQueueNode* next;
    struct BinaryTreeNodeQueueNode* prev;
  } BTNQueueNode;
  typedef struct BinaryTreeNodeQueue {
    BTNQueueNode* sentinel;
    BTNQueueNode* tail;
  } BTNQueue;
  BTNQueue* qe = (BTNQueue*) malloc(sizeof(BTNQueue));
  qe->sentinel = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
  qe->sentinel->next = qe->tail = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
  qe->tail->prev = qe->sentinel;
  qe->tail->data = tr->root;
  while (qe->tail) {
    BTNQueueNode* old_head = qe->sentinel->next;
    if (!old_head->data) {
      qe->sentinel->next = qe->sentinel->next->next;
      if (qe->sentinel->next)
        qe->sentinel->next->prev = qe->sentinel;
      else qe->tail = NULL;
    }
    else {
      print(old_head->data->data);

      BTNQueueNode* left_one = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
      BTNQueueNode* right_one = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
      BTNQueueNode* tail = qe->tail;

      left_one->data = old_head->data->left;
      right_one->data = old_head->data->right;

      tail->next = left_one;
      left_one->next = right_one;
      right_one->next = NULL;
      right_one->prev = left_one;
      left_one->prev = tail;
      qe->tail = right_one;

      qe->sentinel->next = qe->sentinel->next->next;
      if (qe->sentinel->next)
        qe->sentinel->next->prev = qe->sentinel;
      else qe->tail = NULL;
    }
    free(old_head);
  }

  free(qe->sentinel);
  free(qe);
}

void BinaryTreeLayerorderTraversal(BinaryTree* tr)
{
  BinaryTreeLayerorderTraversalAuxWithPrinter(tr, printInt);
}

static void BinaryTreeDestructAux(BinaryTreeNode* nde)
{
  if (!nde) return ;
  BinaryTreeDestructAux(nde->left);
  BinaryTreeDestructAux(nde->right);
}

void BinaryTreeDestruct(BinaryTree* tr)
{
  BinaryTreeDestructAux(tr->root);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
