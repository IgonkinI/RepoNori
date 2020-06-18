#define N 10 // Размер матрицы
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
	
	// Здесь мы определяем сумму координат центра матрицы, в зависимости, если она
	// четная или нечетная.
	if (N%2 == 0){
		mid = N/2 + N/2 - 2;
	} else	{

		mid = N/2 + N/2 - 1;
	}
	
	printf("\nМатрица %d x %d \nВерхний треугольник 0 \nНижний треугольник 1 \n", N,N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			

// Сравниваем, выше ли главной диагонали находятся ячейки
			if (i + j <= mid)
			{
				array3[i][j] = 0;
			}
			else {
				array3[i][j] = 1;
			}
			printf("%d\t",array3[i][j] );
		}
		printf("\n");
	}
	
//Заполнение массива улиткой 
printf("\nМатрица %d x %d заполненная по улитке\n",N,N );

	int array4[N][N];
	int i=1;
	int j;
	int step;
	int numOfStep=N/2;
// Сначала мы вычисляем количество шагов, за которые мы обойдем всю матрицу.
// Потом идем до границ матрицы (по периметру) и заполняем ячейки.
// Когда мы пройдем четыре направления, цикл повторяется, на последнем шаге
// мы заполняем центральную ячейку.
	for(step=1;step<=numOfStep;step++)
	{

		for (j=step-1;j<N-step+1;j++) // Идем вправо.
		{
			array4[step-1][j]=i++;  
		}
		
		for (j=step;j<N-step+1;j++) // Идем вниз
		{ 
			array4[j][N-step]=i++;
		}
		
		for (j=N-step-1;j>=step-1;--j) // Идем влево, снизу
		{	
			array4[N-step][j]=i++;
		}
		
		for (j=N-step-1;j>=step;j--) // Идем вверх слева
		{
			array4[j][step-1]=i++;
		}
	}
	

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("\t%d\t ",array4[i][j]);
		} 
		printf("\n");
	}

return 0;
}