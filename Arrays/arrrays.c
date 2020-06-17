#define N 3 // Размер матрицы
#include <stdio.h>

int main()
{


// Задание квадратной матрицы размера N
	unsigned int num = 0;
	int array1[N][N];
	printf("Квадратная матрица размером %d x %d\n\n",N,N );
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			array1[i][j] = num;
			num++;
		}
	
	}

// Вывод на экран квадратной матрицы размера N
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			printf("%d\t",array1[i][j] );
		}
	printf("\n");
	}

//Вывод на экран массива длинной в N
	int array2[N];
	for (int i = 0; i < N; ++i)
	{
		array2[i] = i;
	}
	printf("\n\nМассив длиной %d\n\n", N);
	for (int i = 0; i < N; ++i)
	{
		printf("%d\t",array2[i]);
	}
	printf("\nЭтот же массив, но в обратном порядке\n");
	for (int i = N-1; i >= 0; i--)
	{
		printf("%d\t",array2[i] );
	}



	// Заполнение x треугольной матрицы N*N и вывод этой матрицы
	int array3[N][N];
	int mid = 0;
	if (N%2 == 0){
		mid = N/2 + N/2 - 1;
	} else	{

		mid = N/2 + N/2;
	}
	
	printf("\nМатрица %d x %d \nВерхний треугольник 1 \nНижний треугольник 0 \n", N,N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			


			if (i + j <= mid)
			{
				array3[i][j] = 1;
			}
			else {
				array3[i][j] = 0;
			}
			printf("%d\t",array3[i][j] );
		}
		printf("\n");
	}
	
//Заполнение массива улиткой еще в процессе создания :)
int array4[N][N];

int firstLine = N - 1;
int firstColumn = N -1;



	return 0;
}