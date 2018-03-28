#define _CRT_SECURE_NO_WARNINGS
#include "SeqList.h"

void InitSeqlist(pSeqList ps)
{
	ps->sz = 0;
	memset(ps->data, 0, MAX*sizeof(DataType));
}

void PushBack(pSeqList ps, DataType x)
{
	assert(ps != NULL);
	if (ps->sz == MAX)
	{
		return;
	}
	ps->data[ps->sz] = x;
	ps->sz++;
}
void PrintSeqlist(pSeqList ps)
{
	assert(ps != NULL);
	int i = 0;
	if (ps->sz == 0)
	{
		return;
	}
	for (i = 0; i < ps->sz; i++)
	{
		printf("%d ", ps->data[i]);
	}
	printf("\n");
}
void PopBack(pSeqList ps)
{
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	ps->sz--;
}
void PushFront(pSeqList ps, DataType x)
{
	assert(ps != NULL);
	if (ps->sz == MAX)
	{
		return;
	}
	memmove(ps->data+1, ps->data, (ps->sz)*sizeof(DataType));
	ps->data[0] = x;
	ps->sz++;
}
void PopFront(pSeqList ps)
{
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	memmove(ps->data, ps->data + 1, (ps->sz - 1)*sizeof(DataType));
	ps->sz--;
}
void Insert(pSeqList ps, int pos, DataType x)
{
	assert(ps != NULL);
	if (ps->sz == MAX)
	{
		return;
	}
	memmove(ps->data+pos+1, ps->data + pos, (ps->sz -pos)*sizeof(DataType));
	ps->data[pos] = x;
	ps->sz++;
}
int Find(pSeqList ps, DataType x)
{
	int i = 0;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return -1;
	}
	for (i = 0; i < ps->sz; i++)
	{
		if (ps->data[i] == x)
		{
			return i;
		}
	}
	return -1;
}
void Remove(pSeqList ps, DataType x)//指定删除
{
	int ret = -1;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	ret = Find((pSeqList)ps->data, x);
	if (ret != -1)
	{
		memmove(ps->data + ret, ps->data + ret + 1, (ps->sz - ret)*sizeof(DataType));
		ps->sz--;
	}
}
void RemoveAll(pSeqList ps, DataType x)
{
	int i = 0;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	for (i = 0; i < ps->sz; i++)
	{
		if (x == ps->data[i])
		{
			memmove(ps->data + i, ps->data + i + 1, (ps->sz - i)*sizeof(DataType));
			ps->sz--;
		}
	}
}
void ReverseList(pSeqList ps)
{
	int left = 0;
	int right = ps->sz-1;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	while (left < right)
	{
		int tmp = ps->data[left];
		ps->data[left] = ps->data[right];
		ps->data[right] = tmp;
		left++;
		right--;
	}

}
void SortList(pSeqList ps)
{
	int i = 0;
	int j = 0;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return;
	}
	for (i = 0; i < ps->sz-1; i++)
	{
		for (j = 0; j < ps->sz - i - 1; j++)
		{
			if (ps->data[j]>ps->data[j + 1])
			{
				int tmp = ps->data[j];
				ps->data[j] = ps->data[j+1];
				ps->data[j+1] = tmp;
			}
		}
	}
}
int BinarySearch(pSeqList ps, DataType x)
{
	int left = 0;
	int right = ps->sz - 1;
	int mid = 0;
	assert(ps != NULL);
	if (ps->sz == 0)
	{
		return -1;
	}
	while (left < right)
	{
		mid = left + (right - left)/2;
		if (ps->data[mid] > x)
		{
			right = mid - 1;
		}
		else if (ps->data[mid] < x)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}
