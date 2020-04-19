#include<math.h>
#include <stdio.h>
#define M 2
#define N 49


int generatePrimeNumbersArray(int numbers[]) {
	int iterator = 0;
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
		if (!hasDivider) {
			numbers[iterator] = i;
			++iterator;
		}
	}
	return iterator;
}

bool checkIsNumberPrimeWithArray(int primeNumbers[], int iterator, int number) {
	for (int i = 0; i < iterator; i++) {
		if (number % primeNumbers[i] == 0 && primeNumbers[i] < number)
		{
			return false;
		}
	}
	return true;
}

bool checkDivisionBySmallerNumbers(int number) {
	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int data[N / 2] = { 0 };
	int iterator = generatePrimeNumbersArray(data);
	for (int i = M; i < N; i++) {
		//if (checkIsNumberPrimeWithArray(data, iterator, i)) { // with array
		if(checkDivisionBySmallerNumbers(i)){ // division by smaller number
			printf("Prime number: %d\n", i);
		}
	}
}