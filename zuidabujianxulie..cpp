#include <iostream>
using namespace std;
#include <vector>
#include<cstdio>
#include<algorithm>

int sam_arr[40005];
int d[40005];
int main()
{
	int n, t;
	scanf("%d %d", &n, &t);
	vector<int> sample(n);
	for (int i = 0; i<n; i++)
		scanf("%d", &sample[i]);

	if (n == 0)
	{
		printf("0\n");
		return 0;
	}
	//构造一个新的数组
	int index = 1;
	for (int i = 0; i<t; i++)
	{
		for (int j = 0; j<n; j++)
		{
			sam_arr[index++] = sample[j];
		}
	}
	int size = n*t;
	d[1] = sam_arr[1];  //初始化 
	int len = 1;
	for (int i = 2; i <= size; i++)
	{
		if (sam_arr[i] >= d[len])
			d[++len] = sam_arr[i];
		else
		{
			int j = upper_bound(d + 1, d + len + 1, sam_arr[i]) - d;
			d[j] = sam_arr[i];
		}
	}

	printf("%d\n", len);
	return 0;
}
