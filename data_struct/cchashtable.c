#include "cchashtable.h"
#include "common.h"


//VecResize increments or decrements the size of the dynamically allocated array
//int Up: selects the incrementation or the decrementation operation
//  Up == 1: increment
//  Up == 0: decrement
static int HtResize(CC_HASH_TABLE *HashTable, int Up);

//Frees the arary and it's keys
static int HtDestroyData(CC_HASH_TABLE_DATA **Data, int Size, int Count);

//HtHash generates a hash for a given key
static int HtHash(char *Key);

//Compares two keys alphabetically
//Returns:
//  <0:	the first character that does not match has a lower value in Key1 than in Key2
//  0:	the contents of both strings are equal
//  >0:	the first character that does not match has a greater value in Key1 than in Key2
static int HtKeyCompare(char *Key1, char *Key2);

//Copies the string from KeySource to KeyDestination
static void HtKeyCopy(char *KeySource, char *KeyDestination);

//Returns the length of the string
static int HtKeyLength(char *Key);

//HtIsPrime determines if a given number is a prime number
static int HtIsPrime(int Number);

//HtNextPrime returns the smallest prime number that is greater than the given number
static int HtNextPrime(int Number);

int HtCreate(CC_HASH_TABLE** HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    PCC_HASH_TABLE hashTable = (PCC_HASH_TABLE)malloc(sizeof(CC_HASH_TABLE));

    if (NULL == hashTable)
    {
        *HashTable = NULL;
        return -1;
    }

    hashTable->Data = NULL;
    hashTable->Size = 0;
    hashTable->Count = 0;

    *HashTable = hashTable;

    return 0;
}

int HtDestroy(CC_HASH_TABLE** HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    if (0 != HtClear(*HashTable))
    {
        return -1;
    }

    free(*HashTable);

    *HashTable = NULL;
    return 0;
}

int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value)
{
    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    if (0 == HashTable->Size)
    {
        if (-1 == HtResize(HashTable, 1))
        {
            return -1;
        }
    }

    if ((HashTable->Count + 1.0) / HashTable->Size > CC_MAX_LOAD_FACTOR) {
        if (-1 == HtResize(HashTable, 1))
        {
            return -1;
        }
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;
    int firstEmpty = -1;

    for (int i = 0; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL == HashTable->Data[index].Key)
        {
            firstEmpty = index;
        }
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            return -1;
        }
        index = (hash + i) % HashTable->Size;
    }

    if (firstEmpty != -1)
    {
        index = firstEmpty;
    }

    char *key = (char *)malloc(HtKeyLength(Key) * sizeof(char));

    if (NULL == key)
    {
        return -1;
    }

    HtKeyCopy(Key, key);

    HashTable->Data[index].Key = key;
    HashTable->Data[index].Value = Value;
    HashTable->Count++;

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value)
{
    if (NULL == HashTable || NULL == Key || NULL == Value || NULL == HashTable->Data || 0 == HashTable->Size || 0 == HashTable->Count)
    {
        return -1;
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 1; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            *Value = HashTable->Data[index].Value;
            return 0;
        }
        index = (hash + i) % HashTable->Size;
    }
    return -1;
}

int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key)
{
    if (NULL == HashTable || NULL == Key || NULL == HashTable->Data || 0 == HashTable->Size || 0 == HashTable->Count)
    {
        return -1;
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 1; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            free(HashTable->Data[index].Key);
            HashTable->Data[index].Key = NULL;
            HashTable->Data[index].Value = -1;
            HashTable->Count--;

            if (((float)HashTable->Count) / HashTable->Size < CC_MIN_LOAD_FACTOR) {
                if (-1 == HtResize(HashTable, 0))
                {
                    return -1;
                }
            }

            return 0;
        }
        index = (hash + i) % HashTable->Size;
    }
    return -1;
}

int HtHasKey(CC_HASH_TABLE* HashTable, char* Key)
{
    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    if (NULL == HashTable->Data || 0 == HashTable->Size || 0 == HashTable->Count)
    {
        return 0;
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 1; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            return 1;
        }
        index = (hash + i) % HashTable->Size;
    }
    return 0;
}

