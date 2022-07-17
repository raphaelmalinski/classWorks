using namespace std;

const int HASH_USERS_SIZE = 200003; 
const int DIVIDER_USERS = 100003;   

struct User
{
    int id;
    vector<int> ratedMoviesId;
    vector<float> ratings;
    bool used = false;
    bool occupied = false;
};
typedef struct User User;

//cria tabela hash de usuarios usando o metodo da divisão e resolve conflitos com duplo hash.
void insert_user_to_hash(User hash[], User user)
{
    int key, keyAux;
    string nameRead, nameReadAux;
    int i = 1;
    bool inserted = false;
    
    key = division_method(user.id);

    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method(user.id) + i;
            i++;
            while (key >= HASH_USERS_SIZE)
            {
                key = key - HASH_USERS_SIZE;
            }
        }
        else
        {
            hash[key] = user;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela de hash criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_user_in_hash(User hash[], int userId)
{
    int i = 1;
    int key = division_method(userId);
    while (hash[key].used)
    {
        if (hash[key].id == userId)
        {
            return key;
        }
        else
        {
            key = key + i * division_method(userId) + i;
            i++;
            while (key >= HASH_USERS_SIZE)
            {
                key = key - HASH_USERS_SIZE;
            }
        }
    }
    return -1;
}