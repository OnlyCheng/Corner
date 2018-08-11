#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> arr(m);
	for (int i = 0; i<m; i++)
	{
		cin >> arr[i];
	}
	vector<int> score(n);
	for (int i = 0; i<m; i++)
	{
		score[arr[i] - 1]++;
	}
	int min = 0;
	int flag = 0;
	for (int i = 0; i<n; i++)
	{
		if (flag == 0)
		{
			min = score[i];
			flag = 1;
		}
		if (min < score[i])
			min = score[i];
	}
	cout << min << endl;
	return 0;
}