int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key)
{
    if (NULL == HashTable || NULL == Key || Index < 0 || Index >= HashTable->Count)
    {
        return -1;
    }

    int index = 0, count = 0;

    while(count <= Index)
    {
        if (NULL != HashTable->Data[index++].Key)
        {
            count++;
        }
    }

    *Key = HashTable->Data[index - 1].Key;

    return 0;
}

int HtClear(CC_HASH_TABLE* HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    if (NULL != HashTable->Data)
    {
        if (0 != HtDestroyData(&HashTable->Data, HashTable->Size, HashTable->Count))
        {
            return -1;
        }
    }

    HashTable->Size = 0;
    HashTable->Count = 0;
    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE* HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    return HashTable->Count;
}

static int HtResize(CC_HASH_TABLE *HashTable, int Up)
{
    int newSize;

    if (Up)
    {
        if (0 == HashTable->Size)
        {
            newSize = 2;
        }
        else
        {
            newSize = HtNextPrime(HashTable->Size * 2);
        }
    }
    else
    {
        if (2 == HashTable->Size)
        {
            return HtClear(HashTable);
        }
        else
        {
            newSize = HtNextPrime(HashTable->Size / 2);
        }
    }

    PCC_HASH_TABLE_DATA data = (PCC_HASH_TABLE_DATA)calloc(newSize, sizeof(CC_HASH_TABLE_DATA));

    if (NULL == data)
    {
        return -1;
    }

    PCC_HASH_TABLE_DATA oldData = HashTable->Data;
    HashTable->Data = data;

    int count = 0, oldCount = HashTable->Count, oldSize = HashTable->Size;

    HashTable->Count = 0;
    HashTable->Size = newSize;

    for (int i = 0; count < oldCount; i++)
    {
        if (NULL != oldData[i].Key)
        {
            if (0 != HtSetKeyValue(HashTable, oldData[i].Key, oldData[i].Value))
            {
                free(data);
                HashTable->Data = oldData;
                HashTable->Count = oldCount;
                HashTable->Size = oldSize;
                return -1;
            }
            count++;
        }
    }    

    return HtDestroyData(&oldData, oldSize, oldCount);
}

static int HtDestroyData(CC_HASH_TABLE_DATA ** Data, int Size, int Count)
{
    if (NULL == Data || Size < 0 || Count < 0 || Count > Size)
    {
        return -1;
    }

    PCC_HASH_TABLE_DATA data = *Data;

    int count = 0;
    for (int i = 0; count < Count; i++)
    {
        if (NULL != (data[i].Key))
        {
            free(data[i].Key);
            data[i].Key = NULL;
            data[i].Value = -1;
            count++;
        }
    }

    free(*Data);
    *Data = NULL;

    return 0;
}

static int HtHash(char *Key)
{
    int hash = 0;
    for (char *i = Key; *i; i++)
    {
        hash += 31 * *i;
    }

    if (hash < 0)
    {
        return -hash;
    }

    return hash;
}

static int HtKeyCompare(char * Key1, char * Key2)
{
    char *i = Key1;
    while (*i)
    {
        if (*i > *(Key2 + (i - Key1)))
        {
            return 1;
        }
        else if (*i < *(Key2 + (i - Key1)))
        {
            return -1;
        }
        i++;
    };

    if (*i > *(Key2 + (i - Key1)))
    {
        return 1;
    }
    else if (*i < *(Key2 + (i - Key1)))
    {
        return -1;
    }

    return 0;
}

static void HtKeyCopy(char *KeySource, char *KeyDestination)
{
    int i;
    for (i = 0; KeySource[i]; i++)
    {
        KeyDestination[i] = KeySource[i];
    }
    KeyDestination[i] = 0;
}

static int HtKeyLength(char *Key)
{
    int i = 0;
    while (Key[i])
    {
        i++;
    }
    return i + 1;
}

static int HtIsPrime(int Number)
{
    if (Number <= 3)
    {
        return Number > 1;
    }
    if (0 == Number % 2 || 0 == Number % 3)
    {
        return 0;
    }

    int i = 5;
    while (i * i <= Number)
    {
        if (Number % i == 0 || (Number + 2) % i == 0)
        {
            return 0;
        }
        i += 6;
    }

    return 1;
}

static int HtNextPrime(int Number)
{
    while (!HtIsPrime(Number))
    {
        Number++;
    }

    return Number;
}
