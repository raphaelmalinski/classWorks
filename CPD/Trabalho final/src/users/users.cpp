#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "HashUsers.cpp"

using namespace std;

void print_user_rated_movie(User hash_users[], Movie hash_movies[], int userId)
{
    vector<Movie> movies_rated;
    int key = search_user_in_hash(hash_users, userId);

    if (key < 0)
    {
        cout << "User not found!";
    }
    else
    {
        User user = hash_users[key];

        movies_rated = search_movie_by_list_id(hash_movies, user.ratedMoviesId);
        for (int i = 0; i < user.ratings.size(); i++)
        {
            cout << "User rating: " << user.ratings[i]
                 << " | Title: " << movies_rated[i].title
                 << " | Global rating: " << movies_rated[i].ratings_average
                 << " | Count: " << movies_rated[i].number_of_ratings
                 << endl;
        }
    }
}