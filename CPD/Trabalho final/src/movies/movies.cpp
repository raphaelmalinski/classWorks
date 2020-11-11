#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "TrieMovie.cpp"
#include "HashMovies.cpp"

using namespace std;

int global_counter = 0;

string replace_chars(string word, char new_char, char old_char)
{
    int i = 0;
    string new_word = word;
    while (i < new_word.length())
    {
        if (new_word[i] == old_char)
        {
            new_word[i] = new_char;
            i = new_word.length();
        }
        i++;
    }

    i = new_word.length() - 1;
    while (i > 0)
    {
        if (new_word[i] == old_char)
        {
            new_word[i] = new_char;
            i = 0;
        }
        i--;
    }
    return new_word;
}

void read_movies(TrieMovie *root, Movie hash_movies[])
{
    fstream fin;
    Movie movie;
    string line, token;
    string delimiter = "|";
    size_t pos;

    fin.open("../Dados_clean/movie_clean.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {

        line = replace_chars(line, '|', ',');
        //Store movie id
        pos = 0;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        movie.id = stoi(token, 0);
        line.erase(0, pos + delimiter.length());

        //Store movie title
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        if (token[0] == '"')
        {
            token.erase(0, 1);
            token.pop_back();
        }
        movie.title = token;
        line.erase(0, pos + delimiter.length());

        //Store list of genres
        pos = line.find(delimiter);
        do
        {
            token = line.substr(0, pos);
            movie.genres.push_back(token);
            line.erase(0, pos + delimiter.length());
        } while ((pos = line.find(delimiter)) != std::string::npos);

        //Insert movie to trie tree
        insert_movie(root, movie.title, movie.id);

        //Insert movie to hash
        insert_movie_to_hash(hash_movies, movie);

        // movies.push_back(movie);
        movie.genres.clear();
    }

    //Usado pra imprimir
    // for (vector<Movie>::iterator it = movies.begin(); it != movies.end(); it++)
    // {
    //     // cout << *it << "\n"; // valor na posição apontada por it
    //     cout << "Id: " << it->id << " Movie: " << it->title << " Genres: ";
    //     for (vector<string>::iterator it_2 = it->genres.begin(); it_2 != it->genres.end(); it_2++)
    //     {
    //         cout << *it_2 << ", ";
    //     }
    //     cout << "\n";
    // }
}

vector<Movie> sort_movies_list(vector<Movie> movies)
{
    Movie aux;
    int k = 1;
    int tam = movies.size();
    int i, j;
    int h = tam / pow(2, k);

    while (h > 0)
    {
        i = h;
        while (i < tam)
        {
            aux = movies[i];
            j = i;
            while (j >= h && aux.number_of_ratings < movies[j - h].number_of_ratings)
            {
                movies[j] = movies[j - h];
                j = j - h;
            }
            movies[j] = aux;
            i = i + 1;
        }
        k++;
        h = tam / pow(2, k);
    }
    return movies;
}

void create_list_of_found_movies(TrieMovie *root, int founded_movies_list[])
{
    int index;
    if (root->isEndOfWord)
    {
        founded_movies_list[global_counter] = root->movieId;
        global_counter++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != NULL)
        {
            if (i >= 65 && i <= 90)
            {
                index = i + 32;
            }
            else
            {
                index = i;
            }
            create_list_of_found_movies(root->children[i], founded_movies_list);
        }
    }
}

vector<Movie> search_movies_to_prefix(TrieMovie *root, Movie hash_movies[], string prefix)
{
    int key;
    vector<Movie> founded_movies_list;
    TrieMovie *founded_movies = search_prefix(root, prefix);

    if(founded_movies == NULL && !founded_movies->isEndOfWord){
        return founded_movies_list;
    }

    int num_of_movies_founded = size_of_trie(founded_movies);
    int founded_movies_id_list[num_of_movies_founded];
    create_list_of_found_movies(founded_movies, founded_movies_id_list);

    for (int i = 0; i < num_of_movies_founded; i++)
    {
        key = search_movie_in_hash(hash_movies, founded_movies_id_list[i]);
        founded_movies_list.push_back(hash_movies[key]);
    }
    return founded_movies_list;
}

void print_movies_to_prefix(TrieMovie *root, Movie hash_movies[], string prefix)
{
    vector<Movie> founded_movies = search_movies_to_prefix(root, hash_movies, prefix);

    if (founded_movies.empty())
    {
        cout << "Movies not found!";
    }
    else
    {
        founded_movies = sort_movies_list(founded_movies);
        cout << "Movie Id | "
             << "Title | "
             << "Genres | "
             << "Rating | "
             << "Count | " << endl;
        for (vector<Movie>::iterator it = founded_movies.end()-1; it != founded_movies.begin()-1; it--)
        {
            cout << it->id << " | "
                 << it->title << " | ";
            for (vector<string>::iterator it_2 = it->genres.begin(); it_2 != it->genres.end(); it_2++)
            {
                cout << *it_2 << ",";
            }
            cout << " | " << it->ratings_average << " | "
                 << it->number_of_ratings << endl << endl;
        }
    }
}
