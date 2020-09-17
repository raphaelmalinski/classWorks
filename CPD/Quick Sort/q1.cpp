#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

clock_t start_clock, end_clock;

void print_array(int C[], int tam)
{
	printf("[");
	for (int i = 0; i < tam - 1; i++)
	{
		printf("%d, ", C[i]);
	}
	printf("%d]", C[tam - 1]);
}

float left, right, max;

int partition_lomuto(int C[], int left, int right)
{
	int chave, i;
	chave = C[left];
	i = left + 1;
	int loopcount = 0;
	for (int j = left + 1; j <= right; j++)
	{
		//cout << "\nloop = " << loopcount++ << "i - " << i << " j = " << j << endl;
		if (C[j] < chave)
		{
			std::swap(C[i], C[j]);
			i++;
		}
	}
	std::swap(C[left], C[i - 1]);
	return i - 1;
}

int partition_hoare(int C[], int left, int right)
{
	int chave, i, j;
	chave = C[left];
	i = left - 1;
	j = right;
	int loopcount = 0;
	while (true)
	{
		while (C[j] > chave)
		{
			j--;
		}
		do
		{
			i++;
		} while (C[i] < chave);
		if (i >= j)
		{
			return j;
		}
		std::swap(C[i], C[j]);
	}
}

int partition_hoare_median(int C[], int left, int right)
{
	int chave, i, j;
	chave = C[(left + right) / 2];
	i = left - 1;
	j = right + 1;
	int loopcount = 0;
	while (true)
	{
		do
		{
			j--;
		} while (C[j] > chave);
		do
		{
			i++;
		} while (C[i] < chave);
		if (i >= j)
		{
			return j;
		}
		std::swap(C[i], C[j]);
	}
}

int partition_lomuto_random(int C[], int left, int right)
{
	int pivot, r;
	r = rand();
	pivot = left + r % (right - left + 1);
	std::swap(C[right], C[pivot]);
	return partition_lomuto(C, left, right);
}

void quick_sort_rec_lomuto(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		//Para testar o random, basta comentar o partition_lomuto e descomentar o partition_lomuto_random
		//pivot = partition_lomuto(C, left, right);
		pivot = partition_lomuto_random(C, left, right);
		quick_sort_rec_lomuto(C, left, pivot - 1);
		quick_sort_rec_lomuto(C, pivot + 1, right);
	}
}

void quick_sort_rec_hoare(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		//Para testar o median, basta comentar o partition_hoare e descomentar o partition_hoare_median
		//pivot = partition_hoare(C, left, right);
		pivot = partition_hoare_median(C, left, right);
		quick_sort_rec_lomuto(C, left, pivot);
		quick_sort_rec_lomuto(C, pivot + 1, right);
	}
}

void quick_sort_lomuto(int C[], int tam, int print_ok)
{
	if (print_ok)
	{
		printf("\nArray before:");
		print_array(C, tam);
	}
	start_clock = clock();
	quick_sort_rec_lomuto(C, 0, tam - 1);
	end_clock = clock();
	if (print_ok)
	{
		printf("\nArray after:");
		print_array(C, tam);
	}
	printf("\nQuick Sort time = %f seconds",
		   (end_clock - start_clock) / (double)CLOCKS_PER_SEC);
}

void quick_sort_hoare(int C[], int tam, int print_ok)
{
	if (print_ok)
	{
		printf("\nArray before:");
		print_array(C, tam);
	}
	start_clock = clock();
	quick_sort_rec_hoare(C, 0, tam - 1);
	end_clock = clock();
	if (print_ok)
	{
		printf("\nArray after:");
		print_array(C, tam);
	}
	printf("\nQuick Sort time = %f seconds",
		   (end_clock - start_clock) / (double)CLOCKS_PER_SEC);
}

#define SIZE 100

int main(int argc, const char *argv[])
{
	int arr1[10] = {12, 2, 5, 4, 8, 7, 6, 9, 1, 15};
	int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr3[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr4[SIZE];
	int arr5[SIZE];
	int arr6[SIZE];
	string chaves[1000];
	string cadeados[1000];

	ifstream arquivo_chaves;
	ifstream arquivo_cadeados;

	arquivo_chaves.open("chaves.txt");
	int i = 0;
	while (arquivo_chaves >> chaves[i++])
		;
	printf("\nRead %d chaves", i - 1);
	cout << chaves[0];

	arquivo_cadeados.open("cadeados.txt");
	int j = 0;
	while (arquivo_cadeados >> cadeados[j++])
		;
	printf("\nRead %d cadeados", j - 1);

	quick_sort_lomuto(arr1, 10, 1);
	quick_sort_lomuto(arr2, 10, 1);
	quick_sort_lomuto(arr3, 10, 1);

	quick_sort_hoare(arr1, 10, 1);
	quick_sort_hoare(arr2, 10, 1);
	quick_sort_hoare(arr3, 10, 1);

	// printf("\nWorst case");
	// for (int i = 0; i < SIZE; i++)
	// 	arr4[i] = SIZE - i;
	// quick_sort(arr4, SIZE, 0);

	// for (int j = 0; j < 10; j++)
	// {
	// 	for (int i = 0; i < SIZE; i++)
	// 		arr4[i] = rand() % SIZE + 1;
	// 	quick_sort(arr4, SIZE, 1);
	// 	cout << endl
	// 		 << endl;
	// }
	return 0;
}