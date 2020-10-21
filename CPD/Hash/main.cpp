#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

static int table_size = 12000;
static int divider = 12007;   //smaller prime number bigger than the number of keys plus 20%
static int fixed_value = 101; //prime number used in polynomial method

struct key
{
    //int key;
    string content;
    bool used = false;
    bool occupied = false;
};
typedef struct key key;

int convert_string_to_int(string word)
{
    int value = 0;
    int value_c;
    for (int i = 0; i < word.length(); i++)
    {
        value_c = tolower(word[i]);
        value = value + value_c;
    }
    return value;
}

//hash functions
int division_method(string key)
{
    int key_number = convert_string_to_int(key) % divider;
    if (key_number >= table_size)
    {
        key_number = key_number - table_size;
    }
    return key_number;
}

//method in https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
int polynomial_method(string key)
{
    int key_number = tolower(key[0]);
    for (int i = 1; i < key.length(); i++)
    {
        key_number = ((key_number * 256) % fixed_value + key[i]) % fixed_value;
    }
    if (key_number >= table_size)
    {
        key_number = key_number - table_size;
    }
    return key_number;
}

void create_division_linear_hash(key input[], char file_name[])
{
    int i = 0;
    int key;
    bool inserted;
    string name_read, name_read_aux;
    ifstream input_file;

    input_file.open(file_name);
    while (input_file >> name_read)
    {
        inserted = false;
        input_file >> name_read_aux;
        name_read = name_read + " " + name_read_aux;
        key = division_method(name_read);
        while (!inserted)
        {
            if (input[key].occupied)
            {
                key = key + 1;
            }
            else
            {
                input[key].content = name_read;
                input[key].occupied = true;
                input[key].used = true;
                inserted = true;
            }
        }
    }
    input_file.close();
}

void print_hash(key hash[])
{
    int j = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (hash[i].occupied)
        {
            cout << hash[i].content << "\n";
            j++;
        }
    }
    cout << "Number of keys: " << j << "\n";
}

int main(int argc, char const *argv[])
{
    string word = "raphael";
    //int key = division_method(word);
    //int key = polynomial_method(word);
    //cout << key;
    // int i = convert_string_to_int(word);
    char file_name[50] = "files/nomes_10000.txt";
    key input[table_size];
    create_division_linear_hash(input, file_name);
    print_hash(input);
    return 0;
}
