﻿#include<math.h>
#include <stdio.h>
#include <omp.h>
#include <vector>
#define M 2
#define N 137000
#define NUM_THREADS 1
# define lenght (N - 1) / 2 + 1

inline int generatePrimeNumbersArray(int solution[]) {
	int last = sqrt(N);
	int* deletionsMatrix = new int[last + 1];

	int iterator = 0;

	for (int i = 0; i <= last; i++)
		deletionsMatrix[i] = 1;
	for (int i = 2; i * i <= last; i++)
		if (deletionsMatrix[i])
			for (int j = i * i; j <= last; j += i)
				deletionsMatrix[j] = 0;
	for (int i = 3; i <= last; i++)
	{
		if (deletionsMatrix[i])
			solution[iterator++] = i;
	}
	delete[] deletionsMatrix;
	return iterator;
}

// sito z podejsciem funckyjnym 1 -> wygenerowana sekwencyjnie macierz liczb pierwszych
inline void function_method() {
	char* deletionsMatrix = new char[lenght];
	int solution[N / 2] = { 0 };
	int primeNumbersArray[N / 2] = { 0 };
	int primeNumbersArrayLength = generatePrimeNumbersArray(primeNumbersArray);
	for (int i = 0; i < lenght; i++)
		deletionsMatrix[i] = 1;

	omp_set_num_threads(NUM_THREADS);
	int id = 0;
	int start_num = 0;
	int left, right = 0;
	int fragmentLenght = primeNumbersArrayLength / NUM_THREADS;
	int restOfNumbers = primeNumbersArrayLength % NUM_THREADS;
	if (fragmentLenght == 0)
	{
		for (int i = 0; fragmentLenght <= 0; i++)
			fragmentLenght = primeNumbersArrayLength / (NUM_THREADS - i);
		restOfNumbers = 0;

	}
	int* primeNumbersArrayPartial = new int[restOfNumbers + fragmentLenght];

	printf("%d\n", fragmentLenght);
#pragma omp parallel private(id, left, right)
	{
		id = omp_get_thread_num();
		left = fragmentLenght * id;
		right = fragmentLenght * (id + 1);
		if (id == NUM_THREADS - 1) right += restOfNumbers;
		std::copy(primeNumbersArray + left, primeNumbersArray + right, primeNumbersArrayPartial);
		printf("%d:<%d,%d)\n", id, left, right);

		for (int i = left; i < right; i++)
		{
			for (int j = 3; primeNumbersArrayPartial[i - left] * j <= N; j += 2)
			{
				if (primeNumbersArrayPartial[i - left] * j > left)
				{
					deletionsMatrix[primeNumbersArrayPartial[i - left] * j / 2] = 0;
					//if(id == 0)
					//printf("%d:wykreslam %d * %d = %d\n", id, primeNumbersArrayPartial[i - left], j, primeNumbersArrayPartial[i - left] * j);
				}
			}
		}

	}

	solution[0] = 2;
	int found = 0;
	int iterator = M == 2 ? 1 : 0;
	for (int i = M / 2; i <= (N - 1) / 2; i++)
	{
		if (i >= M / 2 && deletionsMatrix[i]) solution[iterator++] = 2 * i + 1;
	}
	for (int i = 0; i < N / 2 && solution[i] != 0; i++)
	{
		if (i % 10 == 0) printf("\n");
		found = i + 1;
		printf("%d;", solution[i]);
	}
	delete[] deletionsMatrix;
	printf("\nfound %d numbers", found);
}

int main()
{
	function_method();
}