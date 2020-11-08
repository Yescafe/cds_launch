#include "Sequence.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>               // malloc, calloc, exit
#include "utils/Utilities.h"      // _Error, _Assert
#include <string.h>               // memcpy

// 局部函数，执行检查
inline static void __SequenceCheck(Sequence* seq)
{
  _Assert(seq->size <= seq->capacity, "seq->size > seq->capacity");
}

/**
 * 初始化（创建）一个动态数组。
 * 
 * @param seq
 * @return 创建失败时返回 `true`，反之返回 `false`
 */
bool SequenceCreate(Sequence* seq)
{
  // 已经创建过的动态数组
  if (seq->space != NULL)
    return true;

  // 初始化为容量 1 动态数组
  seq->space = (int*) calloc(1u, sizeof(int));
  // 置配空间失败
  if (!seq->space) {
    _Error("Malloc failed.\n");
    return true;
  }
  seq->capacity = 1u;
  seq->size = 0u;

  __SequenceCheck(seq);
  return false;
}

/**
 * 往数组尾部添加元素。
 * 
 * @param seq
 * @param i 将要添加的元素
 * @return 添加成功时返回 `false`。
 *         通常情况下，只有不能再配置更多的连续内存空间时才会失败。
 */
bool SequencePush(Sequence* seq, int i)
{
  if (seq->size < seq->capacity) {
    seq->space[seq->size++] = i;
  }
  else if (seq->size == seq->capacity) {  // 空间不足
    // 准备两倍容量的新空间
    int* new_space = (int*) calloc(2u * seq->capacity, sizeof(int));
    if (!new_space) {   // 内存不足直接返回
      _Error("Malloc failed.\n");
      return true;
    }
    // 将原空间的内容拷贝到新空间中
    memcpy(new_space, seq->space, sizeof(int) * seq->capacity);
    // 释放原空间
    free(seq->space);
    // 挂载新空间
    seq->space = new_space;
    seq->capacity *= 2u;
    return SequencePush(seq, i);   // 递归调用 push 函数
  }

  __SequenceCheck(seq);
  return false;
}

/**
 * 在 `pos` 处插入元素。
 * 
 * @param seq
 * @param pos 插入位置。此后的元素后退
 * @param i 将要插入的元素
 * @return 插入成功时返回 `false`
 */
bool SequenceInsert(Sequence* seq, size_t pos, int i)
{
  // 如果插入的位置超出范围（insert 操作允许等于 size）
  if (pos > seq->size)
    return true;
  else if (pos == seq->size) {  // 特判
    return SequencePush(seq, i);
  }
  
  // `pos` 位置后的所有元素后移
  int tail = seq->space[seq->size - 1];
  // 反向拷贝数据
  for (size_t i = seq->size - 1; i != pos; --i) {
    seq->space[i] = seq->space[i-1];
  }
  // 将 `i` 插入 `pos` 位置
  seq->space[pos] = i;
  // 这里为了防止 size = capacity 需要重新分配空间的情况，我们先将
  // 原尾部的元素保存起来，并在现有的空间内完成元素插入，忽视最后一个
  // 元素，并在最后完成尾元素的插入。这样，即使是遇到了空间受限的情况，
  // 空间的重新分配也会委托给 push 函数，规避重复逻辑。
  return SequencePush(seq, tail);
}

/**
 * 移除（弹出）数组尾部的元素。
 * 
 * @param seq
 * @param pI 用于存放已被弹出的元素。若为 NULL 则不收集。
 * @return 弹出成功返回 `false`。
 *         通常情况下，只有数组中没有元素了才会弹出失败
 */
bool SequencePop(Sequence* seq, int* pI)
{
  if (seq->size == 0u)
    return true;
  
  if (pI != NULL) {
    *pI = seq->space[seq->size-1];
  }
  --seq->size;

  __SequenceCheck(seq);
  return false;
}

/**
 * 移除某一个位置的元素。
 * 
 * @param seq
 * @param pos 将要移除元素的位置
 * @param pI 同 pop 函数
 * @return 如果成功移除则返回 `false`
 */
bool SequenceRemoveAt(Sequence* seq, size_t pos, int* pI)
{
  if (pos >= seq->size)
    return true;
  
  // 安置 pI
  if (pI != NULL) {
    *pI = seq->space[pos];
  }
  
  // 执行拷贝
  memcpy(seq->space + pos, seq->space + pos + 1, 
         (seq->size - pos - 1u) * sizeof(int));
  // 执行序列长度减
  SequencePop(seq, NULL);

  __SequenceCheck(seq);
  return false;
}

/**
 * 创建一个动态数组的迭代器。
 * 本质为指针，且因为动态数组拥有连续内存空间，所以可以使用 `pointer[offsset]`
 * 这样的语法糖直接访问第 `offset` 位的元素。
 * 
 * @param seq
 * @return 返回首元素指针
 */
inline int* SequenceIterGenerate(Sequence* seq)
{
  return seq->space;
}

/**
 * 创建一个动态数组的常迭代器。
 * 
 * @param seq
 * @return 返回首元素指针
 */
inline const int* SequenceConstIterGenerate(Sequence* seq)
{
  return SequenceIterGenerate(seq);
}

/**
 * 压缩空闲空间。
 * 
 * @param seq
 */
void SequenceShrinkToFit(Sequence* seq)
{
  // 极限状态
  if (seq->size == seq->capacity)
    return ;
  // 否则就是有空闲空间
  // 创建恰好够的空间
  int* new_space = (int*) calloc(seq->size, sizeof(int));
  if (!new_space) {   // 内存不足直接返回
    _Error("Malloc failed.\n");
    return ;
  }
  memcpy(new_space, seq->space, seq->size * sizeof(int));
  free(seq->space);
  seq->space = new_space;
  seq->capacity = seq->size;
}

/**
 * 解散数组。
 * 
 * @param seq
 */
void SequenceDestruct(Sequence* seq)
{
  free(seq->space);
  seq->space = NULL;
  seq->capacity = seq->size = 0;
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
