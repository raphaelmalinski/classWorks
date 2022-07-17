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

//Retorna um novo nodo da trie (inicializa os NULL's)
TrieMovie *initialize_movie(void)
{
    TrieMovie *movie = new TrieMovie;

    movie->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        movie->children[i] = NULL;

    return movie;
}

//Insere um novo filme na árvore trie
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
            pCrawl->children[index] = initialize_movie();

        pCrawl = pCrawl->children[index];
    }

    //Marca o ultimo nodo como folha
    pCrawl->isEndOfWord = true;
    pCrawl->title = key;
    pCrawl->movieId = movieId;
}

//Verifica se uma dada árvore trie é vazia
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

//Retorna o tamanho da trie
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
            counter = counter + size_of_trie(trie->children[i]);
        }
    }
    return counter;
}

//Retorna true se a chave está presente, senão retorna false
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
        if (!pCrawl->children[index])
        {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

//Pesquisa na trie um filme a partir de um prefixo
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
        if (!pCrawl->children[index])
        {
            return NULL;
        }
        pCrawl = pCrawl->children[index];
    }
    return pCrawl;
}

// //Imprime filmes a partir de um dado prefixo
// void print_trie_movies(TrieMovie *root, string word = "")
// {
//     string word_temp;
//     int index;

//     if (root->isEndOfWord)
//     {
//         cout << root->title << endl;
//     }
//     for (int i = 0; i < ALPHABET_SIZE; i++)
//     {
//         word_temp = word;
//         if (root->children[i] != NULL)
//         {
//             if (i >= 65 && i <= 90)
//             {
//                 index = i + 32;
//             }
//             else
//             {
//                 index = i;
//             }
//             // int index = i + 'a';
//             word_temp.push_back(index);
//             print_trie_movies(root->children[i], word_temp);
//         }
//     }
// }

// void print_trie_movies_for_prefix(TrieMovie *root, string word)
// {
//     TrieMovie *trie_with_prefix = search_prefix(root, word);
//     if (trie_with_prefix != NULL)
//     {
//         print_trie_movies(trie_with_prefix, word);
//     }
//     else
//     {
//         cout << "Not found" << endl;
//     }
// }