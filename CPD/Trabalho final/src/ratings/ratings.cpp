using namespace std;

//Monta hash de usuários e filmes a partir de csv de avaliações
void read_ratings(Movie hashMovies[], User hashUsers[])
{
    int key, keyUser, movieId, userId;
    float rating;
    fstream fin;
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

        key = search_movie_in_hash(hashMovies, movieId);
        if (key > 0)
        {
            hashMovies[key].numberOfRatings++;
            hashMovies[key].ratingsAverage =
                (hashMovies[key].ratingsAverage * (hashMovies[key].numberOfRatings - 1) + rating) / hashMovies[key].numberOfRatings;
        }

        keyUser = search_user_in_hash(hashUsers, userId);
        if (keyUser > 0)
        {
            hashUsers[keyUser].ratings.push_back(rating);
            hashUsers[keyUser].ratedMoviesId.push_back(movieId);
        }
        else
        {
            user.id = userId;
            user.ratedMoviesId.push_back(movieId);
            user.ratings.push_back(rating);
            insert_user_to_hash(hashUsers, user);
        }
        user.ratings.clear();
        user.ratedMoviesId.clear();
    }
}