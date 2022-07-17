#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <limits.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//Função que deixar a string toda com letras minusculas
string to_lower(string string)
{
    for (int i = 0; i < string.length(); i++)
    {
        string[i] = tolower(string[i]);
    }
    return string;
}

//Função que verifica se usuario deseja continuar realizando pesquisas
bool stop_program()
{
    string willContinue;
    do
    {
        cout << endl << "Deseja continuar? [s/n] \n";
        cin >> willContinue;
    } while (to_lower(willContinue) != "s" && to_lower(willContinue) != "n");
    if (to_lower(willContinue) == "n")
    {
        return true;
    }
    else
    {
        return false;
    }
}