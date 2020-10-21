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
        value_c = word[i];
        value = value + value_c;
    }
    return value;
}

string to_lower(string string)
{
    for (int i = 0; i < string.length(); i++)
    {
        string[i] = tolower(string[i]);
    }
    return string;
}

//funções de hash escolhidas - divisão e polinomial
int division_method(string key)
{
    string key_temp = to_lower(key);
    int key_number = convert_string_to_int(key_temp) % divider;
    if (key_number >= table_size)
    {
        key_number = key_number - table_size;
    }
    return key_number;
}

//método usado encontra-se no link https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm
int polynomial_method(string key)
{
    string key_temp = to_lower(key);
    int key_number = tolower(key_temp[0]);
    for (int i = 1; i < key_temp.length(); i++)
    {
        key_number = ((key_number * 256) % fixed_value + key_temp[i]) % fixed_value;
    }
    if (key_number >= table_size)
    {
        key_number = key_number - table_size;
    }
    return key_number;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos linearmente
void create_division_linear_hash(key input[], char file_name[])
{
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
                if (key >= table_size)
                {
                    key = key - table_size;
                }
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

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash
void create_division_double_hash(key input[], char file_name[])
{
    int i;
    int key, key_aux;
    bool inserted;
    string name_read, name_read_aux;
    ifstream input_file;

    input_file.open(file_name);
    while (input_file >> name_read)
    {
        i = 1;
        inserted = false;
        input_file >> name_read_aux;
        name_read = name_read + " " + name_read_aux;
        key = division_method(name_read);
        while (!inserted)
        {
            if (input[key].occupied)
            {

                key = key + i * polynomial_method(name_read) + i;
                i++;
                if (key >= table_size)
                {
                    key = key - table_size;
                }
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

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos linear
int search_division_linear_hash(key hash_table[], string name)
{
    int number_access = 0;
    int key = division_method(name);
    while (hash_table[key].used)
    {
        number_access++;
        if (to_lower(hash_table[key].content) == to_lower(name))
        {
            return number_access;
        }
        else
        {
            key++;
            if (key >= table_size)
            {
                key = key - table_size;
            }
        }
    }
    return -1;
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_division_double_hash(key hash_table[], string name)
{
    int i = 1;
    int number_access = 0;
    int key = division_method(name);
    while (hash_table[key].used)
    {
        number_access++;
        if (to_lower(hash_table[key].content) == to_lower(name))
        {
            return number_access;
        }
        else
        {
            key = key + i * polynomial_method(name) + i;
            i++;
            if (key >= table_size)
            {
                key = key - table_size;
            }
        }
    }
    return -1;
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
    string word = "Anarely Anirvin";
    //int key = division_method(word);
    // int key = polynomial_method(word);
    // cout << key;
    // int i = convert_string_to_int(word);
    char file_name[50] = "files/nomes_10000.txt";
    key input[table_size];
    //create_division_linear_hash(input, file_name);
    //cout << search_division_linear_hash(input, "Eban Nikita");
    create_division_double_hash(input, file_name);
    cout << search_division_double_hash(input, "Madoc Kolson");
    //print_hash(input);
    return 0;
}
