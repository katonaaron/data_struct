#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccvector.h"
#include "ccstack.h"
#include "cchashtable.h"
#include "ccheap.h"
#include "cctree.h"

int TestVector();
int TestStack();
int TestHashTable();
int TestHeap();
int TestTree();

void RunTests();

int FindKey(char *Keys[], int Size, char *Key);

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    RunTests();
    _CrtDumpMemoryLeaks();
    return 0;
}

void RunTests()
{
    /// NOTE: The tests provided here are by no means exhaustive and are only
    /// provided as a starting point (not all functions are tested, not all use cases
    /// and failure scenarios are covered). You are encouraged to expand these tests
    /// to include missing scenarios.
    if (0 == TestVector())
    {
        printf("Vector test passed\n\n");
    }
    else
    {
        printf("Vector test failed\n\n");
    }

    if (0 == TestStack())
    {
        printf("Stack test passed\n\n");
    }
    else
    {
        printf("Stack test failed\n\n");
    }

    if (0 == TestHashTable())
    {
        printf("HashTable test passed\n\n");
    }
    else
    {
        printf("HashTable test failed\n\n");
    }

    if (0 == TestHeap())
    {
        printf("Heap test passed\n\n");
    }
    else
    {
        printf("Heap test failed\n\n");
    }

    if (0 == TestTree())
    {
        printf("Tree test passed\n\n");
    }
    else
    {
        printf("Tree test failed\n\n");
    }
}


