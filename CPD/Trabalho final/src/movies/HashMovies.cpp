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

const int hash_size = 60011; //tamanho da tabela sendo um númerdo primo (recomendado para duplo hash)
const int divider = 30011;   //menor número primo maior que o tamanho da tabela

struct Movie
{
    int id;
    string title;
    vector<string> genres;
    float ratings_average = 0;
    int number_of_ratings = 0;
    bool used = false;
    bool occupied = false;
};
typedef struct Movie Movie;

//funções de hash escolhidas - divisão e polinomial
int division_method(int key)
{
    int key_number = key % divider;
    return key_number;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash. Retorna número de colisões
void insert_movie_to_hash(Movie hash[], Movie movie)
{
    int key, key_aux;
    int i = 1;
    bool inserted = false;
    string name_read, name_read_aux;

    key = division_method(movie.id);
    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method(movie.id) + i;
            i++;
            while (key >= hash_size)
            {
                key = key - hash_size;
            }
        }
        else
        {
            hash[key] = movie;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_movie_in_hash(Movie hash[], int movieId)
{
    int i = 1;
    int key = division_method(movieId);
    while (hash[key].used)
    {
        if (hash[key].id == movieId)
        {
            return key;
        }
        else
        {
            key = key + i * division_method(movieId) + i;
            i++;
            // if (key >= hash_size)
            // {
            //     key = key - hash_size;
            // }
            while (key >= hash_size)
            {
                key = key - hash_size;
            }
        }
    }
    return -1;
}

void print_hash(Movie hash[], int table_size)
{
    int j = 0;
    for (int i = 0; i < table_size; i++)
    {
        if (hash[i].occupied)
        {
            cout << "Movie Id: " << hash[i].id
                 << " | Title: " << hash[i].title
                 << " | Movie Genres: ";
            for (vector<string>::iterator it = hash[i].genres.begin(); it != hash[i].genres.end(); it++)
            {
                cout << *it << ", ";
            }
            cout << " | Rating: " << hash[i].ratings_average
                 << " | Count: " << hash[i].number_of_ratings;
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
