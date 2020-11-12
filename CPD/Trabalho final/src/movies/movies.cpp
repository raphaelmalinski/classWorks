#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "TrieMovie.cpp"
#include "HashMovies.cpp"
//#include "../functions.cpp"

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
        //Para pegar o ultimo genero (em casos de mais de um genero)
        if(line != token){
            movie.genres.push_back(line);
        }
        

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

vector<Movie> search_movie_by_list_id(Movie hash_movies[], vector<int> movieIdList){
    vector<Movie> movies_found;
    int key;
    for (int i = 0; i < movieIdList.size(); i++)
    {
        key = search_movie_in_hash(hash_movies, movieIdList[i]);
        if(key > 0){
            movies_found.push_back(hash_movies[key]);
        }
    }
    return movies_found;
}

vector<Movie> sort_movies_list_by_rating(vector<Movie> movies)
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
            while (j >= h && aux.ratings_average < movies[j - h].ratings_average)
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

vector<Movie> sort_movies_list_by_count(vector<Movie> movies)
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

void create_list_of_found_movies(TrieMovie *root, int found_movies_list[])
{
    int index;
    if (root->isEndOfWord)
    {
        found_movies_list[global_counter] = root->movieId;
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
            create_list_of_found_movies(root->children[i], found_movies_list);
        }
    }
}

vector<Movie> search_movies_to_prefix(TrieMovie *root, Movie hash_movies[], string prefix)
{
    int key;
    vector<Movie> found_movies_list;
    TrieMovie *found_movies = search_prefix(root, prefix);

    if (found_movies == NULL && !found_movies->isEndOfWord)
    {
        return found_movies_list;
    }

    int num_of_movies_found = size_of_trie(found_movies);
    int found_movies_id_list[num_of_movies_found];
    create_list_of_found_movies(found_movies, found_movies_id_list);

    for (int i = 0; i < num_of_movies_found; i++)
    {
        key = search_movie_in_hash(hash_movies, found_movies_id_list[i]);
        found_movies_list.push_back(hash_movies[key]);
    }
    return found_movies_list;
}

void print_movies_to_prefix(TrieMovie *root, Movie hash_movies[], string prefix)
{
    vector<Movie> found_movies = search_movies_to_prefix(root, hash_movies, prefix);

    if (found_movies.empty())
    {
        cout << "Movies not found!";
    }
    else
    {
        found_movies = sort_movies_list_by_count(found_movies);
        cout << "Movie Id | "
             << "Title | "
             << "Genres | "
             << "Rating | "
             << "Count | " << endl;
        for (vector<Movie>::iterator it = found_movies.end() - 1; it != found_movies.begin() - 1; it--)
        {
            cout << it->id << " | "
                 << it->title << " | ";
            for (vector<string>::iterator it_2 = it->genres.begin(); it_2 != it->genres.end(); it_2++)
            {
                cout << *it_2 << ",";
            }
            cout << " | " << it->ratings_average << " | "
                 << it->number_of_ratings << endl
                 << endl;
        }
    }
}

//Função que verifica se um dado filme é de um dado genero
bool find_genre(Movie movie, string genre)
{
    for (vector<string>::iterator it = movie.genres.begin(); it != movie.genres.end(); it++)
    {
        if (to_lower(genre) == to_lower(*it))
        {
            return true;
        }
    }
    return false;
}

//Função que retorna um vetor com todos filmes que sejam de um dado genero
//que tenham no minimo 1000 avaliações
vector<Movie> search_movie_to_genre(Movie hash_movies[], string genre)
{
    vector<Movie> movies;
    for (int i = 0; i < hash_movies_size; i++)
    {
        if (hash_movies[i].occupied)
        {
            if (find_genre(hash_movies[i], genre) && hash_movies[i].number_of_ratings >= 1000)
            {
                movies.push_back(hash_movies[i]);
            }
        }
    }
    return movies;
}

//Função que imprime o top n filmes com melhores notas que sejam do genero especificado e
//tenham no minimo 1000 avaliações
void print_top_n_genre(Movie hash_movies[], int top_n, string genre)
{
    vector<Movie> found_movies = search_movie_to_genre(hash_movies, genre);
    if (found_movies.empty())
    {
        cout << "Movies with " << genre << " genre and more then 1000 ratings not found!";
    }
    else
    {
        found_movies = sort_movies_list_by_rating(found_movies);
        for (int i = found_movies.size()-1; i > found_movies.size()-1-top_n; i--)
        {
            cout << found_movies[i].title << " | ";
            for (int j = 0; j < found_movies[i].genres.size(); j++)
            {
                cout << found_movies[i].genres[j] << ", ";
            }
            cout << " | " << found_movies[i].ratings_average 
                 << " | " << found_movies[i].number_of_ratings << endl;
        }
    }
}
