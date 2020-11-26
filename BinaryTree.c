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

/**
 * 先序遍历二叉树的辅助函数。
 * 
 * @param nde 当前递归分支的起始节点
 * @param print 打印函数
 */
static void BinaryTreePreorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  // 节点判空返回
  if (!nde) return ;
  // 先序遍历优先打印子树根节点值
  print(nde->data);
  // 递归遍历左子树
  BinaryTreePreorderTraversalAuxWithPrinter(nde->left, print);
  // 递归遍历右子树
  BinaryTreePreorderTraversalAuxWithPrinter(nde->right, print);
}

/**
 * 先序遍历二叉树。由对应的辅助函数接管。
 * 
 * @param tr
 */
void BinaryTreePreorderTraversal(BinaryTree* tr)
{
  BinaryTreePreorderTraversalAuxWithPrinter(tr->root, printInt);
}

/**
 * 中序遍历二叉树的辅助函数。
 * 
 * @param nde 当前递归分支的起始节点
 * @param print 打印函数
 */
static void BinaryTreeInorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  // 节点判空返回
  if (!nde) return ;
  // 递归遍历左子树
  BinaryTreeInorderTraversalAuxWithPrinter(nde->left, print);
  // 中序遍历在中间打印子树根节点值
  print(nde->data);
  // 递归遍历右子树
  BinaryTreeInorderTraversalAuxWithPrinter(nde->right, print);
}

/**
 * 中序遍历二叉树。由对应的辅助函数接管。
 * 
 * @param tr
 */
void BinaryTreeInorderTraversal(BinaryTree* tr)
{
  BinaryTreeInorderTraversalAuxWithPrinter(tr->root, printInt);
}

/**
 * 后序遍历二叉树的辅助函数。
 * 
 * @param nde 当前递归分支的起始节点
 * @param print 打印函数
 */
static void BinaryTreePostorderTraversalAuxWithPrinter(BinaryTreeNode* nde, IntPrinter print) {
  // 节点判空返回
  if (!nde) return ;
  // 递归遍历左子树
  BinaryTreePostorderTraversalAuxWithPrinter(nde->left, print);
  // 递归遍历右子树
  BinaryTreePostorderTraversalAuxWithPrinter(nde->right, print);
  // 后序遍历在最后打印子树根节点值
  print(nde->data);
}

/**
 * 后序遍历二叉树。由对应的辅助函数接管。
 * 
 * @param nde 当前递归分支的起始节点
 * @param print 打印函数
 */
void BinaryTreePostorderTraversal(BinaryTree* tr)
{
  BinaryTreePostorderTraversalAuxWithPrinter(tr->root, printInt);
}

/**
 * 层序遍历二叉树的辅助函数。
 * 逻辑较为复杂，但是非常清晰。（写注释是被迫营业= =）
 * 
 * @param tr
 * @param print 打印函数
 */
void BinaryTreeLayerorderTraversalAuxWithPrinter(BinaryTree* tr, IntPrinter print)
{
  // 判空返回
  if (!tr->root) return ;
  // 内部元素为 BinaryTreeNode 指针的队列（实际上是链表）
  typedef struct BinaryTreeNodeQueueNode {
    BinaryTreeNode* data;
    struct BinaryTreeNodeQueueNode* next;
    struct BinaryTreeNodeQueueNode* prev;
  } BTNQueueNode;
  typedef struct BinaryTreeNodeQueue {
    BTNQueueNode* sentinel;
    BTNQueueNode* tail;
  } BTNQueue;
  /*
    因为层序遍历就是 BFS，逻辑是比较简单的。用 OOP 的伪码先介绍一下算法：
    create a queue<Node> as qe;
    qe.push tr.root;
    do loop until qe.empty:
      old_head <- qe.head
      if old_head = null:
        qe.pop
        next loop
      print value of old_head
      qe.push old_head.left
      qe.push old_head.right
      qe.pop
    不过实际实现起来，为了不提高代码的阅读难度，没有使用 OOP 和多态，
    所以内容就比较多了。
  */
  // 初始化队列空间
  BTNQueue* qe = (BTNQueue*) malloc(sizeof(BTNQueue));  // 制配空间
  qe->sentinel = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));  // 制配哨兵节点空间

  // 为树的根节点创建空间
  // 两个部分
  // 1. 将首节点挂载到哨兵节点 next 上
  // 2. 设置尾节点
  qe->sentinel->next = qe->tail = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
  // 将哨兵节点挂载到首节点 prev 上
  qe->tail->prev = qe->sentinel;
  // 将首节点的 data 设置为树的根节点
  qe->tail->data = tr->root;

  // 通过 qe->tail 判断队列是否为空。这一步想要成立得有先决条件：
  // 在每一个需要 tail 置空的情况将其置空。
  // 否则，需要用 qe->sentinel->next 来判断，
  // 而且不能保证其他算法不会出现错误
  while (qe->tail) {
    // 取得现在的首节点，因为待会儿一定会被取消挂载，不备份就找不到了。
    BTNQueueNode* old_head = qe->sentinel->next;
    // 只有当首节点有效（不为 null）时，才能将其左右子树添加到队列内。
    if (old_head->data) {
      // 这里是树节点不为空的情况，打印树节点的数据
      print(old_head->data->data);

      // 创建将要添加进队列的两个节点（这里的节点是队列的节点），
      // 一个用于存放左子树的根节点，另一个存放右子树的根节点
      BTNQueueNode* left_one = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
      BTNQueueNode* right_one = (BTNQueueNode*) malloc(sizeof(BTNQueueNode));
      // 这个 tail 是用于备份原尾部的，因为队列的插入操作是尾插，
      // 这里不备份之后找不到。
      BTNQueueNode* tail = qe->tail;

      // 设置两节点的 data 域
      left_one->data = old_head->data->left;
      right_one->data = old_head->data->right;

      // 做五个链接
      tail->next = left_one;
      left_one->next = right_one;
      right_one->next = NULL;
      right_one->prev = left_one;
      left_one->prev = tail;
      // 让 qe 的 tail 指向新的队尾
      qe->tail = right_one;
    }
    // 这部分是是首节点弹出逻辑。无论首节点是否有效，首节点都需要弹出。
    // 将 sentinel->next 的挂载链后移一位
    qe->sentinel->next = qe->sentinel->next->next;
    // 判断原首节点的下一位为不为空
    // 如果不为空，那还需要将它的 prev 域指向 sentinel
    // 如果为空，即队列为空，队列的尾节点指向需要更新
    if (qe->sentinel->next)
      qe->sentinel->next->prev = qe->sentinel;
    else qe->tail = NULL;
    // 解散原头部。
    free(old_head);
  }

  // 能到达这个地方，队列一定为空。直接解散哨兵节点和 qe 本身。算法结束。
  free(qe->sentinel);
  free(qe);
}

/**
 * 层序遍历二叉树。由对应的辅助函数接管。
 * 
 * @param tr
 */
void BinaryTreeLayerorderTraversal(BinaryTree* tr)
{
  BinaryTreeLayerorderTraversalAuxWithPrinter(tr, printInt);
}

/**
 * 二叉树析构的辅助函数，用于递归。
 */
static void BinaryTreeDestructAux(BinaryTreeNode* nde)
{
  if (!nde) return ;
  BinaryTreeDestructAux(nde->left);
  BinaryTreeDestructAux(nde->right);
}

/**
 * 二叉树析构的接口。
 * 
 * @param tr
 */
void BinaryTreeDestruct(BinaryTree* tr)
{
  BinaryTreeDestructAux(tr->root);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
