#ifndef IVAN_BINARY_TREE_H_
#define IVAN_BINARY_TREE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct BinaryTreeNode {
  int data;
  struct BinaryTreeNode* left;
  struct BinaryTreeNode* right;
} BinaryTreeNode;

typedef struct BinaryTree {
  BinaryTreeNode* root;
} BinaryTree;

void BinaryTreePreorderTraversal(BinaryTree* tr);
void BinaryTreeInorderTraversal(BinaryTree* tr);
void BinaryTreePostorderTraversal(BinaryTree* tr);
void BinaryTreeLayerorderTraversal(BinaryTree* tr);
void BinaryTreeDestruct(BinaryTree* tr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_BINARY_TREE_H_ */
