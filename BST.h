#ifndef IVAN_BINARY_SEARCH_TREE_H_
#define IVAN_BINARY_SEARCH_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "BinaryTree.h"           // BinaryTree
#include <stdbool.h>              // bool, true, false

bool BSTInsert(BinaryTree*, int);
BinaryTreeNode* BSTFind(BinaryTree*, int);
bool BSTErase(BinaryTree*, int);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_BINARY_SEARCH_TREE_H_ */
