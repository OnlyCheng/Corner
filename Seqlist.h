#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 10//数组元素个数

typedef int DataType;//数组元素类型重命名

typedef struct SeqList
{
	DataType data[MAX];//创建一个数组
	int sz;     //用于记住元素的个数
}SeqList,*pSeqList;

void InitSeqlist(pSeqList ps);//初始化函数
void PushBack(pSeqList ps, DataType x);//从后边添加的函数
void PrintSeqlist(pSeqList ps);//打印数组的函数
void PopBack(pSeqList ps);//从后往前删除的函数
void PushFront(pSeqList ps, DataType x);//从前边添加的函数
void PopFront(pSeqList ps);//从前往后删除的函数
void Insert(pSeqList ps, int pos, DataType x);//指定位置添加的函数
int Find(pSeqList ps, DataType x);//查找函数
void Remove(pSeqList ps, DataType x); //删除指定某个数的函数
void RemoveAll(pSeqList ps, DataType x);//删除所有的指定的某个值的函数
void ReverseList(pSeqList ps);//逆序函数
void SortList(pSeqList ps);//排序函数
int BinarySearch(pSeqList ps, DataType x);//二分查找函数

#endif
