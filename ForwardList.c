#include "ForwardList.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>              // bool, true, false
#include <stdlib.h>               // malloc, calloc
#include "utils/Utilities.h"      // _Error, _Assert

static void __ForwardListCheck(ForwardList* lst)
{

}

static void __ForwardListCheckNull(ForwardList* lst)
{
  _Assert(lst->head, "Uninitialized forward list.");
}

/**
 * 初始化一个单链表。
 * 
 * @param lst
 * @return 初始化成功返回 `false`
 */
bool ForwardListInit(ForwardList* lst)
{
  if (lst->head) {
    return true;
  }
  lst->head = (ForwardListNode*) malloc(sizeof(ForwardListNode));
  lst->length = 0u;
  return false;
}

/**
 * 向单链表尾部插入元素。时间复杂度O(1)。
 * 考虑到如果不记录尾节点会让该操作的复杂度到达线性，我们优先选择牺牲一个
 * 指针的空间，换取常数级复杂度。
 * 
 * @param lst
 * @param i 待插入元素
 * @return 插入成功返回 `false`
 */
bool ForwardListPush(ForwardList* lst, int i)
{
  __ForwardListCheckNull(lst);
  if (lst->tail) {   // 尾部存在即列表不为空
    lst->tail->next = (ForwardListNode*) malloc(sizeof(ForwardListNode));
    if (!lst->tail->next)
      return true;
    lst->tail = lst->tail->next;
  }
  else {             // 反之为空
    lst->head->next = lst->tail = (ForwardListNode*) malloc(sizeof(ForwardListNode));
    if (!lst->tail)
      return true;
  }

  lst->tail->data = i;
  ++lst->length;
  __ForwardListCheck(lst);
  return false;
}

/**
 * 向单链表的 `pos` 位置插入一个数。时间复杂度O(N)。
 * 
 * @param lst
 * @param pos 插入的位置
 * @param i 待插入的元素
 * @return 插入成功返回 `false`
 */
bool ForwardListInsert(ForwardList* lst, size_t pos, int i)
{
  __ForwardListCheckNull(lst);
  // 当插入位置超出 size 范围
  if (pos > lst->length)
    return true;
  else if (pos == lst->length)
    return ForwardListPush(lst, i);
  
  ForwardListNode* it = lst->head;
  // 开始寻找 `pos` 位置的上一个节点
  for (int i = 0; i != pos; ++i) {
    it = it->next;
  }
  // 分配新节点
  ForwardListNode* new_node = (ForwardListNode*) malloc(sizeof(ForwardListNode));
  // 挂载链接
  new_node->next = it->next;
  it->next = new_node;
  new_node->data = i;
  ++lst->length;

  __ForwardListCheck(lst);
  return false;
}

/**
 * 删除单链表尾部的元素。时间复杂度O(N)。
 * 因为单链表的性质，该操作为线性复杂度。请将其与链表的相同操作进行参照。
 * 
 * @param lst
 * @param pI 接收原尾部值的拷贝。当为 NULL 时不进行拷贝。
 * @return 成功删除时返回 `false`
 */
bool ForwardListPop(ForwardList* lst, int* pI)
{
  __ForwardListCheckNull(lst);
  if (lst->length == 0)
    return true;
  
  // 查找 tail 的上一个节点
  ForwardListNode* it = lst->head;
  while (it->next != lst->tail)
    it = it->next;
  // 删除原 tail，重新设置 tail，断开无效链接
  free(lst->tail);
  lst->tail = it;
  it->next = NULL;
  --lst->length;

  __ForwardListCheck(lst);
  return false;
}

/**
 * 删除指定位置的节点。时间复杂度O(N)。
 * 
 * @param lst
 * @param pos 删除的位置
 * @param pI 接收删除值的拷贝。当其为 NULL 时不进行拷贝。
 * @return 成功删除时返回 `false`
 */
bool ForwardListRemoveAt(ForwardList* lst, size_t pos, int* pI)
{
  __ForwardListCheckNull(lst);
  if (pos >= lst->length)
    return true;
  else if (pos + 1 == lst->length)
    return ForwardListPop(lst, pI);

  ForwardListNode* it = lst->head;
  // 开始寻找 `pos` 位置的上一个节点
  for (int i = 0; i != pos; ++i) {
    it = it->next;
  }
  // 保存 `pos` 位置的指针
  ForwardListNode* next = it->next;
  // 将 `pos` 位置的上一个节点链接到下一个节点
  it->next = next->next;
  // 释放 `pos` 位置的节点
  if (pI != NULL)    // 安置 pI
    *pI = next->data;
  free(next);
  --lst->length;

  __ForwardListCheck(lst);
  return false;
}

/**
 * 返回表首迭代器。
 * 
 * @param lst
 * @return 表首迭代器，实为 ForwardListNode 指针。
 */
inline ForwardListNode* ForwardListIterBegin(ForwardList* lst)
{
  if (lst->head)
    return lst->head->next;
  return NULL;
}

/**
 * 返回表尾迭代器，即 NULL。
 * 
 * @param lst
 * @return 表首迭代器，实为 ForwardListNode 指针。
 */
inline ForwardListNode* ForwardListIterEnd(ForwardList* lst)
{
  return NULL;
}

/**
 * 前推单链表迭代器，类似于 itr += steps 的操作
 * 
 * @param it 当前迭代器
 * @param steps 前推步长
 * @return 运算后的迭代器
 */
ForwardListNode* ForwardListIterAdvance(ForwardListNode* it, size_t steps)
{
  while (steps--) {
    _Assert(it != NULL, "it == NULL");
    it = it->next;
  }
  return it;
}

/**
 * 解散单链表。
 * 
 * @param lst
 */
void ForwardListDestruct(ForwardList* lst)
{
  free(lst->head);
  free(lst->tail);
  lst->head = lst->tail = NULL;
  lst->length = 0u;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
