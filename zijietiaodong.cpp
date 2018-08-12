#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>
#include <string>

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

bool cmp(Interval l, Interval r)
{
	if (l.start == r.start)
		return l.end < r.end;
	else
		return l.start<r.start;
}

vector<Interval> merge(vector<Interval> &intervals) 
{
	vector<Interval> res;
	int size = intervals.size();
	if (size == 0)
		return res;
	sort(intervals.begin(), intervals.end(), cmp);
	for (int i = 0; i<size; i++)
	{
		if (res.empty())
			res.push_back(intervals[i]);
		else
		{
			Interval last = res.back();
			if (last.end < intervals[i].start)
				res.push_back(intervals[i]);
			else//need  Merge
			{
				res.pop_back();
				last.end = max(last.end, intervals[i].end);
				res.push_back(last);
			}
		}
	}
	return res;
}

int main()
{
	int m;
	cin >> m;
	getchar();
	vector<string> v(m);
	for (int i = 0; i < m; i++)
	{
		getline(cin, v[i]);
	}

	//按行解析各个区间存放于一个vector中
	vector<Interval> inters;
	for (int i = 0; i < m; i++)
	{
		string s = v[i];
		int size = s.size();
		int start = 0;
		int end = 0;
		string str;
		for (int i = 0; i < size; i++)
		{
			if (s[i] >= '0' && s[i] <= '9')
			{
				str += s[i];
				if (i == size - 1 || s[i + 1] == ';')//最后一个字符或者后边是分号
				{
					end = atoi(str.c_str());//将string转换为整型
					Interval interval = Interval(start, end);
					inters.push_back(interval);
					str = "";
				}	
				else if (s[i + 1] == ',')
				{
					start = atoi(str.c_str());
					str = "";
				}
			}
		}
	}
	vector<Interval> ret = merge(inters);
	for (int i = 0; i < (int)ret.size(); i++)
	{
		if (i == (int)ret.size()-1)
			cout << ret[i].start << "," << ret[i].end;
		else
			cout << ret[i].start << "," << ret[i].end << ";";
	}
	return 0;
}
