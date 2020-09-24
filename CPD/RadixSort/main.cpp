#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void alloc_array(char **arr)
{
    arr = new char *[1000];
    for (int i = 0; i < 1000; i++)
    {
        arr[i] = new char[30];
    }
}

void print_array(char arr[][30])
{
    int i = 0;
    while (arr[i][0] != '\n')
    {
        cout << arr[i] << " ";
        i++;
    }
}


size_t getMax(string arr[], int n){
    size_t max = arr[0].size();
    for (int i = 1; i < n; i++){
        if (arr[i].size()>max)
            max = arr[i].size();
    }
    return max;
}

void countSort(string a[], int size, size_t k){
    string *b = NULL; int *c = NULL;
    b = new string[size];
    c = new int[257];



    for (int i = 0; i <257; i++){
        c[i] = 0;
        //cout << c[i] << "\n";
    }
    for (int j = 0; j <size; j++){   
        c[k < a[j].size() ? (int)(unsigned char)a[j][k] + 1 : 0]++;            //a[j] is a string
        //cout << c[a[j]] << endl;
    }

    for (int f = 1; f <257; f++){
        c[f] += c[f - 1];
    }

    for (int r = size - 1; r >= 0; r--){
        b[c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0] - 1] = a[r];
        c[k < a[r].size() ? (int)(unsigned char)a[r][k] + 1 : 0]--;
    }

    for (int l = 0; l < size; l++){
        a[l] = b[l];
    }

    // avold memory leak
    delete[] b;
    delete[] c;
}


void radixSort(string b[], int r){
    size_t max = getMax(b, r);
    for (size_t digit = max; digit > 0; digit--){ // size_t is unsigned, so avoid using digit >= 0, which is always true
        countSort(b, r, digit - 1);
    }

}

void read_input_file(char input[][30], char file_name[])
{
    int i = 0;
    ifstream input_file;

    input_file.open(file_name);
    while (input_file >> input[i++])
        ;
    input[i][0] = '\n';
}

void write_output_file(char input[][30], char file_name[])
{
    int i = 0;
    ofstream output_file;

    output_file.open(file_name, ios::out);

    //do here the sort
    radixSort(input, 10000)

    while (input[i][0] != '\n')
    {
        output_file << input[i];
        output_file << ' ';
        i++;
    }
}




int main(/*int argc, char const *argv[]*/)
{
    char input[100000][30];
    char input_file_name[50] = "inputs/input.txt";
    char output_file_name[50] = "outputs/output.txt";

    read_input_file(input, input_file_name);
    write_output_file(input, output_file_name);
    //print_array(input);

    return 0;
}