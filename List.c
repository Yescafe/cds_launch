#include "List.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>              // bool, true, false
#include <stdlib.h>               // malloc, calloc
#include "utils/Utilities.h"      // _Error, _Assert

static void __ListCheck(List* lst)
{

}

static void __ListCheckNull(List* lst)
{
  _Assert(lst->head, "Uninitialized list.");
}

/**
 * 初始化一个链表。
 * 
 * @param lst
 * @return 初始化成功返回 `false`
 */
bool ListInit(List* lst)
{
  if (lst->head) {
    return true;
  }
  lst->head = (ListNode*) malloc(sizeof(ListNode));
  lst->length = 0u;
  return false;
}

/**
 * 向链表的尾部插入元素。时间复杂度 O(1)。
 * 与单链表相同，考虑到尾插的时间复杂度问题，我们优先选择
 * 牺牲一个指针位用于存放链表的尾节点。
 * 
 * @param lst
 * @param i 待插入的元素
 * @return 插入成功返回 `false`
 */
bool ListPushBack(List* lst, int i)
{
  __ListCheckNull(lst);
  if (lst->length == 0) {   // 链表为空
    _Assert(!lst->tail, "tail exists when the list is empty");  // 断言此时尾指针不存在
    lst->head->next = (ListNode*) malloc(sizeof(ListNode));
    if (!lst->head->next)
      return true;
    lst->head->next->prev = lst->head;  // 将头部哨兵节点挂载到新节点上
    lst->tail = lst->head->next;
  }
  else {
    _Assert(lst->tail, "tail is null when the list is not empty");   // 断言此时尾指针存在
    lst->tail->next = (ListNode*) malloc(sizeof(ListNode));
    if (!lst->tail->next)  // 空间制配失败
      return true;
    lst->tail->next->prev = lst->tail;  // 将旧尾部挂载到新尾部后面
    lst->tail = lst->tail->next;        // 更新尾部
  }
  lst->tail->data = i;
  ++lst->length;
  __ListCheck(lst);
  return false;
}

/**
 * 向链表首部插入元素。时间复杂度 O(1)。
 * 很奇怪，不知道为什么在单链表中我忘记写了。这个简单操作单链表也是可以
 * 以 O(1) 的时间复杂度完成的。
 * 
 * @param lst
 * @param i 待插入元素
 * @return 插入成功时返回 `false`
 */
bool ListPushFront(List* lst, int i)
{
  __ListCheckNull(lst);
  // 无论是对于一个空链表，还是非空链表。头插的操作逻辑都是一样的，
  // 于是将两分支合并。
  ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
  if (!new_node)
    return true;
  new_node->next = lst->head->next;    // 将首节点的下一个节点挂载到新插入节点上。如果链表为空该值应该为 NULL
  new_node->prev = lst->head;   // 将首部哨兵挂载到新插入节点的 prev 上
  lst->head->next = new_node;   // 更新首节点指针
  if (!lst->tail)     // 如果原尾部为空，即原链表为空链表
    lst->tail = new_node;    // 那么新插入的节点为尾元素
  new_node->data = i;
  ++lst->length;
  __ListCheck(lst);
  return false;
}

/**
 * 向链表的 `pos` 位置插入一个元素。时间复杂度 O(N)。
 * 
 * @param lst
 * @param pos 待插入位置
 * @param i 待插入元素
 * @return 插入成功则返回 `false`
 */
bool ListInsert(List* lst, size_t pos, int i)
{
  __ListCheckNull(lst);
  // 当插入位置超出 size 范围
  if (pos > lst->length)
    return true;
  else if (pos == lst->length)  // 尾插行为由 `ListPushBack` 接管
    return ListPushBack(lst, i);
  
  // 这句是下面移上来的，因为如果内存在这里就无法分配成功，
  // 下面的遍历操作就不再需要
  ListNode* new_node = (ListNode*) malloc(sizeof(ListNode));
  if (!new_node) 
    return true;

  // 这里考虑一层优化。因为该链表支持双向遍历，我们尽量从最近的一端寻找待查节点位置。
  if (pos < lst->length / 2) {
    ListNode* it = lst->head;
    for (size_t i = 0; i != pos; ++i) // 搜索插入位置的上一个节点
      it = it->next;

    // 注意插入行为的四个指针域的更新顺序
    new_node->next = it->next;
    new_node->prev = it;
    it->next->prev = new_node;
    it->next = new_node;
  }
  else {
    ListNode* it = lst->tail;
    for (size_t i = lst->length - 1; i != pos; --i)
      it = it->prev;

    new_node->prev = it->prev;
    new_node->next = it;
    it->prev->next = new_node;
    it->prev = new_node;
  }
  new_node->data = i;
  ++lst->length;
  __ListCheck(lst);
  return false;
}

