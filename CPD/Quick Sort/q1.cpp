#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

clock_t start_clock, end_clock;
double lomuto_random_statistics[3] = {0.0, 0.0, 0.0};
double lomuto_median_statistics[3] = {0.0, 0.0, 0.0};
double hoare_random_statistics[3] = {0.0, 0.0, 0.0};
double hoare_median_statistics[3] = {0.0, 0.0, 0.0};

float left, right, max;

int create_random_pivot(int left, int right)
{
	int pivot, r;
	r = rand();
	pivot = left + r % (right - left + 1);
	return pivot;
}

int median_3(int a, int b, int c)
{
	if (a < b)
	{
		if (b < c)
		{
			return b;
		}
		else
		{
			if (a < c)
				return c;
			else
				return a;
		}
	}
	else
	{
		if (c < b)
		{
			return b;
		}
		else
		{
			if (c < a)
				return c;
			else
				return a;
		}
	}
}

int partition_lomuto_random(int C[], int left, int right)
{
	int chave, i;
	std::swap(C[left], C[create_random_pivot(left, right)]);
	lomuto_random_statistics[0]++;
	chave = C[left];
	i = left + 1;
	int loopcount = 0;
	for (int j = left + 1; j <= right; j++)
	{
		if (C[j] < chave)
		{
			std::swap(C[i], C[j]);
			lomuto_random_statistics[0]++;
			i++;
		}
	}
	std::swap(C[left], C[i - 1]);
	lomuto_random_statistics[0]++;
	return i - 1;
}

int partition_lomuto_median(int C[], int left, int right)
{
	int chave, i;
	std::swap(C[left], C[median_3(left, (left + right) / 2, right)]);
	lomuto_median_statistics[0]++;
	chave = C[left];
	i = left + 1;
	int loopcount = 0;
	for (int j = left + 1; j <= right; j++)
	{
		if (C[j] < chave)
		{
			std::swap(C[i], C[j]);
			lomuto_median_statistics[0]++;
			i++;
		}
	}
	std::swap(C[left], C[i - 1]);
	lomuto_median_statistics[0]++;
	return i - 1;
}

int partition_hoare_random(int C[], int left, int right)
{
	int chave, i, j;
	std::swap(C[(left + right) / 2], C[create_random_pivot(left, right)]);
	hoare_random_statistics[0]++;
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
		hoare_random_statistics[0]++;
	}
}

int partition_hoare_median(int C[], int left, int right)
{
	int chave, i, j;
	std::swap(C[(left + right) / 2], C[median_3(left, (left + right) / 2, right)]);
	hoare_median_statistics[0]++;
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
		hoare_median_statistics[0]++;
	}
}

void quick_sort_rec_lomuto_random(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		lomuto_random_statistics[1] = lomuto_random_statistics[1] + 2;
		pivot = partition_lomuto_random(C, left, right);
		quick_sort_rec_lomuto_random(C, left, pivot - 1);
		quick_sort_rec_lomuto_random(C, pivot + 1, right);
	}
}

void quick_sort_rec_lomuto_median(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		lomuto_median_statistics[1] = lomuto_median_statistics[1] + 2;
		pivot = partition_lomuto_median(C, left, right);
		quick_sort_rec_lomuto_median(C, left, pivot - 1);
		quick_sort_rec_lomuto_median(C, pivot + 1, right);
	}
}

void quick_sort_rec_hoare_random(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		hoare_random_statistics[1] = hoare_random_statistics[1] + 2;
		pivot = partition_hoare_random(C, left, right);
		quick_sort_rec_hoare_random(C, left, pivot);
		quick_sort_rec_hoare_random(C, pivot + 1, right);
	}
}

void quick_sort_rec_hoare_median(int C[], int left, int right)
{
	int pivot; // índice do pivô
	if (right > left)
	{
		hoare_median_statistics[1] = hoare_median_statistics[1] + 2;
		pivot = partition_hoare_median(C, left, right);
		quick_sort_rec_hoare_median(C, left, pivot);
		quick_sort_rec_hoare_median(C, pivot + 1, right);
	}
}

void quick_sort_lomuto(int C[], int tam, char *option)
{
	if (option == "random")
	{
		start_clock = clock();
		quick_sort_rec_lomuto_random(C, 0, tam - 1);
		end_clock = clock();
		lomuto_random_statistics[2] = (end_clock - start_clock) / (double)CLOCKS_PER_SEC;
	}
	else
	{
		start_clock = clock();
		quick_sort_rec_lomuto_median(C, 0, tam - 1);
		end_clock = clock();
		lomuto_median_statistics[2] = (end_clock - start_clock) / (double)CLOCKS_PER_SEC;
	}
}

