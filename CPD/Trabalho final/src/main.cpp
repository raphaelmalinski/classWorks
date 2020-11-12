#include "functions.cpp"
#include "./movies/movies.cpp"
#include "./users/users.cpp"
#include "./ratings/ratings.cpp"
#include "./tags/tags.cpp"



int main(int argc, char *argv[])
{
    //Criando tabelas hash
    Movie *hash_movies = new Movie[hash_movies_size];
    User *hash_users = new User[hash_users_size];
    Tag *hash_tags = new Tag[hash_tags_size];

    //Criando árvore Trie de filmes
    TrieMovie *movies = initializeMovie();

    read_movies(movies, hash_movies);
    read_ratings(hash_movies, hash_users);
    read_tags(hash_tags);
    print_tags_hash(hash_tags, hash_tags_size);
}