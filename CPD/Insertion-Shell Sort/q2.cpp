#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <math.h>

using namespace std;

void print_array(int C[], int tam)
{
	printf("[");
	for (int i = 0; i < tam - 1; i++)
	{
		printf("%d, ", C[i]);
	}
	printf("%d]", C[tam - 1]);
}

void shell_sort(int C[], int tam, int print_ok)
{
	long changes = 0;
	clock_t start, end;
	long double time_elapsed_ms;
	int k = 1;
	int aux, i, j;
	int h = tam / pow(2, k);
	if (print_ok)
	{
		cout << "\nArray before:";
		print_array(C, tam);
	}
	start = clock();
	while (h > 0)
	{
		i = h;
		while (i < tam)
		{
			aux = C[i];
			j = i;
			while (j >= h && aux < C[j - h])
			{
				C[j] = C[j - h];
				j = j - h;
				changes++;
			}
			C[j] = aux;
			i = i + 1;
		}
		k++;
		h = tam / pow(2, k);
	}

	end = clock();
	time_elapsed_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

	if (print_ok)
	{
		printf("\nArray after:");
		print_array(C, tam);
	}
	printf("\nShell Sort of %d elements: #changes = %ld - time = %10.4Lf ms", tam, changes, time_elapsed_ms);
}

void shell_sort_ciura(int C[], int tam, int print_ok)
{
	int ciura[10] = {0, 1, 4, 10, 23, 57, 132, 301, 701, 1750};
	long changes = 0;
	clock_t start, end;
	long double time_elapsed_ms;
	int k = 9;
	int aux, i, j;
	int h = ciura[k];
	if (print_ok)
	{
		cout << "\nArray before:";
		print_array(C, tam);
	}
	start = clock();
	while (h > 0)
	{
		if (tam / h >= 2)
		{
			i = h;
			while (i < tam)
			{
				aux = C[i];
				j = i;
				while (j >= h && aux < C[j - h])
				{
					C[j] = C[j - h];
					j = j - h;
					changes++;
				}
				C[j] = aux;
				i = i + 1;
			}
		}
		k--;
		h = ciura[k];
	}

	end = clock();
	time_elapsed_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

	if (print_ok)
	{
		printf("\nArray after:");
		print_array(C, tam);
	}
	printf("\nShell Sort with Ciura sequence of %d elements: #changes = %ld - time = %10.4Lf ms", tam, changes, time_elapsed_ms);
}

void copy_array(int *array_origem, int *array_destino, int size)
{
	for (int i = 0; i < size; i++)
		array_destino[i] = array_origem[i];
}

#define SIZE1 100
#define SIZE2 1000
#define SIZE3 10000
#define SIZE4 100000
#define NSIZES 4

int main()
{
	int arr_sizes[NSIZES] = {SIZE1, SIZE2, SIZE3, SIZE4};
	int arr_origem[SIZE4];
	int arr_destino[SIZE4];

	// Generate test arrays
	for (int j = 0; j < NSIZES; j++)
	{
		int size = arr_sizes[j];
		for (int i = 0; i < size; i++)
			arr_origem[i] = rand() % size + 1; // arr_size1[i] = SIZE1-i;

		copy_array(arr_origem, arr_destino, size);
		cout << "\n\nStarting Shell Sort" << flush;
		shell_sort(arr_destino, size, 0);
		cout << "\nEnd Shell Sort" << flush;

		copy_array(arr_origem, arr_destino, size);
		cout << "\n\nStarting Shell Sort with Ciura sequence" << flush;
		shell_sort_ciura(arr_destino, size, 0);
		cout << "\nEnd Shell Sort with Ciura sequence" << flush;
	}

	printf("\n\n");
}