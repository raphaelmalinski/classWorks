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
            if (std::find(hash_tags[key].moviesAssociated.begin(),
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

vector<Movie> return_movies_by_tag(Tag hashTags[], Movie hashMovies[], string tag)
{
    int key_movie;
    vector<Movie> moviesFound;
    int key_tag = search_tag_in_hash(hashTags, tag);
    if(key_tag > 0){
        for(int i = 0; i < hashTags[key_tag].moviesAssociated.size(); i++){
            key_movie = search_movie_in_hash(hashMovies, hashTags[key_tag].moviesAssociated[i]);
            moviesFound.push_back(hashMovies[key_movie]);
        }
    }
    return moviesFound;
}

//Função que imprime filmes associados a tags que estão numa dada lista
void print_list_tags_movies(Tag hashTags[], Movie hashMovies[], vector<string> tagList)
{
    bool movieWasFound = false;
    vector<Movie> moviesFound;
    for (int i = 0; i < tagList.size(); i++)
    {
        moviesFound = return_movies_by_tag(hashTags, hashMovies, tagList[i]);
        if (!moviesFound.empty())
        {
            print_movies(moviesFound);
            movieWasFound = true;
        }
    }
    if(!movieWasFound){
        cout << "Movies with tags informed not found";
    }
}