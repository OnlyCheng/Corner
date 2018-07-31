程序说明
本程序主要分为三大模块：
一、标准输入获取道路网络的行和列、道路网络的连通定义以及验证他们的合法性。
二、根据道路网络及其连通定义，获取渲染网格（将原来是墙但是根据连通定义需要修改为道路的地方进行修改）。
三、将渲染网格以指定的方式打印出来。
程序测试
对题中给出的样例进行了验证，程序得出了正确的结果。除此之外，程序还能正确处理其他合法的样例，并对非法输入也做了防御性编程。
程序具体内容

#include<iostream>
using namespace std;
#include<vector>
#include<string>

class Maze
{
public:
	Maze(int _n, int _m, string _str)   //构造函数，初始化成员
		:n(2 * _n + 1)
		, m(2 * _m + 1)
		, str(_str)
	{
		Map.resize(n);                  //将渲染网格初始化成全0
		for (int i = 0; i < n; i++)
		{
			Map[i].resize(m, 0);
		}
		for (int i = 1; i < n; i = i+2) //隔行隔列初始化道路
		{
			for (int j = 1; j < m; j = j+2)
			{
				Map[i][j] = 1;          //将道路初始化为1
			}
		}
	}
	void Print()     //打印渲染网格
	{
		if (Insert() == false)				//更改渲染网格，将通路连接
			return;
		for (int i = 0; i < n; i++)         //两层循环，遍历渲染网格
		{
			for (int j = 0; j < m; j++)
			{
				if (Map[i][j] == 0)
					cout << "[W]" << " ";   //打印墙壁
				else if (Map[i][j] == 1)
					cout << "[R]" << " ";   //打印路径
			}
			cout << endl;
		}
		cout << endl;
	}
private:
	bool Insert()                //更改渲染网格
	{
		int x = -1, y = -1;      //定义两个变量，保存第一个坐标信息
		int x2 = -1, y2 = -1;    //定义两个变量，保存第二个坐标信息
		int size = str.size();
		int i = 0;
		while (i<size)
		{
			if (str[i] >= '0'&&str[i] <= '9')
			{
				if (x == -1 && y == -1)
					x = 2 * (str[i] - '0') + 1;     //获取x的值
				else if (y == -1)
					y = 2 * (str[i] - '0') + 1;     //获取y的值
				else if (x2 == -1 && y2 == -1)
					x2 = 2 * (str[i] - '0') + 1;    //获取x2的值
				else if (y2 == -1)
					y2 = 2 * (str[i] - '0') + 1;    //获取y2的值
			}
			else if (str[i] == ';')					//当为';'时，重置(x,y)(x2,y2)
			{
				x = -1, y = -1;
				x2 = -1, y2 = -1;
			}
			if (x != -1 && y != -1 && x2 != -1 && y2 != -1)    //判断是否所有坐标都已赋值
			{
				int min = 0;
				int max = 0;
				if (x == x2)
				{
					min = y < y2 ? y : y2;    //取较小的值
					max = y>y2 ? y : y2;      //取较大的值
					if (max - min != 2)       //两个坐标不连通
					{
						cout << "Maze format error." << endl;
						return false;
					}
					Map[x][min + 1] = 1;
				}
				else if (y == y2)
				{
					min = x < x2 ? x : x2;    //取较小的值
					max = x>x2 ? x : x2;      //去较大的值
					if (max - min != 2)       //两个坐标不连通
					{
						cout << "Maze format error." << endl;
						return false;
					}
					Map[min + 1][y] = 1;
				}
				else						 //两个坐标不连通
				{
					cout << "Maze format error." << endl;
					return false;
				}
			}
			i++;
		}
		return true;          //插入成功
	}
private:
	vector<vector<int>> Map;     //渲染网格
	int n;                       //渲染网格的行数
	int m;                       //渲染网格的列数
	string str;                  //保存输入的下标信息
};
bool JudgeInput(string str, int n, int m)      //判断输入的坐标是否有效
{
	int size = str.size();      //输入字符的个数
	int i = 0;
	int flag = 0;               //标记在一个坐标中逗号是否出现，且只能出现一次
	while (i<size)
	{
		if (i == 0)
		{
			while (i<size&&str[i] == ' ')		   //跳过首部的空格
				i++;
		}
		if (i<size&&str[i] >= '0'&&str[i] <= '9')  //判断是否是数字，数字是否超范围
		{
			string temp;
			while (i < size&&str[i] >= '0'&&str[i] <= '9')   //获取数字字母
			{
				temp.push_back(str[i]);
				i++;
			}
			if (i < size && flag == 0 && str[i] != ',')      //输入的字符无法转成数字   
			{
				cout << "Invalid number format." << endl;
				return false;
			}
			int num = atoi(temp.c_str());          //将子符串转换成整形数字
			if (flag == 0 && (num < 0 || num >= n))
			{
				cout << "Number out of range." << endl;
				return false;
			}
			else if (flag == 1 && (num < 0 || num >= m))
			{
				cout << "Number out of range." << endl;
				return false;
			}
		}
		else if (str[i] == ','&&flag == 0)
		{
			i++;
			flag = 1;
		}
		else if (i < size&&str[i] == ' ' && (str[i + 1] >= '0'&&str[i + 1] <= '9'))    //判断两个坐标之间的一个空格
		{
			i++;
			flag = 0;    //一个坐标判断完毕，将falg置0
		}
		else if (i < size&&str[i] == ';' && (str[i + 1] >= '0'&&str[i + 1] <= '9'))   //判断一组坐标后的分号
		{
			i++;
			flag = 0;    //一组坐标判断完毕，将falg置0
		}
		else
		{
			cout << "Invalid number format." << endl;
			return false;
		}
	}
	return true;
}
bool JudgeNM(string nm, int* n, int* m)   //判断输入的行和列是否有效
{
	int size = nm.size();   //获取字符串个数
	if (size == 0)          //字符串为空
	{
		cout << "Incorrect command format." << endl;
		return false;
	}
	int i = 0;         //计数变量
	int flag = 0;      //标记第几个数字，0是第一个
	while (i < size)
	{
		if (i == 0)
		{
			while (i < size&&nm[i] == ' ')           //跳过首部所有的空格
				i++;
			if (i < size && (nm[i]<'0' || nm[i]>'9'))//输入的行列不是数字
			{
				cout << "Incorrect command format." << endl;
				return false;
			}
		}

		if (i<size&&nm[i] >= '0'&&nm[i] <= '9')	//提取数字字符
		{
			string cur;							//定义一个字符串来保存数字字符
			while (i < size&&nm[i] >= '0'&&nm[i] <= '9') //将第一个数字分离出来
			{
				cur.push_back(nm[i]);
				i++;
			}
			if (i < size&&nm[i] != ' ')         //判断下一个字符是否时空格，若不是，无效的数字
			{
				cout << "Invalid number format." << endl;
				return false;
			}
			int num = atoi(cur.c_str());        //将字符串转换成数字
			if (num == 0)
			{
				cout << "Invalid number format." << endl;
				return false;
			}
			if (flag == 0)     //表示当前数字为第一个数字
			{
				*n = num;
				flag = 1;
			}
			else               //为第二个数字
				*m = num;
		}
		else if (i<size&&nm[i] == ' '&&nm[i + 1] != ' ')     //两个数字中的空格有且只有一个空格
		{
			i++;
		}
		else                   //输入格式不正确
		{
			cout << "Incorrect command format." << endl;
			return false;
		}
	}
	return true;
}
int main()
{
	int n = 0, m = 0;
	string nm;    //以字符串形式接收行和列
	while (1)     //获取道路网格序列
	{
		getline(cin, nm);     //获取第一行字符
		if (JudgeNM(nm, &n, &m) == false)       //判断第一行的数字是否有效
			continue;
		fflush(stdin);             //刷新输入缓冲区
		string str;
		getline(cin, str);         //获取第二行的数字是否有效
		if (JudgeInput(str, n, m) == false)        //判断第二行的输入是否有效
			continue;
		Maze M(n, m, str);         //创建迷宫对象
		M.Print();                 //调用成员函数打印渲染网格
	}

	return 0;
}
