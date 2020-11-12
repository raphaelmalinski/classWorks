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

const int hash_users_size = 200003; //tamanho da tabela sendo um númerdo primo (recomendado para duplo hash)
const int divider_users = 100003;   //menor número primo maior que o tamanho da tabela

struct User
{
    int id;
    vector<int> ratedMoviesId;
    vector<float> ratings;
    bool used = false;
    bool occupied = false;
};
typedef struct User User;

//funções de hash escolhidas - divisão e polinomial
// int division_method(int key)
// {
//     int key_number = key % divider_users;
//     return key_number;
// }

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash. Retorna número de colisões
void insert_user_to_hash(User hash[], User user)
{
    int key, key_aux;
    int i = 1;
    bool inserted = false;
    string name_read, name_read_aux;

    key = division_method(user.id);
    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method(user.id) + i;
            i++;
            while (key >= hash_users_size)
            {
                key = key - hash_users_size;
            }
        }
        else
        {
            hash[key] = user;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_user_in_hash(User hash[], int userId)
{
    int i = 1;
    int key = division_method(userId);
    while (hash[key].used)
    {
        if (hash[key].id == userId)
        {
            return key;
        }
        else
        {
            key = key + i * division_method(userId) + i;
            i++;
            // if (key >= hash_size)
            // {
            //     key = key - hash_size;
            // }
            while (key >= hash_users_size)
            {
                key = key - hash_users_size;
            }
        }
    }
    return -1;
}

void print_users_hash(User hash[], int table_size)
{
    int j = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (hash[i].occupied)
        {
            cout << "User Id: " << hash[i].id << " | Ratings: ";
            //  << " | Title: " << hash[i].title
            //  << " | Movie Genres: ";
            for (int k = 0; k < hash[i].ratings.size(); k++)
            {
                cout << hash[i].ratings[k] << ", ";
            }
            cout << " | "
                 << "Movies Id's: ";
            for (int k = 0; k < hash[i].ratedMoviesId.size(); k++)
            {
                cout << hash[i].ratedMoviesId[k] << ", ";
            }
            // cout << " | Rating: " << hash[i].ratings_average
            //      << " | Count: " << hash[i].number_of_ratings;
            cout << endl;
            j++;
        }
    }
    cout << "Number of keys: " << j << "\n";
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
