#include <iostream>
#include <algorithm>
using namespace std;
#include <vector>
struct pos
{
	int _x;
	int _y;
};
int main()
{
	int n;
	scanf("%d", &n);
	vector<pos> v(n);
	for (int i = 0; i<n; i++)
	{
		scanf("%d %d", &v[i]._x, &v[i]._y);
		if (i != n - 1)
			getchar();
	}
	long long x_max = v[0]._x;
	long long x_min = v[0]._x;
	long long y_max = v[0]._y;
	long long y_min = v[0]._y;
	int sum = 0;

	for (int i = 1; i<n; i++)
	{
		if (v[i]._x > x_max)
			x_max = v[i]._x;
		if (v[i]._x < x_min)
			x_min = v[i]._x;
		if (v[i]._y > y_max)
			y_max = v[i]._y;
		if (v[i]._y < y_min)
			y_min = v[i]._y;
	}

	long long nx = x_max - x_min;
	long long ny = y_max - y_min;
	long long len = max(nx, ny);
	sum = len*len;
	cout << sum << endl;
	return 0;
}
