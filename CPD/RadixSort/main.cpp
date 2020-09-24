#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

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

void countSort(string a[], int size, size_t k)
{
    string *b = NULL;
    int *c = NULL;
    b = new string[size];
    c = new int[257];

    //initializing arr
    for (int i = 0; i < 257; i++)
    {
        c[i] = 0;
    }
    for (int j = 0; j < size; j++)
    {
        c[k < a[j].size() ? (int)(unsigned char)a[j][k] + 1 : 0]++; //a[j] is a string
                                                                    //cout << c[j] << endl;
    }

    for (int f = 1; f < 257; f++)
    {
        c[f] += c[f - 1];
    }

    for (int r = size - 1; r >= 0; r--)
    {
        b[c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0] - 1] = a[r];
        c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++)
    {
        a[l] = b[l];
    }

    // avold memory leak
    delete[] b;
    delete[] c;
}

void radixSort(string b[], int size)
{
    size_t bigger = get_bigger_string_length(b, size);
    for (size_t digit = bigger; digit > 0; digit--)
    {
        countSort(b, size, digit - 1);
    }
}

int read_input_file(string input[], char file_name[])
{
    int num_words, i = 0;
    ifstream input_file;

    input_file.open(file_name);
    while (input_file >> input[i++]){
        num_words++;
    }

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


int main(/*int argc, char const *argv[]*/)
{
    string *input = new string[1000000];
    char input_file_name[50] = "inputs/war_and_peace_clean.txt";
    char output_file_name[50] = "outputs/output.txt";

    int size = read_input_file(input, input_file_name);
    write_output_file(input, output_file_name, size);

    return 0;
}