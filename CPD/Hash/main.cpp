#include <cstdio>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

static int divider = 12007; //smaller prime number bigger than the number of keys plus 20%
static int fixed_value = 101; //prime number used in polynomial method

struct key
{
    //int key;
    string content;
    bool used;
    bool occupied;
};
typedef struct key key;

int convert_string_to_int(string word)
{
    int value = 0;
    int value_c;
    for (int i = 0; i < word.length(); i++)
    {
        value_c = tolower(word[i]) - 96; //97 is the number of "a" in ascii table
        value = value + value_c;
    }
    return value;
}

int division_method(string key, int times)
{
    int key_number = convert_string_to_int(key);
    return key_number % divider + times;
}

int polynomial_method(string key, int times)
{
    int value = tolower(key[0]);
    for (int i=1; i < key.length(); i++){
        value = ((value * 256) % fixed_value + key[i]) % fixed_value;
    }
    return value;
}

int main(int argc, char const *argv[])
{
    string word = "r";
    //int key = division_method(word, 0);
    int key = polynomial_method(word, 0);
    cout << key;
    // int i = convert_string_to_int(word);
    return 0;
}
