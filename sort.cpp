#pragma once
#include <iostream>
using namespace std;
#include <assert.h>

void BubbleSort(int* array , int size)
{
	for(int i = 0;i < size - 1;i++)
	{
		for(int j = 0;j < size - i - 1 ; j++)
		{
			if(array[j]>array[j+1])
				swap(array[j],array[j+1]);
		}
	}
}

void print(int* array,int size)
{
	for(int i = 0;i < size ;i++)
	{
		cout<<array[i]<<" ";
	}
	cout<<endl;
}

void InsertSort(int* array , int size)
{
	for(int i = 1;i < size;i++)
	{
		//compare and insert to the right position
		for(int j = i ; j > 0; j--)
		{
			if(array[j] < array[j-1])
			{
				swap(array[j],array[j-1]);
			}
			else
				break;
		}
	}
}

void ShellSort(int* array , int size)
{
	int gap = 0;
	while(gap < size)
	{
		gap = gap*3 + 1;
	}

	for(;gap > 0;gap /= 3)
	{
		for(int i = 1; i < size; i++)
		{
			for(int j = i - gap;j >= 0;j -= gap)
			{
				if(array[j+gap]<array[j])
					swap(array[j+gap],array[j]);
				else
					break;
			}
		}
	}
}

void ChoseSort(int* array,int size)
{
	int min = 0;
	for(int i = 0; i<size; i++)
	{
		int min = i;
		for(int j = i;j<size; j++)
		{
			if(array[min]>array[j])
				min = j;
		}
		swap(array[i],array[min]);
	}
}

void AdjustDown(int* array,int size ,int parent)
{	
	int child = parent*2 +1;
	while(child<size)
	{
		child = parent*2+1;
		if(child > size)
			return;
		if(child+1 < size)
		{
			if(array[child] < array[child+1])
				child += 1;
		}

		if(array[child] > array[parent])
		{
			swap(array[child],array[parent]);
			parent = child;
			child = parent*2 + 1;
		}
		else
			break;
	}
}

void CreatHeap(int* array,int size)
{
	int parent = (size-2)>>1;
	for(int i = parent ; i >= 0;i--)
	{
		AdjustDown(array,size,i);
	}
}

void HeapSort(int* array,int size)
{
	CreatHeap(array,size);
	
	while(size>1)
	{
		swap(array[0],array[size-1]);
		size--;
		AdjustDown(array,size,0);
	}
}

int GetMidPos(int* array,int left,int right)
{
	assert(array);
	assert(left <= right);

	if(left+1 == right)
		return left;

	int mid = left+((right-left)>>1);
	if(array[left]<array[right-1])
	{
		if(array[mid]<array[left])
			return left;
		else if(array[mid]>array[right-1])
			return right-1;
		else
			return mid;
	}
	else
	{
		if(array[mid] > array[left])
			return left;
		else if(array[mid] < array[right-1])
			return right-1;
		else
			return mid;
	}
}


void QuickSort1(int* array,int left, int right)
{
	int pos = GetMidPos(array,left,right);
	if(left+1 >= right)
		return;

	if(pos != right-1)
		swap(array[pos],array[right-1]);
	
	int key = array[right-1];
	int front = left ;
	int back = right - 1;

	while(front < back)
	{
		while(front < back)
		{
			if(array[front]>key)
				break;
			front++;
		}

		while(front < back)
		{
			if(array[back]<key)
				break;
			back--;
		}

		if(front < back)
			swap(array[front],array[back]);
	}
	swap(array[front],array[right-1]);

	QuickSort1(array,left,back);
	QuickSort1(array,front,right);
}

void QuickSort2(int* array, int left, int right)
{
	int pos = GetMidPos(array,left,right);
	if(left+1 >= right)
		return;

	if(pos != right-1)
		swap(array[pos],array[right-1]);
	
	int key = array[right-1];
	int front = left ;
	int end = right - 1;
	
	while(front < end)
	{
		while(front < end)
		{
			if(array[front] > key)
				break;
			front++;
		}

		if(front < end)
			array[end] = array[front];

		while(front < end)
		{
			if(array[end] < key)
				break;
			end--;
		}

		if(front < end)
			array[front] = array[end];
	}
	array[front] = key;

	QuickSort2(array, left ,end);
	QuickSort2(array, front , right);
}

void QuickSort3(int* array, int left, int right)
{
	int pos = GetMidPos(array,left,right);
	if(left+1 >= right)
		return;

	if(pos != right-1)
		swap(array[pos],array[right-1]);
	
	int key = array[right-1];
	int cur = left ;
	int pre = left - 1;

	while(cur < right-1)
	{
		while(array[cur] < key)
		{
			cur++;
			pre++;
		}

		while(array[cur] > key)
		{
			cur++;
		}
			
		while(pre+1 != cur && array[cur] < key)
		{
			swap(array[++pre],array[cur++]);
		}
	}
	swap(array[++pre],array[right-1]);
	
	QuickSort3(array, left, pre);
	QuickSort3(array, pre+1,right);
}


int Getmin(int* array, int size)
{
	int min = array[0];
	for(int i = 0; i < size; i++)
	{
		if(array[i] < min)
			min = array[i];
	}
	return min;
}

int Getmax(int* array, int size)
{
	int max = array[0];
	for(int i = 0; i < size; i++)
	{
		if(array[i] > max)
			max = array[i];
	}
	return max;
}

void CountSort(int* array, int size)
{
	int min = Getmin(array,size);
	int max = Getmax(array,size);
	
	const int len = max-min+1;
	int* count = new int[len];

	for(int i = 0;i < size; i++)
	{
		count[array[i]-min]++;
	}

	int index = 0;
	for(int i = 0; i < len; i++)
	{
		while(count[i]--)
		{
			array[index++] = i + min;
		}
	}
	delete[] count;
}


