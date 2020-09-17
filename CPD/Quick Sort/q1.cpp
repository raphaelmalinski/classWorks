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
		pivot = partition_lomuto(C, left, right);
		//pivot = partition_lomuto_random(C, left, right);
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
		pivot = partition_hoare(C, left, right);
		//pivot = partition_hoare_median(C, left, right);
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
	int *entrada, *arr;
	int tam, j;
	int k = 1;	int i, l = 0;
	ifstream arquivo_entrada;
	ofstream arquivo_saida;

	entrada = new int[10000000];
	arquivo_entrada.open("entradas/entrada-mini.txt");
	arquivo_saida.open("saidas/saida.txt", ios::out);
	while (arquivo_entrada >> entrada[i++])
		;

	arquivo_saida << entrada[0];
	arquivo_saida << "\n";
	for (i = 1; i <= entrada[0]; i++)
	{
		tam = entrada[k];
		arquivo_saida << entrada[k];
		arquivo_saida << ' ';
		k++;
		j = 0;
		arr = new int[tam];
		while (j < tam)
		{
			arr[j] = entrada[k];
			j++;
			k++;
		}
		//quick_sort_lomuto(arr, tam, 1);
		quick_sort_hoare(arr, tam, 1);
		while (l < tam)
		{
			arquivo_saida << arr[l];
			arquivo_saida << ' ';
			l++;
		}
		l = 0;
		arquivo_saida << "\n";
	}

	// arquivo_cadeados.open("cadeados.txt");
	// int j = 0;
	// while (arquivo_cadeados >> cadeados[j++])
	// 	;
	return 0;
}