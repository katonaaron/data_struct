#include "cchashtable.h"
#include "common.h"

//VecResize increments or decrements the size of the dynamically allocated array
//int Up: selects the incrementation or the decrementation operation
//  Up == 1: increment
//  Up == 0: decrement
static int HtResize(CC_HASH_TABLE *HashTable, int Up);

//HtHash generates a hash for a given key
static int HtHash(char *Key);

//Compares two keys alphabetically
//Returns:
//  <0:	the first character that does not match has a lower value in Key1 than in Key2
//  0:	the contents of both strings are equal
//  >0:	the first character that does not match has a greater value in Key1 than in Key2
static int HtKeyCompare(char *Key1, char *Key2);

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

    free((*HashTable)->Data);
    free(*HashTable);

    return 0;
}

int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value)
{
    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    if (0 != HtHasKey(HashTable, Key))
    {
        return -1;
    }

    if (0 == HashTable->Size || (HashTable->Count + 1.0) / HashTable->Size > CC_MAX_LOAD_FACTOR) {
        if (-1 == HtResize(HashTable, 1))
        {
            return -1;
        }
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 0; NULL != HashTable->Data[index].Key; i++)
    {
        index = (hash + i * i) % HashTable->Size;
    }

    HashTable->Data[index].Key = Key;
    HashTable->Data[index].Value = Value;
    HashTable->Count++;

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value)
{
    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 0; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            return HashTable->Data[index].Value;
        }
        index = (hash + i * i) % HashTable->Size;
    }
    return -1;
}

int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    return -1;
}

int HtHasKey(CC_HASH_TABLE* HashTable, char* Key)
{
    if (NULL == HashTable || NULL == Key)
    {
        return -1;
    }

    int hash = HtHash(Key);
    int index = hash % HashTable->Size;

    for (int i = 0; NULL != HashTable->Data[index].Key || 0 != HashTable->Data[index].Value; i++)
    {
        if (NULL != HashTable->Data[index].Key && 0 == HtKeyCompare(HashTable->Data[index].Key, Key))
        {
            return 1;
        }
        index = (hash + i * i) % HashTable->Size;
    }
    return 0;
}

int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Key);
    return -1;
}

int HtClear(CC_HASH_TABLE* HashTable)
{
    if (NULL == HashTable)
    {
        return -1;
    }

    free(HashTable->Data);
    HashTable->Data = NULL;
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

    PCC_HASH_TABLE_DATA data = (PCC_HASH_TABLE_DATA)calloc(newSize, sizeof(CC_HASH_TABLE_DATA)), dataOld;

    if (NULL == data)
    {
        return -1;
    }

    dataOld = HashTable->Data;
    HashTable->Data = data;

    int count = 0;
    for (int i = 0; i < HashTable->Size && count < HashTable->Count; i++)
    {
        if (NULL != dataOld[i].Key)
        {
            if (0 != HtSetKeyValue(HashTable, dataOld[i].Key, dataOld[i].Value))
            {
                free(data);
                HashTable->Data = dataOld;
                return -1;
            }
            count++;
        }
    }

    HashTable->Size = newSize;

    return 0;
}

static int HtHash(char *Key)
{
    return -1;
}

int HtKeyCompare(char * Key1, char * Key2)
{
    for (char *i = Key1; *i; i++)
    {
        if (*i > *(Key2 + (i - Key1)))
        {
            return 1;
        }
        else if (*i < *(Key2 + (i - Key1)))
        {
            return -1;
        }
    }
    return 0;
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

int HtNextPrime(int Number)
{
    while (!HtIsPrime(Number))
    {
        Number++;
    }

    return Number;
}
