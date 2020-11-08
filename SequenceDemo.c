#include <stdio.h>
#include <stdlib.h>
#include "Sequence.h"

static void __info_seq(Sequence* seq, const char* info)
{
  printf("\n%s", info);
  printf(": \n");
  printf("seq {            \n");
  printf("  space = %p     \n", (void*) seq->space);
  printf("  size  = %zd    \n", seq->size);
  printf("  capacity = %zd \n", seq->capacity);
  printf("}                \n");
  printf("list items:");
  const int* cSpace = SequenceConstIterGenerate(seq);
  for (size_t i = 0u; i < seq->size; ++i) {
    printf(" %d", cSpace[i]);
  }
  printf("\nlist space:");
  cSpace = SequenceConstIterGenerate(seq);
  for (size_t i = 0u; i < seq->capacity; ++i) {
    printf(" %d", cSpace[i]);
  }
  printf("\n");
}

int main(void)
{
  Sequence* seq = (Sequence*) malloc(sizeof(Sequence));

  SequenceCreate(seq);
  __info_seq(seq, "create array");

  for (int i = 0; i < 6; ++i) {
    SequencePush(seq, i + 1);
  }
  __info_seq(seq, "push 6 elems");

  while (seq->size != 0)
    SequencePop(seq, NULL);
  __info_seq(seq, "pop 6 elems");

  for (int i = 0; i < 8; ++i) {
    SequencePush(seq, i + 1);
  }
  __info_seq(seq, "push 8 elems");

  for (int i = 0; i < 3; ++i) {
    SequenceInsert(seq, 0, -i - 1);
  }
  __info_seq(seq, "push 3 elems on front");

  for (int i = 0; i < 5; ++i) {
    int removed;
    SequenceRemoveAt(seq, seq->size / 2, &removed);
    printf("removed %d\n", removed);
  }
  __info_seq(seq, "remove 5 elems int the middle position");

  for (int i = 0; i < 2; ++i) {
    SequenceInsert(seq, seq->size, 1000);
  }
  __info_seq(seq, "insert 2 items at tail");

  for (int i = 0; i < 2; ++i) {
    SequenceInsert(seq, seq->size - 1, 999);
  }
  __info_seq(seq, "insert 2 items at the pioneer of tail");

  SequenceShrinkToFit(seq);
  __info_seq(seq, "shrink to fit");

  SequencePush(seq, 10001);
  __info_seq(seq, "then push 1 elem");

  SequenceDestruct(seq);
  __info_seq(seq, "destruct");

  free(seq);
  return 0;
}
