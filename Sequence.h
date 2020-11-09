#ifndef IVAN_SEQUENCE_H_
#define IVAN_SEQUENCE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>               // size_t
#include <stdbool.h>              // bool, true, false

typedef struct Sequence
{
  int* space;
  size_t size;
  size_t capacity;
} Sequence;

bool SequenceCreate(Sequence*);
bool SequencePush(Sequence*, int);
bool SequenceInsert(Sequence*, size_t, int);
bool SequencePop(Sequence*, int*);
bool SequenceRemoveAt(Sequence*, size_t, int*);
int* SequenceIterGenerate(Sequence*);
const int* SequenceConstIterGenerate(Sequence*);
void SequenceShrinkToFit(Sequence*);
size_t SequenceLength(Sequence*);
size_t SequenceCapacity(Sequence*);
void SequenceDestruct(Sequence*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IVAN_SEQUENCE_H_ */ 
