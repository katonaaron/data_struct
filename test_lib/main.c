#include <stdio.h>
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

int main(void)
{
    RunTests();
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
    CC_HASH_TABLE* usedTable = NULL;

    retVal = HtCreate(&usedTable);
    if (0 != retVal)
    {
        printf("HtCreate failed!\n");
        goto cleanup;
    }

    retVal = HtSetKeyValue(usedTable, "mere", 20);
    if (0 != retVal)
    {
        printf("HtSetKeyValue failed!\n");
        goto cleanup;
    }

    if (1 != HtHasKey(usedTable, "mere"))
    {
        printf("Invalid answer to HtHasKey!\n");
        retVal = -1;
        goto cleanup;
    }

    retVal = HtGetKeyValue(usedTable, "mere", &foundVal);
    if (0 != retVal)
    {
        printf("HtGetKeyValue failed!\n");
        goto cleanup;
    }

    if (foundVal != 20)
    {
        printf("Invalid value after get!\n");
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (NULL != usedTable)
    {
        if (0 != HtDestroy(&usedTable))
        {
            printf("HtDestroy failed!\n");
            retVal = -1;
        }
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

    //Test VecCreate
    retVal = VecCreate(&usedVector);
    if (0 != retVal)
    {
        printf("VecCreate failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != VecCreate(NULL))
    {
        printf("VecCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (0 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecInsertTail
    retVal = VecInsertTail(usedVector, 10);
    if (0 != retVal)
    {
        printf("VecInsertTail failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != VecInsertTail(NULL, 10) || usedVector->Items[0] != 10)
    {
        printf("VecInsertTail failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (1 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecInsertHead
    retVal = VecInsertHead(usedVector, 16);
    if (0 != retVal)
    {
        printf("VecInsertHead failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != VecInsertHead(NULL, 10) || usedVector->Items[0] != 16 || usedVector->Items[1] != 10)
    {
        printf("VecInsertHead failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (2 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecGetCount
    if (VecGetCount(usedVector) != 2 || VecGetCount(usedVector) != usedVector->Count)
    {
        printf("Invalid count returned!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecInsertAfterIndex
    retVal = VecInsertAfterIndex(usedVector, -1, 20);
    if (0 != retVal)
    {
        printf("VecInsertAfterIndex failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != VecInsertAfterIndex(NULL, 0, 10)
        || -1 != VecInsertAfterIndex(usedVector, -2, 20)
        || -1 != VecInsertAfterIndex(usedVector, 3, 20)
        || usedVector->Items[1] != 16
        || usedVector->Items[0] != 20
        || usedVector->Items[2] != 10)
    {
        printf("VecInsertAfterIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (4 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecGetValueByIndex
    retVal = VecGetValueByIndex(usedVector, 0, &foundVal);
    if (0 != retVal
        || -1 != VecGetValueByIndex(NULL, 0, &foundVal)
        || -1 != VecGetValueByIndex(usedVector, 0, NULL)
        || -1 != VecGetValueByIndex(usedVector, -1, &foundVal)
        || -1 != VecGetValueByIndex(usedVector, 5, &foundVal))
    {
        printf("VecGetValueByIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (foundVal != 20)
    {
        printf("Invalid value found at position 0: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecSort
    int freq[100] = { 0 }, prev = -1;
    for (int i = 0; i < VecGetCount(usedVector); i++)
    {
        if (0 != VecGetValueByIndex(usedVector, i, &foundVal))
        {
            printf("VecGetValueByIndex failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        freq[foundVal]++;
    }
    VecSort(usedVector);
    for (int i = 0; i < VecGetCount(usedVector); i++)
    {
        if (0 != VecGetValueByIndex(usedVector, i, &foundVal))
        {
            printf("VecGetValueByIndex failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (i != 0 && foundVal < prev)
        {
            printf("VecSort failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        prev = foundVal;
        freq[foundVal]--;
    }
    for (int i = 0; i < 100; i++)
    {
        if (freq[i] != 0)
        {
            printf("VecSort failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Test VecRemoveByIndex
    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != VecRemoveByIndex(NULL, 0))
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != VecRemoveByIndex(usedVector, -1))
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != VecRemoveByIndex(usedVector, 3))
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (usedVector->Items[0] != 16
        || usedVector->Items[1] != 20
        || VecGetCount(usedVector) != 2)
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (4 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    retVal = VecRemoveByIndex(usedVector, 0);
    if (0 != retVal)
    {
        printf("VecRemoveByIndex failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (2 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test VecClear
    retVal = VecClear(usedVector);
    if (0 != retVal || -1 != VecClear(NULL))
    {
        printf("VecClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != VecGetCount(usedVector))
    {
        printf("Invalid count after clear: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Size test
    if (0 != usedVector->Size)
    {
        printf("The Vector doesn't have the required size!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test the VecResize static function. 
    /*if (-1 != VecResize(NULL, 1)
        || 0 != VecResize(usedVector, 1)
        || 1 != usedVector->Size
        || 0 != VecResize(usedVector, 1)
        || 2 != usedVector->Size
        || 0 != VecResize(usedVector, 1)
        || 4 != usedVector->Size
        || 0 != VecResize(usedVector, 0)
        || 2 != usedVector->Size
        || 0 != VecResize(usedVector, 0)
        || 1 != usedVector->Size
        || 0 != VecResize(usedVector, 0)
        || 0 != usedVector->Size
        || -1 != VecResize(usedVector, 0))
    {
        printf("VecResize failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }*/

cleanup:
    if (NULL != usedVector)
    {
        //Test VecDestroy
        if (0 != VecDestroy(&usedVector)
            || NULL != usedVector
            || -1 != VecDestroy(NULL))
        {
            printf("VecDestroy failed!\n");
            retVal = -1;
        }
    }
    return retVal;
}