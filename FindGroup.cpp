#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>


void dig(vector<vector<int> >& v, int i, int j, int& count)
{
	if (v[i][j] == 0)
		return;
	++count;
	v[i][j] = 0;
	int row = v.size();
	int col = v[0].size();
	if (j + 1 < col)  //向右
		dig(v, i, j + 1, count);
	if (i - 1 >= 0)      //向上
		dig(v, i - 1, j, count);
	if (j - 1 >= 0)   //向左
		dig(v, i, j - 1, count);
	if (i + 1 < row)    //向下
		dig(v, i + 1, j, count);
	if (i + 1<row && j + 1<col)   //向右下
		dig(v, i + 1, j + 1, count);
	if (i - 1 >= 0 && j + 1<col)    //向右上
		dig(v, i - 1, j + 1, count);
	if (i - 1 >= 0 && j - 1 >= 0)   //向左上
		dig(v, i - 1, j - 1, count);
	if (i + 1<row && j - 1 >= 0)   //向左下
		dig(v, i + 1, j - 1, count);

}

int main()
{
	int M, N;
	string MN;
	getline(cin, MN);
	string t;
	for (int i = 0; i < MN.size(); i++)
	{
		if (MN[i] >= '0' && MN[i] <= '9')
		{
			t += MN[i];
			if (i == MN.size() - 1)
				N = atoi(t.c_str());
			else if (MN[i + 1] == ',')
			{
				M = atoi(t.c_str());
				t = "";
			}
		}
	}
	vector<string> inv(M);
	for (int i = 0; i < M; i++)
	{
		getline(cin, inv[i]);
	}
	//解析放入v中
	vector<vector<int> > v(M);
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < inv[i].size(); j++)
		{
			if (inv[i][j] <= '9' && inv[i][j] >= '0')
				v[i].push_back(inv[i][j] - '0');
		}
	}
	int sum = 0;
	int max = 0;
	int count = 0;

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (v[i][j] == 0)
				continue;
			dig(v, i, j, count);
			++sum;
			if (count > max)
				max = count;
			count = 0;
		}
	}
	cout << sum <<","<< max << endl;
	return 0;
}
