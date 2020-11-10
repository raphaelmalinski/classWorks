#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "TrieMovie.cpp"
#include "HashMovies.cpp"

using namespace std;

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
        insertMovie(root, movie.title, movie.id);

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
