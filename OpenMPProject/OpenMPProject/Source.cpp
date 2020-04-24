//#include<math.h>
//#include <stdio.h>
//#include <omp.h>
//#define M 2
//#define N 49
//
//inline void eratosthenes_seq(int last) {
//	int* deletionsMatrix = new int[last + 1];
//	int solution[N / 2] = { 0 };
//
//	int iterator = 0;
//
//	for (int i = 0; i <= last; i++)
//		deletionsMatrix[i] = 1;
//	for (int i = 2; i * i <= last; i++)
//		if (deletionsMatrix[i])
//			for (int j = i * i; j <= last; j += i)
//				deletionsMatrix[j] = 0;
//	for (int i = 2; i <= last; i++)
//	{
//		if (i >= M && deletionsMatrix[i]) solution[iterator++] = i;
//	}
//
//	int found = 0;
//	for (int i = 0; i < N / 2 && solution[i] != 0; i++)
//	{
//		if (i % 10 == 0) printf("\n");
//		found = i + 1;
//		printf("%d;", solution[i]);
//	}
//	printf("\nfound %d numbers", found);
//
//	delete[] deletionsMatrix;
//}
//
//int main()
//{
//	eratosthenes_seq(N);
//}
//
//	