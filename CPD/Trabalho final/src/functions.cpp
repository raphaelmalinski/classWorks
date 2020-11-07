#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void read_record()
{

	// File pointer
	fstream fin;

	// Open an existing file
	fin.open("../Dados_clean/minirating.csv", ios::in);

	// Read the Data from the file
	// as String Vector
	vector<string> rows;
	string line, temp;
	fin >> line;
	while (fin >> line)
	{
		fin >> temp;
		line = line + " " + temp;
		rows.push_back(line);		
	}
	// for (vector<string>::iterator it = rows.begin(); it != rows.end(); it++)
	// {
	// 	cout << *it << "\n"; // valor na posição apontada por it
	// }
}


void read_rating()
{
	fstream fin;
	vector<string> rows;
	string line, temp;
	
	fin.open("../Dados_clean/minirating.csv", ios::in);
	fin >> line;
	while (fin >> line)
	{
		fin >> temp;
		line = line + " " + temp;
		rows.push_back(line);		
	}

	//Usado pra imprimir
	// for (vector<string>::iterator it = rows.begin(); it != rows.end(); it++)
	// {
	// 	cout << *it << "\n"; // valor na posição apontada por it
	// }
}