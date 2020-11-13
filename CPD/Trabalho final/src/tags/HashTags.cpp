#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int hash_tags_size = 700001; //tamanho da tabela sendo um númerdo primo (recomendado para duplo hash)
const int divider_tags = 500009;   //menor número primo maior que o tamanho da tabela

struct Tag
{
    string tag;
    vector<int> moviesAssociated;
    bool used = false;
    bool occupied = false;
};
typedef struct Tag Tag;

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

//funções de hash escolhidas - divisão e polinomial
int division_method_tag(string key)
{
    string key_temp = to_lower(key);
    int key_number = convert_string_to_int(key_temp) % divider_tags;
    return key_number;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash. Retorna número de colisões
void insert_tag_to_hash(Tag hash[], Tag tag)
{
    int key;
    int i = 1;
    bool inserted = false;
    string tag_temp = tag.tag;

    key = division_method_tag(tag_temp);

    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method_tag(tag_temp) + i;
            i++;
            while (key >= hash_tags_size)
            {
                key = key - hash_tags_size;
            }
        }
        else
        {
            hash[key].tag = tag.tag;
            hash[key].moviesAssociated = tag.moviesAssociated;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_tag_in_hash(Tag hash[], string tag)
{
    int tag_converted;
    int i = 1;

    int key = division_method_tag(tag);
    while (hash[key].used)
    {
        if (to_lower(hash[key].tag) == to_lower(tag))
        {
            return key;
        }
        else
        {
            key = key + i * division_method_tag(tag) + i;
            i++;
            // if (key >= hash_size)
            // {
            //     key = key - hash_size;
            // }
            while (key >= hash_tags_size)
            {
                key = key - hash_tags_size;
            }
        }
    }
    return -1;
}

void print_tags_hash(Tag hash[], int table_size)
{
    int j = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (hash[i].occupied)
        {
            cout << "Tag: " << hash[i].tag << " | "
                 << "Movies Id's: ";
                 
            for (vector<int>::iterator it = hash[i].moviesAssociated.begin(); it != hash[i].moviesAssociated.end(); it++)
            {
                cout << *it << ", ";
            }
            j++;
            cout << endl;
        }
    }
    cout << endl << "Number of keys: " << j << "\n";
}

// int main(int argc, char const *argv[])
// {
//     Movie input_linear[table_size_linear];
//     Movie input_double_hash[table_size_double_hash];

//     //Cria tabela hash com metodo da divisão e resolve conflitos com duplo hash
//     cout << create_division_double_hash(input_double_hash, file_name);
//     cout << "\n"
//          << search_division_double_hash(input_double_hash, "Madoc Kolson");
//     cout << "\n"
//          << return_occupancy_rate(input_double_hash, table_size_double_hash);

//     return 0;
// }
