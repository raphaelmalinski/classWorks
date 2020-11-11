#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

const int ALPHABET_SIZE = 128;

struct TrieMovie
{
    TrieMovie *children[ALPHABET_SIZE];
    string title;
    int movieId;
    bool isEndOfWord;
};
typedef struct TrieMovie TrieMovie;

// Returns new trie node (initialized to NULLs)
TrieMovie *initializeMovie(void)
{
    TrieMovie *movie = new TrieMovie;

    movie->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        movie->children[i] = NULL;

    return movie;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert_movie(TrieMovie *root, string key, int movieId)
{
    TrieMovie *pCrawl = root;
    int index;
    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] >= 65 && key[i] <= 90)
        {
            index = tolower(key[i]);
        }
        else
        {
            index = key[i];
        }
        if (!pCrawl->children[index])
            pCrawl->children[index] = initializeMovie();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
    pCrawl->title = key;
    pCrawl->movieId = movieId;
}

bool is_trie_empty(TrieMovie *trie)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (trie->children[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

int size_of_trie(TrieMovie *trie)
{
    int counter = 0;
    if(trie->isEndOfWord){
        counter++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (trie->children[i] != NULL)
        {
            // if(trie->children[i]->isEndOfWord){
            //     counter++;
            // }
            counter = counter + size_of_trie(trie->children[i]);
        }
    }
    return counter;
}


// Returns true if key presents in trie, else
// false
bool search(struct TrieMovie *root, string key)
{
    TrieMovie *pCrawl = root;
    int index;

    for (int i = 0; i < key.length(); i++)
    {
        if (key[i] >= 65 && key[i] <= 90)
        {
            index = tolower(key[i]);
        }
        else
        {
            index = key[i];
        }
        // int index = tolower(key[i]) - 'a';
        if (!pCrawl->children[index])
        {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

TrieMovie *search_prefix(struct TrieMovie *root, string prefix)
{
    TrieMovie *pCrawl = root;
    int index;

    for (int i = 0; i < prefix.length(); i++)
    {
        if (prefix[i] >= 65 && prefix[i] <= 90)
        {
            index = tolower(prefix[i]);
        }
        else
        {
            index = prefix[i];
        }
        // int index = tolower(key[i]) - 'a';
        if (!pCrawl->children[index])
        {
            return NULL;
        }

        pCrawl = pCrawl->children[index];
    }
    // return (pCrawl != NULL && !is_trie_empty(pCrawl));
    return pCrawl;
}

void print_trie_movies(TrieMovie *root, string word = "")
{
    string word_temp;
    int index;

    if (root->isEndOfWord)
    {
        cout << root->title << endl;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        word_temp = word;
        if (root->children[i] != NULL)
        {
            if (i >= 65 && i <= 90)
            {
                index = i + 32;
            }
            else
            {
                index = i;
            }
            // int index = i + 'a';
            word_temp.push_back(index);
            print_trie_movies(root->children[i], word_temp);
        }
    }
}

void print_trie_movies_for_prefix(TrieMovie *root, string word)
{
    TrieMovie *trie_with_prefix = search_prefix(root, word);
    if (trie_with_prefix != NULL)
    {
        print_trie_movies(trie_with_prefix, word);
    }
    else
    {
        cout << "Not found" << endl;
    }
}


// void read_movies()
// {
//     fstream fin;
//     vector<Movie> movies;
//     Movie movie;
//     string line, token;
//     int i;
//     string delimiter = "|";
//     size_t pos;

//     fin.open("../Dados_clean/movie_clean.csv", ios::in);
//     getline(fin, line);
    
//     while (getline(fin, line))
//     {
//         i = 0;
//         while (i < line.length())
//         {
//             if (line[i] == ',')
//             {
//                 line[i] = '|';
//                 i = line.length();
//             }
//             i++;
//         }

//         i = line.length() - 1;
//         while (i > 0)
//         {
//             if (line[i] == ',')
//             {
//                 line[i] = '|';
//                 i = 0;
//             }
//             i--;
//         }

//         //Store movie id
//         pos = 0;
//         pos = line.find(delimiter);
//         token = line.substr(0, pos);
//         movie.id = stoi(token, 0);
//         line.erase(0, pos + delimiter.length());

//         //Store movie title
//         pos = line.find(delimiter);
//         token = line.substr(0, pos);
//         if (token[0] == '"'){
//             token.erase(0,1);
//             token.pop_back();
//         }
//         movie.title = token;
//         line.erase(0, pos + delimiter.length());

//         //Store list of genres
//         pos = line.find(delimiter);
//         do
//         {
//             token = line.substr(0, pos);
//             movie.genres.push_back(token);
//             line.erase(0, pos + delimiter.length());
//         } while ((pos = line.find(delimiter)) != std::string::npos);

//         movies.push_back(movie);
//         movie.genres.clear();
//     }
    
//     //Usado pra imprimir 
//     // for (vector<Movie>::iterator it = movies.begin(); it != movies.end(); it++)
//     // {
//     //     // cout << *it << "\n"; // valor na posição apontada por it
//     //     cout << "Id: " << it->id << " Movie: " << it->title << " Genres: ";
//     //     for (vector<string>::iterator it_2 = it->genres.begin(); it_2 != it->genres.end(); it_2++)
//     //     {
//     //         cout << *it_2 << ", ";
//     //     }
//     //     cout << "\n";
//     // }
// }
