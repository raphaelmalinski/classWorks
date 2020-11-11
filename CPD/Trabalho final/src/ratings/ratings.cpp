#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct rating
{
    int userId;
    int movieId;
    float rating;
    //string timesTamp;
};
typedef struct rating Rating;

void read_ratings(Movie hash_movies[])
{
    int key;
    fstream fin;
    //vector<Rating> ratings;
    Rating rating;
    string line;
    string delimiter = ",";
    size_t pos = 0;

    fin.open("../Dados_clean/minirating.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {
        pos = line.find(delimiter);
        rating.userId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        rating.movieId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        rating.rating = stof(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        key = search_movie_in_hash(hash_movies, rating.movieId);
        if (key > 0)
        {
            hash_movies[key].number_of_ratings++;
            hash_movies[key].ratings_average =
                (hash_movies[key].ratings_average * (hash_movies[key].number_of_ratings - 1) + rating.rating) / hash_movies[key].number_of_ratings;
        }

        //ratings.push_back(rating);
    }

    //Usado pra imprimir
    // for (vector<Rating>::iterator it = ratings.begin(); it != ratings.end(); it++)
    // {
    // 	cout <<
    //     "User Id: " << it->userId <<
    //     ", Movie Id: " << it->movieId <<
    //     ", Rating: " << it->rating << endl;
    //     //", TimesTemp: " << it->timesTamp << "\n";
    // }
}