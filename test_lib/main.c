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
    int foundVal;
    CC_TREE* usedTree = NULL;

    //TreeCreate Test
    retVal = TreeCreate(&usedTree);
    if (0 != retVal)
    {
        printf("TreeCreate failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != TreeCreate(NULL))
    {
        printf("TreeCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Structure Test

    int nodes[] = { 43, 18, 22, 9, 21, 6, 8, 20, 63, 50, 62, 51, 8 };

    for (int i = 0; i < 13; i++)
    {
        retVal = TreeInsert(usedTree, nodes[i]);
        if (0 != retVal)
        {
            printf("TreeInsert failed!: line: %d\n", __LINE__);
            goto cleanup;
        }
    }

    printf("Preorder: ");
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPreorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\n");
    printf("Inorder: ");
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthInorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthInorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\n");
    printf("Postorder: ");
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPostorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPostorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\n");

    retVal = TreeRemove(usedTree, 8);
    if (0 != retVal)
    {
        printf("TreeRemove failed!\n");
        goto cleanup;
    }

    printf("Tree: ");
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPreorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\n");

    //End Structure Test
    /*retVal = TreeInsert(usedTree, 20);
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
    }*/

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
    CC_HEAP* minHeap = NULL, *maxHeap = NULL;

    //Test HpCreateMinHeap
    retVal = HpCreateMinHeap(&minHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMinHeap failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HpCreateMinHeap(NULL, NULL))
    {
        printf("HpCreateMinHeap failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test HpCreateMaxHeap
    retVal = HpCreateMaxHeap(&maxHeap, NULL);
    if (0 != retVal)
    {
        printf("HpCreateMaxHeap failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != HpCreateMaxHeap(NULL, NULL))
    {
        printf("HpCreateMaxHeap failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TODO: heapify vector

    //Test HpInsert
    if (-1 != HpInsert(NULL, 1))
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    retVal = HpInsert(minHeap, 1);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(minHeap, 6);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (2 != HpGetElementCount(minHeap))
    {
        printf("Invalid element count!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != minHeap->Items->Items[0] && 6 != minHeap->Items->Items[0])
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 1);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 6);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (2 != HpGetElementCount(maxHeap))
    {
        printf("Invalid element count!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (6 != minHeap->Items->Items[0] && 1 != minHeap->Items->Items[0])
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test HpGetExtreme
    retVal = HpGetExtreme(minHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (1 != foundVal)
    {
        printf("Invalid minimum value returned!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    retVal = HpGetExtreme(maxHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpGetExtreme failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (6 != foundVal)
    {
        printf("Invalid minimum value returned!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Insert additional elements to test the other functions
    retVal = HpInsert(minHeap, 2);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(minHeap, 7);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(minHeap, 8);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(minHeap, 3);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 2);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 7);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 8);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    retVal = HpInsert(maxHeap, 3);
    if (0 != retVal)
    {
        printf("HpInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }

    if (6 != HpGetElementCount(maxHeap) || 6 != HpGetElementCount(minHeap))
    {
        printf("Invalid element count!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test structure
    PCC_VECTOR minVector, maxVector;
    VecCreate(&minVector);
    VecCreate(&maxVector);
    VecInsertTail(minVector, 1);
    VecInsertTail(minVector, 6);
    VecInsertTail(minVector, 2);
    VecInsertTail(minVector, 7);
    VecInsertTail(minVector, 8);
    VecInsertTail(minVector, 3);
    VecInsertTail(maxVector, 8);
    VecInsertTail(maxVector, 7);
    VecInsertTail(maxVector, 3);
    VecInsertTail(maxVector, 1);
    VecInsertTail(maxVector, 6);
    VecInsertTail(maxVector, 2);

    for (int i = 0; i < minVector->Count; i++)
    {
        if (minHeap->Items->Items[i] != minVector->Items[i])
        {
            printf("Invalid minimum heap structure!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    for (int i = 0; i < maxVector->Count; i++)
    {
        if (maxHeap->Items->Items[i] != maxVector->Items[i])
        {
            printf("Invalid maximum heap structure!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Test HpSortToVector
    PCC_VECTOR sortedVector;
    retVal = VecCreate(&sortedVector);

    if (-1 != HpSortToVector(NULL, sortedVector) || -1 != HpSortToVector(minHeap, NULL))
    {
        printf("HpSortToVector failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    retVal = HpSortToVector(minHeap, sortedVector);
    if (0 != retVal)
    {
        printf("HpSortToVector failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    for (int i = 0; i < minVector->Count; i++)
    {
        if (minHeap->Items->Items[i] != minVector->Items[i])
        {
            printf("HpSortToVector failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    VecSort(minVector);
    for (int i = 0; i < minVector->Count; i++)
    {
        if (sortedVector->Items[i] != minVector->Items[i])
        {
            printf("HpSortToVector failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    VecClear(sortedVector);
    retVal = HpSortToVector(maxHeap, sortedVector);
    if (0 != retVal)
    {
        printf("HpSortToVector failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    for (int i = 0; i < maxVector->Count; i++)
    {
        if (maxHeap->Items->Items[i] != maxVector->Items[i])
        {
            printf("HpSortToVector failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    VecSort(maxVector);
    for (int i = 0; i < maxVector->Count; i++)
    {
        if (sortedVector->Items[i] != maxVector->Items[i])
        {
            printf("HpSortToVector failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Test HpRemove
    retVal = HpRemove(minHeap, 7);
    if (0 != retVal)
    {
        printf("HpRemove failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    VecClear(minVector);
    VecInsertTail(minVector, 1);
    VecInsertTail(minVector, 3);
    VecInsertTail(minVector, 2);
    VecInsertTail(minVector, 6);
    VecInsertTail(minVector, 8);
    for (int i = 0; i < minVector->Count; i++)
    {
        if (minHeap->Items->Items[i] != minVector->Items[i])
        {
            printf("HpRemove failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    retVal = HpRemove(maxHeap, 7);
    if (0 != retVal)
    {
        printf("HpRemove failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    VecClear(maxVector);
    VecInsertTail(maxVector, 8);
    VecInsertTail(maxVector, 6);
    VecInsertTail(maxVector, 3);
    VecInsertTail(maxVector, 1);
    VecInsertTail(maxVector, 2);
    for (int i = 0; i < maxVector->Count; i++)
    {
        if (maxHeap->Items->Items[i] != maxVector->Items[i])
        {
            printf("HpRemove failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Test HpPopExtreme
    retVal = HpPopExtreme(minHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpPopExtreme failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != foundVal)
    {
        printf("HpPopExtreme failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    retVal = HpPopExtreme(maxHeap, &foundVal);
    if (0 != retVal)
    {
        printf("HpPopExtreme failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (8 != foundVal)
    {
        printf("HpPopExtreme failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    VecClear(minVector);
    VecInsertTail(minVector, 2);
    VecInsertTail(minVector, 3);
    VecInsertTail(minVector, 8);
    VecInsertTail(minVector, 6);
    for (int i = 0; i < minVector->Count; i++)
    {
        if (minHeap->Items->Items[i] != minVector->Items[i])
        {
            printf("HpRemove failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    VecClear(maxVector);
    VecInsertTail(maxVector, 6);
    VecInsertTail(maxVector, 2);
    VecInsertTail(maxVector, 3);
    VecInsertTail(maxVector, 1);
    for (int i = 0; i < maxVector->Count; i++)
    {
        if (maxHeap->Items->Items[i] != maxVector->Items[i])
        {
            printf("HpRemove failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

cleanup:
    if (-1 != HpDestroy(NULL))
    {
        printf("HpDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (NULL != minHeap)
    {
        if (0 != HpDestroy(&minHeap))
        {
            printf("HpDestroy failed!: line: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (NULL != maxHeap)
    {
        if (0 != HpDestroy(&maxHeap))
        {
            printf("HpDestroy failed!: line: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (0 != VecDestroy(&minVector))
    {
        printf("VecDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (0 != VecDestroy(&maxVector))
    {
        printf("VecDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (0 != VecDestroy(&sortedVector))
    {
        printf("VecDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
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

    //Test VecSwap
    if (-1 != VecSwap(NULL, 0, 0)
        || 0 != VecInsertTail(usedVector, 2)
        || 0 != VecInsertTail(usedVector, 3)
        || 0 != VecSwap(usedVector, 0, 1)
        || 3 != usedVector->Items[0]
        || 2 != usedVector->Items[1]
        || -1 != VecSwap(usedVector, -1, 0)
        || -1 != VecSwap(usedVector, 0, -1)
        || -1 != VecSwap(usedVector, 2, 0)
        || -1 != VecSwap(usedVector, 0, 2)
        )
    {
        printf("VecSwap failed!: line: %d\n", __LINE__);
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