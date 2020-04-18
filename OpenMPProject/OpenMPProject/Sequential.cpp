#include<math.h>
#include <stdio.h>
#include <vector>
#define M 4
#define N 21370


int main()
{
	std::vector<int> primeNumbers;
	primeNumbers.push_back(2);
	for (int i = 3; i < N; i++)
	{
		bool hasDivider = false;
		for (int j = 0; j < primeNumbers.size() && primeNumbers[j] <= sqrt(i); j++)
		{
			if (i % primeNumbers[j] == 0)
			{
				hasDivider = true;
				break;
			}
		}
		if (!hasDivider)
		{
			primeNumbers.push_back(i);
			if (i >= M)
			{
				printf("%d\n", i);
			}
		}
	}
}