#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// struct rating
// {
//     int userId;
//     int movieId;
//     float rating;
//     //string timesTamp;
// };
// typedef struct rating Rating;

void read_ratings(Movie hash_movies[], User hash_users[])
{
    int key, key_user, movieId, userId;
    float rating;
    fstream fin;
    //vector<Rating> ratings;
    // Rating rating;
    string line;
    string delimiter = ",";
    size_t pos = 0;
    User user;

    fin.open("../Dados_clean/rating.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {
        pos = line.find(delimiter);
        userId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        movieId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        rating = stof(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        key = search_movie_in_hash(hash_movies, movieId);
        if (key > 0)
        {
            hash_movies[key].number_of_ratings++;
            hash_movies[key].ratings_average =
                (hash_movies[key].ratings_average * (hash_movies[key].number_of_ratings - 1) + rating) / hash_movies[key].number_of_ratings;
        }

        key_user = search_user_in_hash(hash_users, userId);
        if (key_user > 0)
        {
            hash_users[key_user].ratings.push_back(rating);
            hash_users[key_user].ratedMoviesId.push_back(movieId);
        }
        else
        {
            user.id = userId;
            user.ratedMoviesId.push_back(movieId);
            user.ratings.push_back(rating);
            insert_user_to_hash(hash_users, user);
        }
        user.ratings.clear();
        user.ratedMoviesId.clear();
        //ratings.push_back(rating);
    }
}