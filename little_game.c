#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	int j = 0;
	int x = 5;
	int y = 10;

	int height = 20;
	int velocity = 1;

	while (1)
	{
		x += velocity;
		system("cls");

		for (i = 0; i < x; i++)
		{
			printf("\n");
		}

		for (j = 0; j < y; j++)
		{
			printf(" ");
		}

		printf("O");
		printf("\n");

		if (x == height)
		{
			velocity = -velocity;
		}
		if (x == 0)
		{
			velocity = -velocity;
		}
	}
	return 0;
}
