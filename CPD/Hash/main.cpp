#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>

using namespace std;

const int table_size_linear = 20000;      //tamanho de pelo menos o dobro do numero de chaves
const int table_size_double_hash = 12007; //tamanho da tabela sendo um númerdo primo (recomendado para duplo hash)
const int divider = 20011;                //menor número primo maior que o tamanho da tabela
const int fixed_value = 12007;            //número primo usado no método polinomial. Escolhido por apresentar o menor número de conflitos
const int division = 0;
const int polynomial = 1;

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
    return key_number;
}

//cria tabela de hash usando o metodo da divisão ou polinomial e resolve conflitos linearmente. Retorna número de colisões
int create_division_polynomial_linear_hash(key input[], char file_name[], int method = 0)
{
    int num_collisions = 0;
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
        switch (method)
        {
        case division:
            key = division_method(name_read);
            break;
        case polynomial:
            key = polynomial_method(name_read);
            break;
        default:
            key = division_method(name_read);
            break;
        }

        while (!inserted)
        {
            if (input[key].occupied)
            {
                num_collisions++;
                key = key + 1;
                while (key >= table_size_linear)
                {
                    key = key - table_size_linear;
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
    return num_collisions;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash. Retorna número de colisões
int create_division_double_hash(key input[], char file_name[])
{
    int num_collisions = 0;
    int key, key_aux, i;
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
                num_collisions++;
                key = key + i * polynomial_method(name_read) + i;
                i++;
                while (key >= table_size_double_hash)
                {
                    key = key - table_size_double_hash;
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
    return num_collisions;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash. Retorna o número de colisões
int create_polynomial_double_hash(key input[], char file_name[])
{
    int num_collisions = 0;
    int key, key_aux, i;
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
        key = polynomial_method(name_read);
        while (!inserted)
        {
            if (input[key].occupied)
            {
                num_collisions++;
                key = key + i * polynomial_method(name_read) + division_method(name_read);
                i++;
                while (key >= table_size_double_hash)
                {
                    key = key - table_size_double_hash;
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
    return num_collisions;
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos linear
int search_division_polynomial_linear_hash(key hash_table[], string name, int method = 0)
{
    int number_access = 0;
    // int key = division_method(name);
    int key;
    switch (method)
    {
    case division:
        key = division_method(name);
        break;
    case polynomial:
        key = polynomial_method(name);
        break;
    default:
        key = division_method(name);
        break;
    }

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
            if (key >= table_size_linear)
            {
                key = key - table_size_linear;
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
            if (key >= table_size_double_hash)
            {
                key = key - table_size_double_hash;
            }
        }
    }
    return -1;
}

//pesquisa na tabela de hash criada usando metodo polinomial com resolução de conflitos com duplo hash
int search_polynomial_double_hash(key hash_table[], string name)
{
    int i = 1;
    int number_access = 0;
    int key = polynomial_method(name);
    while (hash_table[key].used)
    {
        number_access++;
        if (to_lower(hash_table[key].content) == to_lower(name))
        {
            return number_access;
        }
        else
        {
            key = key + i * polynomial_method(name) + division_method(name);
            i++;
            if (key >= table_size_double_hash)
            {
                key = key - table_size_double_hash;
            }
        }
    }
    return -1;
}

float return_occupancy_rate(key hash_table[], int table_size)
{
    float num_of_occupations = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (hash_table[i].occupied)
        {
            num_of_occupations++;
        }
    }
    return num_of_occupations / table_size;
}

int lower_value(int values[], int list_size)
{
    int lower = INT_MAX;
    for (int i = 0; i < list_size; i++)
    {
        if (values[i] < lower)
        {
            lower = values[i];
        }
    }
    return lower;
}

int highest_value(int values[], int list_size)
{
    int highest = 0;
    for (int i = 0; i < list_size; i++)
    {
        if (values[i] > highest)
        {
            highest = values[i];
        }
    }
    return highest;
}

void consult_names_polynamial_double_hash(key hash_table[], char file_name[])
{
    int list_num_access[50], name_num_access, highest_value_access, lower_value_access;
    int i, j, num_access = 0;
    string not_found[50], found[50];
    string name_read, name_read_aux;
    ifstream input_file;
    ofstream output_file;

    output_file.open("files/result.txt", ios::out);
    input_file.open(file_name);
    while (input_file >> name_read)
    {
        input_file >> name_read_aux;
        name_read = name_read + " " + name_read_aux;
        name_num_access = search_polynomial_double_hash(hash_table, name_read);
        if (name_num_access != -1)
        {
            num_access = num_access + name_num_access;
            found[i] = name_read;
            list_num_access[i] = name_num_access;
            i++;
        }
        else
        {
            not_found[j] = name_read;
            j++;
        }
    }
    output_file << "Lista de nomes encontrados: \n";
    for (int k = 0; k < i; k++)
    {
        output_file << found[k] << "\n";
    }
    output_file << "Quantidade de nomes encontrados: " << i << "\n\n";

    output_file << "Lista de nomes não encontrados: \n";
    for (int k = 0; k < j; k++)
    {
        output_file << not_found[k] << "\n";
    }
    output_file << "Quantidade de nomes não encontrados: " << j << "\n\n";
    output_file << "Média de entradas verificadas: " << num_access / float(i) << "\n";
    
    highest_value_access = highest_value(list_num_access, i);
    output_file << "\nLista de nomes com mais acessos: " << highest_value_access <<  "\n";
    for (int k = 0; k < i; k++)
    {
        if (list_num_access[k] == highest_value_access)
        {
            output_file << found[k] << "\n";
        }
    }

    lower_value_access = lower_value(list_num_access, i);
    output_file << "\nLista de nomes com menos acessos: " << lower_value_access << "\n";
    for (int k = 0; k < i; k++)
    {
        if (list_num_access[k] == lower_value_access)
        {
            output_file << found[k] << "\n";
        }
    }
    input_file.close();
}

void print_hash(key hash[], int table_size)
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
    char file_name[50] = "files/nomes_10000.txt";
    char consult_file_name[50] = "files/consultas.txt";
    key input_linear[table_size_linear];
    key input_double_hash[table_size_double_hash];

    //Cria tabela hash com metodo da divisão e resolve conflitos de forma linear
    // cout << create_division_polynomial_linear_hash(input_linear, file_name, division);
    // cout << "\n" << search_division_polynomial_linear_hash(input_linear, "madoc Kolson");
    // cout << "\n"
    //      << return_occupancy_rate(input_linear, table_size_linear);

    //Cria tabela hash com metodo da divisão e resolve conflitos com duplo hash
    // cout << create_division_double_hash(input_double_hash, file_name);
    // cout << "\n" << search_division_double_hash(input_double_hash, "Madoc Kolson");
    // cout << "\n" << return_occupancy_rate(input_double_hash, table_size_double_hash);

    //Cria tabela hash com metodo polinomial e resolve conflitos de forma linear
    // cout << create_division_polynomial_linear_hash(input_linear, file_name, polynomial);
    // cout << "\n" << search_division_polynomial_linear_hash(input_linear, "Madoc Kolson", polynomial);
    // cout << "\n" << return_occupancy_rate(input_linear, table_size_linear);

    //Cria tabela hash com metodo polinomial e resolve conflitos com duplo hash
    cout << "Número de colisões: " << create_polynomial_double_hash(input_double_hash, file_name);
    cout << "\n"
         << search_polynomial_double_hash(input_double_hash, "mado Kolson");
    cout << "\n"
         << "Taxa de ocupação: " << return_occupancy_rate(input_double_hash, table_size_double_hash);
    consult_names_polynamial_double_hash(input_double_hash, consult_file_name);

    //print_hash(input_linear, table_size_linear);
    //print_hash(input_double_hash, table_size_double_hash);
    return 0;
}