int TestTree()
{
    int retVal = -1;
    CC_TREE* usedTree = NULL;

    retVal = TreeCreate(&usedTree);
    if (0 != retVal)
    {
        printf("TreeCreate failed!\n");
        goto cleanup;
    }

    retVal = TreeInsert(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeInsert failed!\n");
        goto cleanup;
    }

    if (1 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = TreeRemove(usedTree, 20);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    if (0 != TreeContains(usedTree, 20))
    {
        printf("TreeContains invalid return value after remove!\n");
        retVal = -1;
        goto cleanup;
    }

    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedTree)
    {
        if (0 != TreeDestroy(&usedTree))
        {
            printf("TreeDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHeap()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HEAP* usedHeap = NULL;

    retVal = HpCreateMinHeap(&usedHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMinHeap failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 20);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    retVal = HpInsert(usedHeap, 10);
    if (0 != retVal)
    {
        printf("HpInsert failed!\n");
        goto cleanup;
    }

    if (2 != HpGetElementCount(usedHeap))
    {
        printf("Invalid element count!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HpGetExtreme(usedHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!\n");
        goto cleanup;
    }

    if (10 != foundVal)
    {
        printf("Invalid minimum value returned!");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedHeap)
    {
        if (0 != HpDestroy(&usedHeap))
        {
            printf("HpDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestHashTable()
{
    int retVal = -1;
    int foundVal = -1;
    char *foundKey = NULL;
    CC_HASH_TABLE* usedTable = NULL;

    //HtCreate Test
    retVal = HtCreate(&usedTable);
    if (0 != retVal)
    {
        printf("HtCreate failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HtCreate(NULL))
    {
        printf("HtCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtHasKey test #1
    retVal = HtHasKey(usedTable, "mere");
    if (0 != retVal)
    {
        printf("HtHasKey failed!: line: %d\n", __LINE__);
        goto cleanup;
    }

    //HtClear test #1
    retVal = HtClear(usedTable);
    if (0 != retVal)
    {
        printf("HtClear failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HtClear(NULL))
    {
        printf("HtClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtGetKeyCount test
    retVal = HtGetKeyCount(usedTable);
    if (0 != retVal)
    {
        printf("HtGetKeyCount failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HtGetKeyCount(NULL))
    {
        printf("HtGetKeyCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtRemoveKey test #1
    retVal = HtRemoveKey(usedTable, "mere");
    if (-1 != retVal)
    {
        printf("HtRemoveKey failed!: line: %d\n", __LINE__);
        goto cleanup;
    }

    //HtGetKeyValue test #1
    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (-1 != retVal)
    {
        printf("HtGetKeyValue failed!: line: %d\n", __LINE__);
        goto cleanup;
    }

    //HtSetKeyValue Test
    retVal = HtSetKeyValue(usedTable, "mere", 20);
    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HtSetKeyValue(NULL, "pere", 10) || -1 != HtSetKeyValue(usedTable, NULL, 10)
        || -1 != HtSetKeyValue(usedTable, "mere", 10))
    {
        printf("HtSetKeyValue failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Get key count, check if has key #1
    if (1 != HtGetKeyCount(usedTable))
    {
        printf("HtGetKeyCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != HtHasKey(usedTable, "mere") || 0 != HtHasKey(usedTable, "pere"))
    {
        printf("HtHasKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtHasKey test #2
    if (-1 != HtHasKey(NULL, "mere") || -1 != HtHasKey(usedTable, NULL))
    {
        printf("HtHasKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtGetKeyValue test #2
    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (0 != retVal)
    {
        printf("HtGetKeyValue failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (20 != foundVal)
    {
        printf("HtGetKeyValue failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != HtGetKeyValue(NULL, "mere", &foundVal) || -1 != HtGetKeyValue(usedTable, NULL, &foundVal)
        || -1 != HtGetKeyValue(usedTable, "mere", NULL))
    {
        printf("HtGetKeyValue failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtGetNthKey test
    retVal = HtGetNthKey(usedTable, 0, &foundKey);
    if (0 != retVal)
    {
        printf("HtGetNthKey failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (0 != strcmp("mere", foundKey))
    {
        printf("Invalid key after HtGetNthKey!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != HtGetNthKey(NULL, 0, &foundKey) || -1 != HtGetNthKey(usedTable, 0, NULL)
        || -1 != HtGetNthKey(usedTable, -1, &foundKey) || -1 != HtGetNthKey(usedTable, 1, &foundKey))
    {
        printf("HtGetNthKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //HtRemoveKey test #1
    if (-1 != HtRemoveKey(usedTable, "cartofi"))
    {
        printf("HtRemoveKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    retVal = HtRemoveKey(usedTable, "mere");
    if (0 != retVal)
    {
        printf("HtRemoveKey failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HtRemoveKey(usedTable, NULL) || -1 != HtRemoveKey(NULL, "mere"))
    {
        printf("HtRemoveKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Get key count, check if has key #2
    if (0 != HtGetKeyCount(usedTable))
    {
        printf("HtGetKeyCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != HtHasKey(usedTable, "mere"))
    {
        printf("HtHasKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //STRUCTURE TEST
    //Insert key-value pairs in order to test the structure
    char *keys[] = { "a", "b", "c", "d", "apple", "cat", "dog", "deoxyribonucleic acid" };
    int values[] = { 1, 2, 3, 4, 123, 23423, 123, 12361273 };

    for (int i = 0; i < 8; i++)
    {
        if (0 != HtSetKeyValue(usedTable, keys[i], values[i]))
        {
            printf("HtSetKeyValue failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Get key count, check if has key #3
    if (8 != HtGetKeyCount(usedTable))
    {
        printf("HtGetKeyCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != HtHasKey(usedTable, "deoxyribonucleic acid"))
    {
        printf("HtHasKey failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Check if every key-value pair are present
    int freq[8] = { 0 }, index;
    for (int i = 0; i < HtGetKeyCount(usedTable); i++)
    {
        if (0 != HtGetNthKey(usedTable, i, &foundKey))
        {
            printf("HtGetNthKey failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (0 != HtGetKeyValue(usedTable, foundKey, &foundVal))
        {
            printf("HtGetNthValue failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        index = FindKey(keys, 8, foundKey);
        if (index == -1 || values[index] != foundVal || 0 != strcmp(keys[index], foundKey))
        {
            printf("HtGetNthValue or HtGetNthKey failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        freq[i]++;
    }
    for (int i = 0; i < 8; i++)
    {
        if (1 != freq[i])
        {
            printf("Structure test failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

cleanup:
    if (-1 != HtDestroy(NULL))
    {
        printf("HtDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (NULL != usedTable)
    {
        if (0 != HtDestroy(&usedTable))
        {
            printf("HtDestroy failed!: line: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (NULL != usedTable)
    {
        printf("HtDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (0 != HtCreate(&usedTable))
    {
        printf("HtCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (0 != HtDestroy(&usedTable))
    {
        printf("HtDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }

    return retVal;
}

int TestStack()
{
    int retVal = -1;
    int foundVal = -1;
    CC_STACK* usedStack = NULL;

    retVal = StCreate(&usedStack);
    if (0 != retVal)
    {
        printf("StCreate failed!\n");
        goto cleanup;
    }

    retVal = StPush(usedStack, 10);
    if (0 != retVal)
    {
        printf("StPush failed!\n");
        goto cleanup;
    }

    if (1 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = StPop(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPop failed!\n");
        goto cleanup;
    }

    if (foundVal != 10)
    {
        printf("Invalid value after pop!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedStack)
    {
        if (0 != StDestroy(&usedStack))
        {
            printf("StDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int TestVector()
{
    int retVal = -1;
    int foundVal = 0;
    CC_VECTOR* usedVector = NULL;

    retVal = VecCreate(&usedVector);
    if (0 != retVal)
    {
        printf("VecCreate failed!\n");
        goto cleanup;
    }

    retVal = VecInsertTail(usedVector, 10);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!\n");
        goto cleanup;
    }

    retVal = VecInsertHead(usedVector, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!\n");
        goto cleanup;
    }

    if (VecGetCount(usedVector) != 2)
    {
        printf("Invalid count returned!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecInsertAfterIndex(usedVector, 0, 20);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!\n");
        goto cleanup;
    }

    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!\n");
        goto cleanup;
    }

    retVal = VecGetValueByIndex(usedVector, 0, &foundVal);
    if (0 != retVal)
    {
        printf("VecGetValueByIndex failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value found at position 0\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = VecClear(usedVector);
    if (0 != retVal)
    {
        printf("VecClear failed!\n");
        goto cleanup;
    }

    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedVector)
    {
        if (0 != VecDestroy(&usedVector))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}

int FindKey(char *Keys[], int Size, char *Key)
{
    if (Size < 1 || NULL == Keys || NULL == Key)
    {
        return -1;
    }
    for (int i = 0; i < Size; i++)
    {
        if (NULL == Keys[i])
        {
            return -1;
        }
        if (0 == strcmp(Key, Keys[i]))
        {
            return i;
        }
    }
    return -1;
}