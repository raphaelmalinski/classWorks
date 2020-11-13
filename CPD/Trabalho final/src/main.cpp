#include "functions.cpp"
#include "./movies/movies.cpp"
#include "./users/users.cpp"
#include "./ratings/ratings.cpp"
#include "./tags/tags.cpp"



int main(int argc, char *argv[])
{
    //Criando tabelas hash
    Movie *hashMovies = new Movie[hash_movies_size];
    User *hashUsers = new User[hash_users_size];
    Tag *hashTags = new Tag[hash_tags_size];

    //Criando árvore Trie de filmes
    TrieMovie *movies = initializeMovie();

    //Montando estruturas necessárias
    read_movies(movies, hashMovies);
    read_ratings(hashMovies, hashUsers);
    read_tags(hashTags);
    //cout << search_tag_in_hash(hash_tags, "expansive") << endl;
    print_list_tags_movies(hashTags, hashMovies, {"BraZil", "drugs", "aids"});
}