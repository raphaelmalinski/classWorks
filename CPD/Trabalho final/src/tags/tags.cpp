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
                          hash_tags[key].moviesAssociated.end(), movieId) 
                          == hash_tags[key].moviesAssociated.end())
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
        // tags.push_back(tag);
    }

    //Usado pra imprimir
    // for (vector<Tag>::iterator it = tags.begin(); it != tags.end(); it++)
    // {
    //     cout <<
    //     "User Id: " << it->userId <<
    //     ", Movie Id: " << it->movieId <<
    //     ", Tag: " << it->tag <<
    //     ", TimesTamp: " << it->timesTamp << "\n";
    // }
}
