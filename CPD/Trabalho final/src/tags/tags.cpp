#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct tag
{
    int userId;
    int movieId;
    string tag;
    string timesTamp;
};
typedef struct tag Tag;

void read_tags()
{
    fstream fin;
    vector<Tag> tags;
    Tag tag;
    string line, token;
    string delimiter = ",";
    size_t pos;

    fin.open("../Dados_clean/tag_clean.csv", ios::in);
    getline(fin, line);

    while (getline(fin, line))
    {
        pos = 0;
        pos = line.find(delimiter);
        token = line.substr(0, pos);
        tag.userId = stoi(token, 0);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        tag.movieId = stoi(token);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        tag.tag = token;
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        token = line.substr(0, pos);
        tag.timesTamp = token;
        line.erase(0, pos + delimiter.length());

        tags.push_back(tag);
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
