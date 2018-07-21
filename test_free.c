#include <iostream>
using namespace std;
#include <stdio.h>

void test()
{
	char* p = (char*)malloc(100);
	strcpy(p, "hello");
	free(p);
	if (p != NULL)
	{
		strcpy(p, "world");
		printf(p);//虽然访问了已经释放的空间，但还是会正常输出world
	}
}

int main()
{
	test();
	return 0;
}
