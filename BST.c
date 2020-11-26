#include "BST.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>               // malloc, calloc
#include "utils/Utilities.h"      // _Error, _Assert

/**
 * 向二叉搜索树中插入元素。
 * 
 * @param tr
 * @param i 待插入元素
 * @return 如果 BST 中已经存在该元素则返回 `true`。
 *         成功插入返回 `false`，另外其他情况均返回 `true`。
 */
bool BSTInsert(BinaryTree* tr, int i)
{
  BinaryTreeNode* it = tr->root;
  if (!it) {  // 空树创建
    tr->root = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    tr->root->data = i;
    tr->root->left = tr->root->right = NULL;
    return false;
  }
  else if (i == it->data) {  // 根节点即为 i
    return true;
  }
  BinaryTreeNode* parent;
  while (it && i != it->data) {
    int present_data = it->data;
    parent = it;
    if (i < present_data) {
      it = it->left;
    }
    else {
      it = it->right;
    }
  }
  if (it) {    // 找到了与 i 相等的节点
    return true;
  }
  // 没有找到需要添加
  int parent_data = parent->data;
  if (i < parent_data) {  // 比叶子节点小，左添加
    parent->left = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    parent->left->data = i;
    parent->left->left = parent->left->right = NULL;
  }
  else {    // 比叶子节点大，右添加
    parent->right = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    parent->right->data = i;
    parent->right->left = parent->right->right = NULL;
  }
  return false;
}

/**
 * 在二叉搜索树中查找一个元素。
 * 
 * @param tr
 * @param i 查找目标
 * @return 找到则返回指向目标节点的指针，否则返回 NULL
 */
BinaryTreeNode* BSTFind(BinaryTree* tr, int i)
{
  BinaryTreeNode* it = tr->root;
  while (it) {
    if (i == it->data) {
      break;
    }
    else if (i < it->data) {
      it = it->left;
    }
    else {
      it = it->right;
    }
  }
  return it;
}

/**
 * 局部函数，提供给 `BSTErase` 使用。
 * 将 `slave` 子树挂载到 `master` 子树下。
 * 
 * @param master 挂载点
 * @param slave 待挂载子树根节点
 */
static void BSTMount(BinaryTreeNode* master, BinaryTreeNode* slave)
{
  // 作为兄弟节点的两颗子树，`slave` 中所有子节点和 `master` 中所有子节点
  // 都有绝对的序，于是只需判断是将 `slave` 挂载在 `master` 的最左端还是最右端。
  if (slave->data < master->data) { // 极左挂载
    BinaryTreeNode* it = master;
    BinaryTreeNode* leftest;
    while (it) {
      leftest = it;
      it = it->left;
    }
    leftest->left = slave;
  }
  else { // 极右挂载
    BinaryTreeNode* it = master;
    BinaryTreeNode* rightest;
    while (it) {
      rightest = it;
      it = it->right;
    }
    rightest->right = slave;
  }
}

/**
 * 删除二叉搜索树中的元素。
 * 
 * @param tr
 * @param i 查找元素
 * @return 如果成功找到且删除成功则返回 `false` 
 */
bool BSTErase(BinaryTree* tr, int i)
{
  BinaryTreeNode* it = tr->root;
  BinaryTreeNode* parent = NULL;
  if (!it) return true;
  while (it && i != it->data) {
    parent = it;
    if (i < it->data) {
      it = it->left;
    }
    else {
      it = it->right;
    }
  }
  if (!it) {
    return true;
  }
  // 四种子节点情况判断
  if (it->left && it->right) {           // 左右子树均存在
    BSTMount(it->left, it->right);
    BinaryTreeNode* old_it = it;
    it = it->left;
    free(old_it);
  } else if (it->left && !it->right) {   // 右子树不存在
    BinaryTreeNode* old_it = it;
    it = it->left;
    free(old_it);
  } else if (!it->left && it->right) {   // 左子树不存在
    BinaryTreeNode* old_it = it;
    it = it->right;
    free(old_it);
  } else {   // 无子树
    free(it);
    it = NULL;
  }
  // 更新父节点的挂载
  if (!parent) { // 删除的是根节点
    tr->root = it;   // 此时需要更新根节点
  }
  else {
    int parent_data = parent->data;
    // 根据 `i` 和 `parent_data` 的相对大小判断更新的是左子树还是右子树
    if  (i < parent_data) {
      parent->left = it;
    }
    else {
      parent->right = it;
    }
  }
  return false;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
