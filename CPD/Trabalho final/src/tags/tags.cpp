#include "HashTags.cpp"

using namespace std;

//Monta estrutura de tags a partir do csv de tags
void read_tags(Tag hashTags[])
{
    fstream fin;
    Tag tag;
    string line, token, tagString;
    string delimiter = ",";
    size_t pos;
    int movieId, key, tagConverted;

    fin.open("../Dados_clean/tag_clean.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {
        //Ignora id do usuário (não será usado)
        pos = 0;
        pos = line.find(delimiter);
        line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        //Guarda id do filme
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        movieId = stoi(token);
        line.erase(0, pos + delimiter.length());

        //Guarda tag
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        if (token[0] == '"')
        {
            token.erase(0, 1);
            token.pop_back();
        }
        tagString = token;
        line.erase(0, pos + delimiter.length());

        //Ignora timestamp (não será usado)
        pos = line.find(delimiter);
        line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        key = search_tag_in_hash(hashTags, tagString);
        if (key > 0)
        {
            if (find(hashTags[key].moviesAssociated.begin(),
                     hashTags[key].moviesAssociated.end(), movieId) == hashTags[key].moviesAssociated.end())
            {
                hashTags[key].moviesAssociated.push_back(movieId);
            }
        }
        else
        {
            tag.tag = tagString;
            tag.moviesAssociated.push_back(movieId);
            insert_tag_to_hash(hashTags, tag);
        }
        tag.moviesAssociated.clear();
    }
}

//Retorna vetor com a intersecção de dois vetores
vector<int> return_equal_values(vector<int> vector1, vector<int> vector2)
{
    if (vector1.empty())
    {
        return vector2;
    }
    else if (vector2.empty())
    {
        return vector1;
    }
    else
    {
        vector<int> vectorAux;
        for (int i = 0; i < vector1.size(); i++)
        {
            for (int j = 0; j < vector2.size(); j++)
            {
                if (vector1[i] == vector2[j])
                {
                    vectorAux.push_back(vector1[i]);
                    j = vector2.size();
                }
            }
        }
        return vectorAux;
    }
}

//Retorna vetor de ids de filmes que estão associados a uma lista de tags
vector<int> return_movies_ids_by_list_tags(Tag hashTags[], vector<string> tag)
{
    int key_movie, key_tag;
    vector<int> moviesIdsFound, moviesIdsFound_aux;
    for (int i = 0; i < tag.size(); i++)
    {
        key_tag = search_tag_in_hash(hashTags, tag[i]);
        if (key_tag > 0)
        {
            for (int j = 0; j < hashTags[key_tag].moviesAssociated.size(); j++)
            {
                moviesIdsFound_aux.push_back(hashTags[key_tag].moviesAssociated[j]);
            }
            moviesIdsFound = return_equal_values(moviesIdsFound, moviesIdsFound_aux);
            moviesIdsFound_aux.clear();
        }
    }
    return moviesIdsFound;
}

//Função que imprime filmes associados a tags que estão numa dada lista
void print_list_tags_movies(Tag hashTags[], Movie hashMovies[], vector<string> tagList)
{
    int key_movie;
    bool movieWasFound = false;
    Movie movieFound;
    vector<int> moviesIdFound = return_movies_ids_by_list_tags(hashTags, tagList);
    for (int i = 0; i < moviesIdFound.size(); i++)
    {
        key_movie = search_movie_in_hash(hashMovies, moviesIdFound[i]);
        if (key_movie > 0)
        {
            movieFound = hashMovies[key_movie];
            print_movie(movieFound);
            movieWasFound = true;
        }
    }
    if (!movieWasFound)
    {
        cout << "Movies with tags informed not found! ";
    }
}

//Retorna lista de tags encontradas em uma string
vector<string> return_tags(string tags)
{
    vector<string> tagList;
    size_t pos = 0;
    string delimiter = "'";
    string token;

    //Remove o espaço que tem no inicio
    pos = tags.find(delimiter);
    tags.erase(0, pos + delimiter.length());

    pos = tags.find(delimiter);
    do
    {
        token = tags.substr(0, pos);
        if(token != " "){
            tagList.push_back(token);
        }
        tags.erase(0, pos + delimiter.length());
    } while ((pos = tags.find(delimiter)) != std::string::npos);

    return tagList;
}