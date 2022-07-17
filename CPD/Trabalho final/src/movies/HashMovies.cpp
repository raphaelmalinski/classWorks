using namespace std;

const int HASH_MOVIES_SIZE = 60011;
const int DIVIDER_MOVIES = 30011;   

struct Movie
{
    int id;
    string title;
    vector<string> genres;
    float ratingsAverage = 0;
    int numberOfRatings = 0;
    bool used = false;
    bool occupied = false;
};
typedef struct Movie Movie;

//funções de hash escolhidas - divisão
int division_method(int key)
{
    int keyNumber = key % DIVIDER_MOVIES;
    return keyNumber;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash
void insert_movie_to_hash(Movie hash[], Movie movie)
{
    int key, keyAux;
    int i = 1;
    bool inserted = false;
    string nameRead, nameReadAux;

    key = division_method(movie.id);
    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method(movie.id) + i;
            i++;
            while (key >= HASH_MOVIES_SIZE)
            {
                key = key - HASH_MOVIES_SIZE;
            }
        }
        else
        {
            hash[key] = movie;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela hash de filmes criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_movie_in_hash(Movie hash[], int movieId)
{
    int i = 1;
    int key = division_method(movieId);
    while (hash[key].used)
    {
        if (hash[key].id == movieId)
        {
            return key;
        }
        else
        {
            key = key + i * division_method(movieId) + i;
            i++;
            while (key >= HASH_MOVIES_SIZE)
            {
                key = key - HASH_MOVIES_SIZE;
            }
        }
    }
    return -1;
}