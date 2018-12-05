#pragma once

//The hash table is implemented as a dynamic array made of pairs of keys and values.
//Quadratic Probing is used. The elements of the array have the following property: 
//  if(NULL == Key)
//      if(0 == Value)
//          empty slot
//      else
//          deleted slot

//The maximal load factor (nr of elements / size of an array), after which the
//size of the array will be increased and the values of the hashtable will be rehashed
#define CC_MAX_LOAD_FACTOR 0.6

//The minimal load factor (nr of elements / size of an array), after which the
//size of the array will be decreased and the values of the hashtable will be rehashed
#define CC_MIN_LOAD_FACTOR 0.2

typedef struct _CC_HASH_TABLE_DATA {
    char *Key;
    int Value;
}CC_HASH_TABLE_DATA, *PCC_HASH_TABLE_DATA;

typedef struct _CC_HASH_TABLE { 
    // Members
    CC_HASH_TABLE_DATA *Data;
    int Size;
    int Count;
} CC_HASH_TABLE, *PCC_HASH_TABLE; 
  
int HtCreate(CC_HASH_TABLE** HashTable); 
int HtDestroy(CC_HASH_TABLE** HashTable); 
 
int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value); 
int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value); 
int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key); 
int HtHasKey(CC_HASH_TABLE* HashTable, char* Key); 
int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key); 
int HtClear(CC_HASH_TABLE* HashTable); 
int HtGetKeyCount(CC_HASH_TABLE* HashTable);  
