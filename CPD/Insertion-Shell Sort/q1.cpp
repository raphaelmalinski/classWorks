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
		cout << "\nAfter increments of size " << h << " the list is";
		print_array(C, tam);
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
	printf("\nShell Sort of %d elements: #changes = %ld - time = %10.4Lf ms\n", tam, changes, time_elapsed_ms);
}

int main()
{
	int arr1[10] = {12, 2, 5, 4, 8, 7, 6, 9, 1, 15};
	int arr2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int arr3[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	int arr4[15] = {733, 77, 611, 51, 496, 990, 61, 175, 127, 794, 794, 76, 197, 141, 863};
    int arr5[20] = {872, 424, 729, 573, 877, 696, 321, 758, 949, 217, 767, 238, 562, 175, 999, 12, 380, 406, 225, 995};
	int arr6[9] = {54, 26, 93, 17, 77, 31, 44, 55, 20};

	shell_sort(arr1, 10, 1);
	shell_sort(arr2, 10, 1);
	shell_sort(arr3, 10, 1);
	shell_sort(arr4, 15, 1);
	shell_sort(arr5, 20, 1);
	shell_sort(arr6, 9, 1);
	
	printf("\n\n");
}