#include<math.h>
#include <stdio.h>
#include <omp.h>
#define M 2
#define N 490
#define NUM_THREADS 4
# define lenght (N - 1) / 2 + 1

int generatePrimeNumbersArray(int numbers[]) {
	int iterator = 0;
	for (int i = 3; i <= sqrt(N); i++)
	{
		bool hasDivider = false;
		for (int j = 2; j <= sqrt(i); j++)
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

// sito z podejsciem funckyjnym 1 -> wygenerowana sekwencyjnie macierz liczb pierwszych
inline void domain_method() {
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
	if(fragmentLenght == 0)
	{
		for (int i = 0; fragmentLenght <= 0; i++)
			fragmentLenght = primeNumbersArrayLength / (NUM_THREADS-i);
		restOfNumbers = 0;

	}

	printf("%d\n", fragmentLenght);
#pragma omp parallel private(id, left, right)
	{
		id = omp_get_thread_num();
		left = fragmentLenght * id;
		right = fragmentLenght * (id + 1);
		if (id == NUM_THREADS - 1) right += restOfNumbers;
		//printf("%d:<%d,%d)\n", id, left, right);

			for (int i = left; i < right; i++)
			{
				for (int j = 3; primeNumbersArray[i] * j <= N; j += 2)
				{
					if (primeNumbersArray[i] * j > left)
					{
						deletionsMatrix[primeNumbersArray[i] * j / 2] = 0;
						//printf("%d:wykreslam %d * %d = %d\n", id, primeNumbersArray[i], j, primeNumbersArray[i] * j);
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
	domain_method();
}