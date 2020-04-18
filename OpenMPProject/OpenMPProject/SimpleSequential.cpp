#include<math.h>
#include <stdio.h>
#define M 4
#define N 21370


int main1()
{
	for (int i = M; i < N; i++)
	{
		bool hasDivider = false;
		for (int j = 2; j < sqrt(i); j++)
		{
			if (i % j == 0)
			{
				hasDivider = true;
				break;
			}
		}
		if (!hasDivider)
			printf("%d\n", i);
	}
}