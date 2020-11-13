#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include "HashTags.cpp"

using namespace std;

void read_tags(Tag hash_tags[])
{
    fstream fin;
    Tag tag;
    string line, token, tag_s;
    string delimiter = ",";
    size_t pos;
    int movieId, key, tag_converted;

    fin.open("../Dados_clean/tag_clean.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {
        pos = 0;
        pos = line.find(delimiter);
        // token = line.substr(0, pos);
        line.substr(0, pos);
        // tag.userId = stoi(token, 0);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        movieId = stoi(token);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        if (token[0] == '"')
        {
            token.erase(0, 1);
            token.pop_back();
        }
        tag_s = token;
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        //token = line.substr(0, pos);
        line.substr(0, pos);
        // tag.timesTamp = token;
        line.erase(0, pos + delimiter.length());

        key = search_tag_in_hash(hash_tags, tag_s);
        if (key > 0)
        {
            if (find(hash_tags[key].moviesAssociated.begin(),
                     hash_tags[key].moviesAssociated.end(), movieId) == hash_tags[key].moviesAssociated.end())
            {
                hash_tags[key].moviesAssociated.push_back(movieId);
            }
        }
        else
        {
            tag.tag = tag_s;
            tag.moviesAssociated.push_back(movieId);
            insert_tag_to_hash(hash_tags, tag);
        }
        tag.moviesAssociated.clear();
    }
}

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
                if(vector1[i] == vector2[j]){
                    vectorAux.push_back(vector1[i]);
                    j = vector2.size();
                }
            }
        }
        return vectorAux;
    }
}

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
        cout << "Movies with tags informed not found";
    }
}