#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct rating
{
    int userId;
    int movieId;
    float rating;
    string timesTamp;
};
typedef struct rating Rating;

void read_ratings()
{
	fstream fin;
	vector<Rating> ratings;
    Rating rating;
	string line, temp;
    string delimiter = ",";
    size_t pos = 0;
	
	fin.open("../Dados_clean/minirating.csv", ios::in);
	fin >> line;
	while (fin >> line)
	{
		fin >> temp;
		line = line + " " + temp;
        
        pos = line.find(delimiter);
        temp = line.substr(0, pos);
        rating.userId = stoi(temp);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        temp = line.substr(0, pos);
        rating.movieId = stoi(temp);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        temp = line.substr(0, pos);
        rating.rating = stof(temp);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        temp = line.substr(0, pos);
        rating.timesTamp = temp;
        line.erase(0, pos + delimiter.length());

        ratings.push_back(rating);
	}

	//Usado pra imprimir
	for (vector<Rating>::iterator it = ratings.begin(); it != ratings.end(); it++)
	{
		cout << 
        "User Id: " << it->userId << 
        ", Movie Id: " << it->movieId << 
        ", Rating: " << it->rating << 
        ", TimesTemp: " << it->timesTamp << "\n";
	}
}