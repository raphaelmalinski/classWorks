#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct movie
{
    int id;
    string title;
    vector<string> genres;
};
typedef struct movie Movie;

void read_movies()
{
    fstream fin;
    vector<Movie> movies;
    Movie movie;
    string line, token;
    int i;
    string delimiter = "|";
    size_t pos;

    fin.open("../Dados_clean/movie_clean.csv", ios::in);
    getline(fin, line);
    
    while (getline(fin, line))
    {
        i = 0;
        while (i < line.length())
        {
            if (line[i] == ',')
            {
                line[i] = '|';
                i = line.length();
            }
            i++;
        }

        i = line.length() - 1;
        while (i > 0)
        {
            if (line[i] == ',')
            {
                line[i] = '|';
                i = 0;
            }
            i--;
        }

        pos = 0;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        movie.id = stoi(token, 0);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        movie.title = token;
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        do
        {
            token = line.substr(0, pos);
            movie.genres.push_back(token);
            line.erase(0, pos + delimiter.length());
        } while ((pos = line.find(delimiter)) != std::string::npos);

        movies.push_back(movie);
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
