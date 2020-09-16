#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

char **get_input_dnas(int num_dnas, int length_dna)
{
    char **list_dnas;
    list_dnas = new char *[num_dnas];
    for (int i = 0; i < num_dnas; i++)
    {
        list_dnas[i] = new char[length_dna];
        cin >> list_dnas[i];
    }
    return list_dnas;
}

int measure_sorted(char *dna, int length_dna)
{
    int measure_value = 0;
    for (int i = 0; i < length_dna - 1; i++)
    {
        for (int j = i + 1; j < length_dna; j++)
        {
            if (dna[j] < dna[i])
                measure_value++;
        }
    }
    return measure_value;
}

int *measure_sorted_list(char **list_dnas, int length_dna, int num_dnas)
{
    int *measure_list = new int[num_dnas];
    for (int i = 0; i < num_dnas; i++)
    {
        measure_list[i] = measure_sorted(list_dnas[i], length_dna);
    }
    return measure_list;
}

void insertion_sort(int *measure_list, int num_dnas, char **list_dnas, int length_dna)
{
    int i, j, chave;
    char *aux_dna = new char[length_dna];

    for (j = 1; j < num_dnas; j++)
    {
        chave = measure_list[j];
        aux_dna = list_dnas[j];
        i = j - 1;
        while ((i >= 0) && (measure_list[i] > chave))
        {
            measure_list[i + 1] = measure_list[i];
            list_dnas[i + 1] = list_dnas[i];
            i--;
        }
        measure_list[i + 1] = chave;
        list_dnas[i + 1] = aux_dna;
    }
}

int binary_search(int *measure_list, int low, int high, int key)
{
    int mid;

    if (low == high)
        return low;

    mid = low + ((high - low) / 2);

    if (key > measure_list[mid])
        return binary_search(measure_list, mid + 1, high, key);
    else if (key < measure_list[mid])
        return binary_search(measure_list, low, mid, key);

    return mid;
}

void insertion_binary_sort(int *measure_list, int num_dnas, char **list_dnas, int length_dna)
{
    int j, chave;
    int insertion_place;
    char *aux_dna = new char[length_dna];

    for (j = 1; j < num_dnas; j++)
    {
        insertion_place = binary_search(measure_list, 0, j, measure_list[j]);
        chave = measure_list[j];
        aux_dna = list_dnas[j];
        // Movimenta elementos para direita
        for (int k = j - 1; k >= insertion_place; k--)
        {
            measure_list[k + 1] = measure_list[k];
            list_dnas[k + 1] = list_dnas[k];
        }
        measure_list[insertion_place] = chave;
        list_dnas[insertion_place] = aux_dna;
    }
}

void shell_sort(int *measure_list, int num_dnas, char **list_dnas, int length_dna)
{
    int k = 1;
    int aux, i, j;
    int h = num_dnas / pow(2, k);
    char *aux_dna = new char[length_dna];

    while (h > 0)
    {
        i = h;
        while (i < num_dnas)
        {
            aux = measure_list[i];
            aux_dna = list_dnas[i];
            j = i;
            while (j >= h && aux < measure_list[j - h])
            {
                measure_list[j] = measure_list[j - h];
                list_dnas[j] = list_dnas[j - h];
                j = j - h;
            }
            measure_list[j] = aux;
            list_dnas[j] = aux_dna;
            i = i + 1;
        }
        k++;
        h = num_dnas / pow(2, k);
    }
}

int main()
{
    int num_lists;
    cin >> num_lists;
    int length_dna[num_lists], num_dnas[num_lists];
    char **list_dnas[num_lists];
    int *measure_list[num_lists];

    for (int i = 0; i < num_lists; i++)
    {
        cout << "\n";
        cin >> length_dna[i] >> num_dnas[i];
        list_dnas[i] = get_input_dnas(num_dnas[i], length_dna[i]);
        measure_list[i] = measure_sorted_list(list_dnas[i], length_dna[i], num_dnas[i]);
        //shell_sort(measure_list[i], num_dnas[i], list_dnas[i], length_dna[i]);
        insertion_sort(measure_list[i], num_dnas[i], list_dnas[i], length_dna[i]);
        //insertion_binary_sort(measure_list[i], num_dnas[i], list_dnas[i], length_dna[i]);
    }
    cout << "\n";
    for (int i = 0; i < num_lists; i++)
    {
        for (int j = 0; j < num_dnas[i]; j++)
        {
            cout << list_dnas[i][j];
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}
