#include "HashUsers.cpp"

using namespace std;

void print_user_rated_movie(User hashUsers[], Movie hashMovies[], int userId)
{
    vector<Movie> moviesRated;
    int key = search_user_in_hash(hashUsers, userId);

    if (key < 0)
    {
        cout << "User not found!";
    }
    else
    {
        User user = hashUsers[key];

        moviesRated = search_movie_by_list_id(hashMovies, user.ratedMoviesId);
        for (int i = 0; i < user.ratings.size(); i++)
        {
            cout << "User rating: " << user.ratings[i]
                 << " | Title: " << moviesRated[i].title
                 << " | Global rating: " << moviesRated[i].ratingsAverage
                 << " | Count: " << moviesRated[i].numberOfRatings
                 << endl;
        }
    }
}