#include "TrieMovie.cpp"
#include "HashMovies.cpp"

using namespace std;

int globalCounter = 0;

//Função usada para trocar virgulas da extremidade uma string por outro caractere
string replace_chars(string word, char newChar, char oldChar)
{
    int i = 0;
    string newWord = word;
    while (i < newWord.length())
    {
        if (newWord[i] == oldChar)
        {
            newWord[i] = newChar;
            i = newWord.length();
        }
        i++;
    }

    i = newWord.length() - 1;
    while (i > 0)
    {
        if (newWord[i] == oldChar)
        {
            newWord[i] = newChar;
            i = 0;
        }
        i--;
    }
    return newWord;
}

//Função usada para ler do arquivo csv os filmes e incluílos na tabela hash e na arvore trie
void read_movies(TrieMovie *root, Movie hashMovies[])
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
        if (line != token)
        {
            movie.genres.push_back(line);
        }

        //Insert movie to trie tree
        insert_movie(root, movie.title, movie.id);

        //Insert movie to hash
        insert_movie_to_hash(hashMovies, movie);

        movie.genres.clear();
    }
}

//Função usada para pesquisar filmes na hash de filmes por uma lista de ids de filmes
vector<Movie> search_movie_by_list_id(Movie hashMovies[], vector<int> movieIdList)
{
    vector<Movie> moviesFound;
    int key;
    for (int i = 0; i < movieIdList.size(); i++)
    {
        key = search_movie_in_hash(hashMovies, movieIdList[i]);
        if (key > 0)
        {
            moviesFound.push_back(hashMovies[key]);
        }
    }
    return moviesFound;
}

//Função que ordena crescentemente uma lista de filmes pela nota (utiliza shell sort)
vector<Movie> sort_movies_list_by_rating(vector<Movie> movies)
{
    int i, j;
    int k = 1;
    int tam = movies.size();
    int h = tam / pow(2, k);
    Movie aux;

    while (h > 0)
    {
        i = h;
        while (i < tam)
        {
            aux = movies[i];
            j = i;
            while (j >= h && aux.ratingsAverage < movies[j - h].ratingsAverage)
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

//Cria lista de filmes encontrados na árvore trie
void create_list_of_found_movies(TrieMovie *root, int found_movies_list[])
{
    int index;
    if (root->isEndOfWord)
    {
        found_movies_list[globalCounter] = root->movieId;
        globalCounter++;
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

//Pesquisa fillmes em uma arvore trie por prefixo
vector<Movie> search_movies_to_prefix(TrieMovie *root, Movie hash_movies[], string prefix)
{
    int key;
    vector<Movie> foundMoviesList;
    TrieMovie *foundMovies = search_prefix(root, prefix);

    if (foundMovies == NULL)
    {
        return foundMoviesList;
    }

    int numOfMoviesFound = size_of_trie(foundMovies);
    int foundMoviesIdList[numOfMoviesFound];
    create_list_of_found_movies(foundMovies, foundMoviesIdList);

    for (int i = 0; i < numOfMoviesFound; i++)
    {
        key = search_movie_in_hash(hash_movies, foundMoviesIdList[i]);
        foundMoviesList.push_back(hash_movies[key]);
    }
    globalCounter = 0;
    return foundMoviesList;
}

//Imprime filmes a partir de um dado prefixo
void print_movies_by_prefix(TrieMovie *root, Movie hashMovies[], string prefix)
{
    vector<Movie> foundMovies = search_movies_to_prefix(root, hashMovies, prefix);
    
    if (foundMovies.empty())
    {
        cout << "Movies not found!";
    }
    else
    {
        foundMovies = sort_movies_list_by_rating(foundMovies);
        for (vector<Movie>::iterator it = foundMovies.end() - 1; it != foundMovies.begin() - 1; it--)
        {
            cout << "Movie Id: " << it->id
                 << " | Title: " << it->title
                 << " | Genres: ";
            for (vector<string>::iterator it_2 = it->genres.begin(); it_2 != it->genres.end(); it_2++)
            {
                cout << *it_2 << ",";
            }
            cout << " | Rating: " << it->ratingsAverage
                 << " | Count: " << it->numberOfRatings << endl;
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
vector<Movie> search_movie_to_genre(Movie hashMovies[], string genre)
{
    vector<Movie> movies;
    for (int i = 0; i < HASH_MOVIES_SIZE; i++)
    {
        if (hashMovies[i].occupied)
        {
            if (find_genre(hashMovies[i], genre) && hashMovies[i].numberOfRatings >= 1000)
            {
                movies.push_back(hashMovies[i]);
            }
        }
    }
    return movies;
}

//Função que imprime o top n filmes com melhores notas que sejam do genero especificado e
//tenham no minimo 1000 avaliações
void print_top_n_genre(Movie hashMovies[], int topN, string genre)
{
    vector<Movie> foundMovies = search_movie_to_genre(hashMovies, genre);
    if (foundMovies.empty())
    {
        cout << "Movies with " << genre << " genre and more then 1000 ratings not found!";
    }
    else
    {
        foundMovies = sort_movies_list_by_rating(foundMovies);
        for (int i = foundMovies.size() - 1; i > foundMovies.size() - 1 - topN; i--)
        {
            cout << "Title: " << foundMovies[i].title
                 << "Genres: "
                 << " | ";
            for (int j = 0; j < foundMovies[i].genres.size(); j++)
            {
                cout << foundMovies[i].genres[j] << ", ";
            }
            cout << " | "
                 << "Rating: " << foundMovies[i].ratingsAverage
                 << " | "
                 << "Count: " << foundMovies[i].numberOfRatings << endl;
        }
    }
}

//Imprime um filme dado filme
void print_movie(Movie movie)
{
    cout << "Title: " << movie.title << " | Genres: ";
    for (int i = 0; i < movie.genres.size(); i++)
    {
        cout << movie.genres[i] << ", ";
    }
    cout << " | Rating: " << movie.ratingsAverage
         << " | Count: " << movie.numberOfRatings
         << endl;
}