void quick_sort_hoare(int C[], int tam, char *option)
{
	if (option == "random")
	{
		start_clock = clock();
		quick_sort_rec_hoare_random(C, 0, tam - 1);
		end_clock = clock();
		hoare_random_statistics[2] = (end_clock - start_clock) / (double)CLOCKS_PER_SEC;
	}
	else
	{
		start_clock = clock();
		quick_sort_rec_hoare_median(C, 0, tam - 1);
		end_clock = clock();
		hoare_median_statistics[2] = (end_clock - start_clock) / (double)CLOCKS_PER_SEC;
	}
}

void write_lomuto_output(int *entrada, int tam, char *option)
{
	int i, j, *arr;
	int k = 1;
	int l = 0;
	ofstream arquivo_saida;
	if (option == "random")
	{
		arquivo_saida.open("saidas/saida-aleatorio-lomuto.txt", ios::out);
	}
	else
	{
		arquivo_saida.open("saidas/saida-mediana3-lomuto.txt", ios::out);
	}
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
		quick_sort_lomuto(arr, tam, option);
		while (l < tam)
		{
			arquivo_saida << arr[l];
			arquivo_saida << ' ';
			l++;
		}
		l = 0;
		arquivo_saida << "\n";
	}
}

void write_hoare_output(int *entrada, int tam, char *option)
{
	int i, j, *arr;
	int k = 1;
	int l = 0;
	ofstream arquivo_saida;
	if (option == "random")
	{
		arquivo_saida.open("saidas/saida-aleatorio-hoare.txt", ios::out);
	}
	else
	{
		arquivo_saida.open("saidas/saida-mediana3-hoare.txt", ios::out);
	}
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
		quick_sort_hoare(arr, tam, option);
		while (l < tam)
		{
			arquivo_saida << arr[l];
			arquivo_saida << ' ';
			l++;
		}
		l = 0;
		arquivo_saida << "\n";
	}
}

void write_statistics_lomuto(char *option)
{
	ofstream lomuto_statistics_file;
	if (option == "random")
	{
		lomuto_statistics_file.open("estatisticas/stats-aleatorio-lomuto.txt", ios::out);
		lomuto_statistics_file << "Número de swaps: " << (int)lomuto_random_statistics[0] << "\n";
		lomuto_statistics_file << "Número de chamadas recursivas: " << (int)lomuto_random_statistics[1] << "\n";
		lomuto_statistics_file << "Tempo de execução: " << lomuto_random_statistics[2] << "\n";
	}
	else
	{
		lomuto_statistics_file.open("estatisticas/stats-mediana3-lomuto.txt", ios::out);
		lomuto_statistics_file << "Número de swaps: " << (int)lomuto_median_statistics[0] << "\n";
		lomuto_statistics_file << "Número de chamadas recursivas: " << (int)lomuto_median_statistics[1] << "\n";
		lomuto_statistics_file << "Tempo de execução: " << lomuto_median_statistics[2] << "\n";
	}
}

void write_statistics_hoare(char *option)
{
	ofstream hoare_statistics_file;
	if (option == "random")
	{
		hoare_statistics_file.open("estatisticas/stats-aleatorio-hoare.txt", ios::out);
		hoare_statistics_file << "Número de swaps: " << (int)hoare_random_statistics[0] << "\n";
		hoare_statistics_file << "Número de chamadas recursivas: " << (int)hoare_random_statistics[1] << "\n";
		hoare_statistics_file << "Tempo de execução: " << hoare_random_statistics[2] << "\n";
	}
	else
	{
		hoare_statistics_file.open("estatisticas/stats-mediana3-hoare.txt", ios::out);
		hoare_statistics_file << "Número de swaps: " << (int)hoare_median_statistics[0] << "\n";
		hoare_statistics_file << "Número de chamadas recursivas: " << (int)hoare_median_statistics[1] << "\n";
		hoare_statistics_file << "Tempo de execução: " << hoare_median_statistics[2] << "\n";
	}
}

void lomuto(int *entrada, int tam, char *option)
{
	write_lomuto_output(entrada, tam, option);
	write_statistics_lomuto(option);
}

#define SIZE 100

int main(int argc, const char *argv[])
{
	int *entrada, *arr;
	int tam;
	int i = 0;
	ifstream arquivo_entrada;

	entrada = new int[1000000];
	arr = new int[1000000];
	arquivo_entrada.open("entradas/entrada.txt");
	while (arquivo_entrada >> entrada[i++])
		;

	arr = entrada;
	write_lomuto_output(arr, tam, "random");
	write_statistics_lomuto("random");

	arr = entrada;
	write_lomuto_output(arr, tam, "median");
	write_statistics_lomuto("median");

	arr = entrada;
	write_hoare_output(arr, tam, "random");
	write_statistics_hoare("random");

	arr = entrada;
	write_hoare_output(arr, tam, "median");
	write_statistics_hoare("median");

	return 0;
}