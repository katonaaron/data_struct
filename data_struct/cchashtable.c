#include "cchashtable.h"
#include "common.h"

//VecResize increments or decrements the size of the dynamically allocated array
//int Up: selects the incrementation or the decrementation operation
//  Up == 1: increment
//  Up == 0: decrement
static int HtResize(CC_HASH_TABLE *HashTable, int Up);

//HtHash generates a hash for a given key
static int HtHash(char *Key);

//HtIsPrime determines if a given number is a prime number
static int HtIsPrime(int Number);

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

    if (0 == HashTable->Size || (HashTable->Count + 1) / HashTable->Size > CC_MAX_LOAD_FACTOR) {
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
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);
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
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    return -1;
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
    return -1;
}

static int HtHash(char *Key)
{
    return -1;
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
