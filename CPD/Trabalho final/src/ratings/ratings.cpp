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
	string line;
    string delimiter = ",";
    size_t pos = 0;
	
	fin.open("../Dados_clean/minirating.csv", ios::in);
    getline(fin, line);

	while (getline(fin, line))
	{
        pos = line.find(delimiter);
        rating.userId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        rating.movieId = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        rating.rating = stof(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        ratings.push_back(rating);
	}

	//Usado pra imprimir
	// for (vector<Rating>::iterator it = ratings.begin(); it != ratings.end(); it++)
	// {
	// 	cout << 
    //     "User Id: " << it->userId << 
    //     ", Movie Id: " << it->movieId << 
    //     ", Rating: " << it->rating << endl;
    //     //", TimesTemp: " << it->timesTamp << "\n";
	// }
}