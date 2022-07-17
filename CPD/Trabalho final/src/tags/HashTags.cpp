using namespace std;

const int HASH_TAGS_SIZE = 700001; //tamanho da tabela sendo um númerdo primo (recomendado para duplo hash)
const int DIVIDER_TAGS = 500009;   //menor número primo maior que o tamanho da tabela

struct Tag
{
    string tag;
    vector<int> moviesAssociated;
    bool used = false;
    bool occupied = false;
};
typedef struct Tag Tag;

//Converte uma string em um inteiro
int convert_string_to_int(string word)
{
    int value = 0;
    int value_c;
    for (int i = 0; i < word.length(); i++)
    {
        value_c = word[i];
        value = value + value_c;
    }
    return value;
}

//Método da divisão 
int division_method_tag(string key)
{
    string keyTemp = to_lower(key);
    int keyNumber = convert_string_to_int(keyTemp) % DIVIDER_TAGS;
    return keyNumber;
}

//cria tabela de hash usando o metodo da divisão e resolve conflitos com duplo hash
void insert_tag_to_hash(Tag hash[], Tag tag)
{
    int key;
    int i = 1;
    bool inserted = false;
    string tag_temp = tag.tag;

    key = division_method_tag(tag_temp);

    while (!inserted)
    {
        if (hash[key].occupied)
        {
            key = key + i * division_method_tag(tag_temp) + i;
            i++;
            while (key >= HASH_TAGS_SIZE)
            {
                key = key - HASH_TAGS_SIZE;
            }
        }
        else
        {
            hash[key].tag = tag.tag;
            hash[key].moviesAssociated = tag.moviesAssociated;
            hash[key].occupied = true;
            hash[key].used = true;
            inserted = true;
        }
    }
}

//pesquisa na tabela hash de tags criada usando metodo da divisao com resolução de conflitos com duplo hash
int search_tag_in_hash(Tag hash[], string tag)
{
    int tagConverted;
    int i = 1;
    int key = division_method_tag(tag);

    while (hash[key].used)
    {
        if (to_lower(hash[key].tag) == to_lower(tag))
        {
            return key;
        }
        else
        {
            key = key + i * division_method_tag(tag) + i;
            i++;
            while (key >= HASH_TAGS_SIZE)
            {
                key = key - HASH_TAGS_SIZE;
            }
        }
    }
    return -1;
}