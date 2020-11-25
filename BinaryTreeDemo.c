#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
// #define _DEBUG

#ifdef _DEBUG
  static void printInt(int i)
  {
    printf("i = %d\n", i);
  }
#else
#  define printInt(X) ((void) 0)
#endif /* _DEBUG */

static void create_binary_tree(BinaryTreeNode** pNode, int input[], size_t a, size_t* k, int null)
{
  printInt(*k);
  if (*k < a) {
    if (input[*k] == null) {
      ++(*k);
      return ;
    }
    *pNode = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    (*pNode)->data = input[(*k)++];
    create_binary_tree(&(*pNode)->left, input, a, k, null);
    create_binary_tree(&(*pNode)->right, input, a, k, null);
  }
}

int main(void)
{
  BinaryTree* binary_tree = (BinaryTree*) malloc(sizeof(BinaryTree));
  int arr[] = {1, 2, 4, 0, 0, 5, 0, 0, 3, 6, 0, 0, 7, 0, 0};
  size_t k = 0;
  create_binary_tree(&binary_tree->root, arr, sizeof(arr)/sizeof(arr[0]), &k, 0);
  
  puts("Pre-order Traversal: ");
  BinaryTreePreorderTraversal(binary_tree);
  putchar('\n');

  puts("In-order Traversal: ");
  BinaryTreeInorderTraversal(binary_tree);
  putchar('\n');

  puts("Post-order Traversal: ");
  BinaryTreePostorderTraversal(binary_tree);
  putchar('\n');

  puts("Layer-order Traversal: ");
  BinaryTreeLayerorderTraversal(binary_tree);
  putchar('\n');

  BinaryTreeDestruct(binary_tree);
  free(binary_tree);
  return 0;
}
