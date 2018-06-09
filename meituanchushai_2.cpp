#include <iostream>
using namespace std;

int GetCount(int a[], int b[], int n)
{
	if (a == NULL || b == NULL || n <= 0)
		return 0;

	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i<n; i++)
		sum1 += a[i];
	for (int i = 0; i<n; i++)
		sum2 += b[i];
	if (sum1 != sum2)
		return 0;

	int count = 0;
	for (int i = 0; i<n; i++)
	{
		if (a[i] == b[i])
		{
			a[i] = 0;
			continue;
		}

		if (b[i] == 0)
			continue;
		int j = i;
		for (; j<n; j++)
		{
			if (a[j] == 0)
				continue;
			if (a[j] >= b[i])//已经足够了
			{
				count += a[j] * (j - i);
				a[j] -= b[i];
				break;
			}
			else
			{
				count += a[j] * (j - i);
				b[i] -= a[j];
				a[j] = 0;
			}
		}
		if (j != n)
			continue;
		for (int k = 0; k<n; k++)
		{
			if (a[k] == 0)
				continue;
			if (a[k] >= b[i])
			{
				count += a[k] * (k + i);
				a[k] -= b[i];
				break;
			}
			else//只够提供一部分
			{
				count += a[k] * (k + i);
				b[i] -= a[k];
				a[k] = 0;
			}
		}
	}
	return count;
}

int main()
{
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i<n; i++)
	{
		cin >> a[i];
	}
	int b[n];
	for (int i = 0; i<n; i++)
	{
		cin >> b[i];
	}

	int ret = GetCount(a, b, n);
	cout << ret << endl;
	return 0;
}