/**
 * 从链表尾部删除元素。时间复杂度 O(1)。
 * 这是我非常期待的一个部分，因为链表的双向遍历属性，这样的一个尾删操作
 * 会与单链表的尾删逻辑完全不同。
 * 
 * @param lst
 * @param pI 回收尾部元素
 * @return 删除成功返回 `false`
 */
bool ListPopBack(List* lst, int* pI)
{
  __ListCheckNull(lst);
  if (lst->length == 0)
    return true;
  ListNode* new_tail = lst->tail->prev;  // 即旧尾部的上一个节点
  // 回收原尾部
  if (pI != NULL)
    *pI = lst->tail->data;
  // 解散原尾部
  free(lst->tail);
  if (new_tail == lst->head)   // 如果这是最后一个节点
    lst->tail = NULL;          // 尾部应被设置为 NULL
  else
    lst->tail = new_tail;
  new_tail->next = NULL;
  --lst->length;
  __ListCheck(lst);
  return false;
}

/**
 * 从链表首部删除元素。时间复杂度 O(1)。
 * 同样的，单链表也可以以 O(1) 完成该算法。
 * 直接由 `ListRemoveAt` 接管。
 * 
 * @param lst
 * @param pI 回收尾部元素
 * @return 删除成功返回 `false`
 */
bool ListPopFront(List* lst, int* pI)
{
  return ListRemoveAt(lst, 0u, pI);
}

/**
 * 删除指定位置的元素。
 * 
 * @param lst
 * @param pos 待删除位置
 * @param pI 回收尾部元素
 * @return 删除成功返回 `false`
 */
bool ListRemoveAt(List* lst, size_t pos, int* pI)
{
  __ListCheckNull(lst);
  if (pos > lst->length)
    return true;
  // 因为节点拥有两个指针域 `prev` 和 `next`，这个算法的需要讨论的情况
  // 是整个链表中最繁杂的。
  // 先特判 `pos` 是不是最后位置
  else if (pos == lst->length - 1) {
    // 如果是，那么它的下一个节点不存在，无需更新下一个节点的 `prev` 域
    // 并且这里也可以直接由 pop back 操作托管
    return ListPopBack(lst, pI);
  }
  // 对于一般情况，进行遍历
  // 同样的，删除操作也可以做两向的优化。
  if (pos < lst->length / 2) {  // 从 lst->head 逼近
    ListNode* it = lst->head;
    for (int i = 0; i != pos; ++i)
      it = it->next;
    ListNode* target = it->next;
    // 找到靶子后尝试回收
    if (pI != NULL)
      *pI = target->data;
    // 更新靶子前后节点的指针域
    it->next = target->next;
    target->next->prev = it;
    // 解散靶子节点
    free(target);
  }
  else {  // 从 lst->tail 逼近
    ListNode* it = lst->tail;
    for (int i = lst->length - 1; i != pos + 1; --i)
      it = it->prev;
    ListNode* target = it->prev;
    if (pI != NULL)
      *pI = target->data;
    it->prev = target->prev;
    target->prev->next = it;
    free(target);
  }
  --lst->length;
  __ListCheck(lst);
  return false;
}

/**
 * 清空链表。
 * 
 * @param lst
 */
void ListClear(List* lst)
{
  while (lst->length != 0)
    ListPopBack(lst, NULL);
}

/**
 * 析构链表。
 * 
 * @param lst
 */
void ListDestruct(List* lst)
{
  ListClear(lst);
  free(lst->head);
  lst->head = lst->tail = NULL;
  lst->length = 0u;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
