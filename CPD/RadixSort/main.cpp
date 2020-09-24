#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

//Foi usada a versão LSD do radix sort devido a maior facilidade de implementação 
//do algoritmo. A versão MSD seria mais indicada nesse problema porque evitaria 
//execuções de código desnecessárias, mas devido essa maior facilidade do código,
//foi optado pelo LSD.

size_t get_bigger_string_length(string arr[], int size)
{
    size_t bigger = arr[0].size();
    for (int i = 1; i < size; i++)
    {
        if (arr[i].size() > bigger)
            bigger = arr[i].size();
    }
    return bigger;
}

void count_sort(string arr[], int size, size_t digit)
{
    string *arr_aux = NULL;
    int *c = NULL;
    arr_aux = new string[size];
    c = new int[257];

    for (int i = 0; i < 257; i++)
    {
        c[i] = 0;
    }

    for (int j = 0; j < size; j++)
    {
        c[digit < arr[j].size() ? (int)(unsigned char)arr[j][digit] + 1 : 0]++;
    }

    for (int k = 1; k < 257; k++)
    {
        c[k] += c[k - 1];
    }

    for (int l = size - 1; l >= 0; l--)
    {
        arr_aux[c[digit < arr[l].size() ? (int)(unsigned char)arr[l][digit] + 1 : 0] - 1] = arr[l];
        c[digit < arr[l].size() ? (int)(unsigned char)arr[l][digit] + 1 : 0]--;
    }
    
    for (int m = 0; m < size; m++)
    {
        arr[m] = arr_aux[m];
    }

    delete[] arr_aux;
    delete[] c;
}

void radixSort(string arr[], int size)
{
    size_t bigger = get_bigger_string_length(arr, size);
    for (size_t digit = bigger; digit > 0; digit--)
    {
        count_sort(arr, size, digit - 1);
    }
}

int read_input_file(string input[], char file_name[])
{
    int num_words = 0;
    int i = 0;
    ifstream input_file;

    input_file.open(file_name);
    while (input_file >> input[i++])
    {
        num_words++;
    }
    input_file.close();

    return num_words;
}

void write_output_file(string input[], char file_name[], int size)
{
    int i = 0;
    ofstream output_file;

    output_file.open(file_name, ios::out);

    radixSort(input, size);

    for (int l = 0; l < size; l++)
    {
        output_file << input[l];
        output_file << ' ';
    }
}

void write_dataset_file(string input[], char file_name[], int size)
{
    int num_occurrences = 1;
    string word;
    ofstream dataset_file;

    word = input[0];
    dataset_file.open(file_name, ios::out);
    for (int i = 1; i < size; i++)
    {
        if (word == input[i])
        {
            num_occurrences++;
        }
        else
        {
            dataset_file << word << ' ' << num_occurrences << endl;
            word = input[i];
            num_occurrences = 1;
        }
    }
}

int main()
{
    char input_frankestein_file[50] = "inputs/frankestein.txt";
    char output_frankestein_file[50] = "outputs/frankestein_ordenado.txt";
    char dataset_frankestein_file[50] = "datasets/frankestein_dataset.txt";

    char input_war_and_peace_file[50] = "inputs/war_and_peace.txt";
    char output_war_and_peace_file[50] = "outputs/war_and_peace_ordenado.txt";
    char dataset_war_and_peace_file[50] = "datasets/war_and_peace_dataset.txt";

    //frankestein
    string *input_frankestein_arr = new string[100000];
    int size = read_input_file(input_frankestein_arr, input_frankestein_file);
    write_output_file(input_frankestein_arr, output_frankestein_file, size);
    write_dataset_file(input_frankestein_arr, dataset_frankestein_file, size);

    //war_and_peace
    string *input_war_and_peace_arr = new string[600000];
    size = read_input_file(input_war_and_peace_arr, input_war_and_peace_file);
    write_output_file(input_war_and_peace_arr, output_war_and_peace_file, size);
    write_dataset_file(input_war_and_peace_arr, dataset_war_and_peace_file, size);

    return 0;
}