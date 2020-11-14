#include "functions.cpp"
#include "./movies/movies.cpp"
#include "./users/users.cpp"
#include "./ratings/ratings.cpp"
#include "./tags/tags.cpp"

int main(int argc, char *argv[])
{
    //Criando tabelas hash
    Movie *hashMovies = new Movie[HASH_MOVIES_SIZE];
    User *hashUsers = new User[HASH_USERS_SIZE];
    Tag *hashTags = new Tag[HASH_TAGS_SIZE];

    //Criando árvore Trie de filmes
    TrieMovie *movies = initialize_movie();

    //Montando estruturas necessárias
    read_movies(movies, hashMovies);
    read_ratings(hashMovies, hashUsers);
    read_tags(hashTags);

    int topN;
    string command, line;
    string delimiter = " ";
    size_t pos = 0;
    string willContinue;
    vector<string> tagList;

    //Inicia console
    while (1)
    {
        system("clear");

        getline(cin, line);
        cout << endl;

        pos = line.find(delimiter);

        //Verifica se o comando tem parametros
        if (pos != string::npos)
        {
            command = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }

        if (command == "movie")
        {
            print_movies_by_prefix(movies, hashMovies, line);
            if (stop_program())
            {
                return 0;
            }
        }
        else if (command == "user")
        {
            print_user_rated_movie(hashUsers, hashMovies, stoi(line));
            if (stop_program())
            {
                return 0;
            }
        }
        else if (command[0] == 't' && command[1] == 'o' && command[2] == 'p')
        {
            string topNString = command.erase(0, 3);
            topN = stoi(topNString);
            print_top_n_genre(hashMovies, topN, line);
            if (stop_program())
            {
                return 0;
            }
        }
        else if (command == "tags")
        {
            tagList = return_tags(line);
            print_list_tags_movies(hashTags, hashMovies, tagList);
            if (stop_program())
            {
                return 0;
            }
        }
        else
        {
            cout << "Comando inválido! ";
            if (stop_program())
            {
                return 0;
            }
        }
        //Limpa o buffer
        getline(cin, line);
        command.clear();
    }
}