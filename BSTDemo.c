#include <stdio.h>
#include "BST.h"
#include <stddef.h>
#include <stdlib.h>

static void add_arr_into_bst(BinaryTree* tr, int* arr, size_t a)
{
  for (size_t i = 0; i != a; ++i) {
    BSTInsert(tr, arr[i]);
  }
}

int main(void)
{
  BinaryTree* bst = (BinaryTree*) malloc(sizeof(BinaryTree));
  int arr[] = {4, 2, 1, 3, 6, 7, 5};
  const size_t A = sizeof(arr)/sizeof(arr[0]);
  add_arr_into_bst(bst, arr, A);
  
  printf("src: ");
  for (int i = 0; i != A; ++i) {
    printf("%d, ", arr[i]);
  }
  putchar('\n');

  puts("Init: ");
  BinaryTreeLayerorderTraversal(bst);

  BSTErase(bst, 4);
  puts("BSTErase(bst, 4);: ");
  BinaryTreeLayerorderTraversal(bst);

  BinaryTreeDestruct(bst);

  for (int i = 0; i < A; ++i) {
    arr[i] = i + 1;
  }
  printf("src: ");
  for (int i = 0; i != A; ++i) {
    printf("%d, ", arr[i]);
  }
  putchar('\n');

  add_arr_into_bst(bst, arr, A);
  puts("Init: ");
  BinaryTreeLayerorderTraversal(bst);

  BSTErase(bst, 4);
  puts("BSTErase(bst, 4): ");
  BinaryTreeLayerorderTraversal(bst);

  BinaryTreeDestruct(bst);
  free(bst);
}
