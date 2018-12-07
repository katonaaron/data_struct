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

    //Get count, height and see if it contains #1
    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 10))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeInsert Test
    retVal = TreeInsert(usedTree, 10);
    if (0 != retVal)
    {
        printf("TreeInsert failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != TreeInsert(NULL, 10))
    {
        printf("TreeInsert failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Get count, height and see if it contains #2
    if (1 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != TreeContains(usedTree, 10))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeRemove test
    retVal = TreeRemove(usedTree, 10);
    if (0 != retVal)
    {
        printf("TreeRemove failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != TreeRemove(NULL, 10))
    {
        printf("TreeRemove failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Get count, height and see if it contains #3
    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 10))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeContains Test
    if (-1 != TreeContains(NULL, 10))
    {
        printf("TreeContains failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeGetCount Test
    if (-1 != TreeGetCount(NULL))
    {
        printf("TreeGetCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeGetHeight Test
    if (-1 != TreeGetHeight(NULL))
    {
        printf("TreeGetHeight failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeClear Test #1
    retVal = TreeClear(usedTree);
    if (0 != retVal)
    {
        printf("TreeClear failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != TreeClear(NULL))
    {
        printf("TreeClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //STRUCTURE TEST
    //Insert nodes to test the structure
    int nodes[] = { 43, 18, 22, 9, 21, 6, 8, 20, 63, 50, 62, 51, 8 };
    int preorder[] = { 22, 18, 8, 6, 8, 9, 21, 20, 50, 43, 62, 51, 63 };
    int inorder[] = { 6, 8, 8, 9, 18, 20, 21, 22, 43, 50, 51, 62, 63 };
    int postorder[] = { 8, 6, 9, 8, 20, 21, 18, 43, 51, 63, 62, 50, 22 };
    int firstdelete[] = { 22, 18, 9, 6, 21, 20, 50, 43, 62, 51, 63 };
    int seconddelete[] = { 43, 18, 9, 6, 21, 20, 62, 50, 51, 63 };

    for (int i = 0; i < 13; i++)
    {
        retVal = TreeInsert(usedTree, nodes[i]);
        if (0 != retVal)
        {
            printf("TreeInsert failed!: line: %d\n", __LINE__);
            goto cleanup;
        }
    }

    //Get count, height and see if it contains #4
    if (13 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (4 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != TreeContains(usedTree, 8))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //TreeGetNth(Pre/In/Post)order test
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPreorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (foundVal != preorder[i])
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (0 != TreeGetNthInorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthInorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (foundVal != inorder[i])
        {
            printf("TreeGetNthInorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (0 != TreeGetNthPostorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPostorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (foundVal != postorder[i])
        {
            printf("TreeGetNthPostorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //TreeGetNth(Pre/In/Post)order Test
    if (-1 != TreeGetNthPreorder(NULL, 0, &foundVal) || -1 != TreeGetNthPreorder(usedTree, 0, NULL)
        || -1 != TreeGetNthPreorder(usedTree, -1, &foundVal) || -1 != TreeGetNthPreorder(usedTree, 13, &foundVal))
    {
        printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != TreeGetNthInorder(NULL, 0, &foundVal) || -1 != TreeGetNthInorder(usedTree, 0, NULL)
        || -1 != TreeGetNthInorder(usedTree, -1, &foundVal) || -1 != TreeGetNthInorder(usedTree, 13, &foundVal))
    {
        printf("TreeGetNthInorder failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != TreeGetNthPostorder(NULL, 0, &foundVal) || -1 != TreeGetNthPostorder(usedTree, 0, NULL)
        || -1 != TreeGetNthPostorder(usedTree, -1, &foundVal) || -1 != TreeGetNthPostorder(usedTree, 13, &foundVal))
    {
        printf("TreeGetNthPostorder failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test the node removal #1
    retVal = TreeRemove(usedTree, 8);
    if (0 != retVal)
    {
        printf("TreeRemove failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPreorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (foundVal != firstdelete[i])
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Get count, height and see if it contains #5
    if (11 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (3 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 8))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Test the node removal #2
    retVal = TreeRemove(usedTree, 22);
    if (0 != retVal)
    {
        printf("TreeRemove failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    for (int i = 0; i < TreeGetCount(usedTree); i++)
    {
        if (0 != TreeGetNthPreorder(usedTree, i, &foundVal))
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
        if (foundVal != seconddelete[i])
        {
            printf("TreeGetNthPreorder failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Get count, height and see if it contains #6
    if (10 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (3 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 22))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //END STRUCTURE TEST

    // TreeClear Test #1
    retVal = TreeClear(usedTree);
    if (0 != retVal)
    {
        printf("TreeClear failed!: line: %d\n", __LINE__);
        goto cleanup;
    }

    //Get count, height and see if it contains #7
    if (0 != TreeGetCount(usedTree))
    {
        printf("TreeGetCount invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != TreeGetHeight(usedTree))
    {
        printf("TreeGetHeight invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != TreeContains(usedTree, 43))
    {
        printf("TreeContains invalid return value: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

cleanup:
    if (-1 != TreeDestroy(NULL))
    {
        printf("TreeDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    if (NULL != usedTree)
    {
        if (0 != TreeDestroy(&usedTree))
        {
            printf("TreeDestroy failed!: line: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (NULL != usedTree)
    {
        printf("TreeDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
    }
    return retVal;
}

int TestHeap()
{
    int retVal = -1;
    int foundVal = -1;
    CC_HEAP* minHeap = NULL, *maxHeap = NULL, *usedHeap = NULL;;

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
            printf("HpPopExtreme failed!: line: %d\n", __LINE__);
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
            printf("HpPopExtreme failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //Test HpCreate from vector
    //MinHeap
    int values[] = { 43, 18, 22, 9, 21, 6, 8, 20, 63, 50, 62, 51 };
    if (0 != VecClear(minVector))
    {
        printf("VecClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    for (int i = 0; i < 12; i++)
    {
        if (0 != VecInsertTail(minVector, values[i]))
        {
            printf("VecClear failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    if (0 != HpCreateMinHeap(&usedHeap, minVector))
    {
        printf("HpCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    int order[] = { 6, 18, 8, 20, 21, 22, 9, 43,63, 50, 62, 51 };
    int size = HpGetElementCount(usedHeap);
    if (12 != size)
    {
        printf("HpGetElementCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    for (int i = 0; i < 12; i++)
    {
        if (usedHeap->Items->Items[i] != order[i])
        {
            printf("HpCreate from vector failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

    //MaxHeap
    if (0 != HpDestroy(&usedHeap))
    {
        printf("HpDestroy failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != VecClear(minVector))
    {
        printf("VecClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    for (int i = 0; i < 12; i++)
    {
        if (0 != VecInsertTail(minVector, values[i]))
        {
            printf("VecClear failed!: line: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }
    if (0 != HpCreateMaxHeap(&usedHeap, minVector))
    {
        printf("HpCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    int maxOrder[] = {63, 62, 51, 21, 50, 22, 8, 9, 20, 18, 43, 6};
    size = HpGetElementCount(usedHeap);
    if (12 != size)
    {
        printf("HpGetElementCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    for (int i = 0; i < 12; i++)
    {
        if (usedHeap->Items->Items[i] != maxOrder[i])
        {
            printf("HpCreate from vector failed!: line: %d\n", __LINE__);
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
    if (NULL != usedHeap)
    {
        if (0 != HpDestroy(&usedHeap))
        {
            printf("HpDestroy failed!: line: %d\n", __LINE__);
            retVal = -1;
        }
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
    CC_STACK* usedStack = NULL, *usedStack2 = NULL;

    //Test StCreate
    retVal = StCreate(&usedStack);
    if (0 != retVal)
    {
        printf("StCreate failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != StCreate(NULL))
    {
        printf("StCreate failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StGetCount and StIsEmpty test #1
    if (0 != StGetCount(usedStack))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StPush test
    int values[] = { 10, 22, 31, 1, 2, 5, 21, 11, 14, 12};
    for (int i = 0; i < 10; i++)
    {
        retVal = StPush(usedStack, values[i]);
        if (0 != retVal)
        {
            printf("StPush failed!: %d\n", __LINE__);
            goto cleanup;
        }
    }    
    if (-1 != StPush(NULL, 10))
    {
        printf("StPush failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StGetCount and StIsEmpty test #2
    if (10 != StGetCount(usedStack))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StPeek test
    retVal = StPeek(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPeek failed!: %d\n", __LINE__);
        goto cleanup;
    }
    if (foundVal != 12)
    {
        printf("Invalid value after peek!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != StPeek(NULL, &foundVal) || -1 != StPeek(usedStack, NULL))
    {
        printf("StPeek failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StGetCount and StIsEmpty test #3
    if (10 != StGetCount(usedStack))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StPop test
    retVal = StPop(usedStack, &foundVal);
    if (0 != retVal)
    {
        printf("StPop failed!: %d\n", __LINE__);
        goto cleanup;
    }
    if (foundVal != 12)
    {
        printf("Invalid value after pop!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (-1 != StPop(NULL, &foundVal) || -1 != StPop(usedStack, NULL))
    {
        printf("StPop failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }


    //StGetCount and StIsEmpty test #4
    if (9 != StGetCount(usedStack))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StClear test
    retVal = StClear(usedStack);
    if (0 != retVal)
    {
        printf("StClear failed!: line: %d\n", __LINE__);
        goto cleanup;
    }
    if (-1 != StClear(NULL))
    {
        printf("StClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StGetCount and StIsEmpty test #5
    if (0 != StGetCount(usedStack))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (1 != StIsEmpty(usedStack))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StClear test #2 - clear empty vector
    if (0 != StClear(usedStack))
    {
        printf("StClear failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StPop test #2 - pop from empty vector
    retVal = StPop(usedStack, &foundVal);
    if (-1 != retVal)
    {
        printf("StPop failed!: %d\n", __LINE__);
        goto cleanup;
    }
    
    //StPeek test #2 - peek from empty vector
    retVal = StPeek(usedStack, &foundVal);
    if (-1 != retVal)
    {
        printf("StPeek failed!: %d\n", __LINE__);
        goto cleanup;
    }

    //StIsEmpty test
    if (-1 != StIsEmpty(NULL))
    {
        printf("StIsEmpty failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StGetCount test
    if (-1 != StGetCount(NULL))
    {
        printf("StGetCount failed!: line: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //Insert values to test StPushStack
    retVal = StCreate(&usedStack2);
    if (0 != retVal)
    {
        printf("StCreate failed!: line: %d\n", __LINE__);
        goto cleanup;
    }


    int values2[] = { 1, 2, 3, 1, 4, 5 };

    for (int i = 0; i < 3; i++)
    {
        retVal = StPush(usedStack, values2[i]);
        if (0 != retVal)
        {
            printf("StPush failed!: %d\n", __LINE__);
            goto cleanup;
        }
    }

    for (int i = 3; i < 6; i++)
    {
        retVal = StPush(usedStack2, values2[i]);
        if (0 != retVal)
        {
            printf("StPush failed!: %d\n", __LINE__);
            goto cleanup;
        }
    }

    //StGetCount and StIsEmpty test #6
    if (3 != StGetCount(usedStack) || 3 != StGetCount(usedStack2))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != StIsEmpty(usedStack) || 0 != StIsEmpty(usedStack2))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    //StPushStack test
    StPushStack(usedStack, usedStack2);

    //StGetCount and StIsEmpty test #7
    if (6 != StGetCount(usedStack) || 0 != StGetCount(usedStack2))
    {
        printf("StGetCount failed!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }
    if (0 != StIsEmpty(usedStack) || 1 != StIsEmpty(usedStack2))
    {
        printf("Invalid answer to StIsEmpty!: %d\n", __LINE__);
        retVal = -1;
        goto cleanup;
    }

    /*Printing out the values of the 2 stacks
    printf("Stack1: ");
    int vectorSize = VecGetCount(usedStack->Items);
    if (vectorSize < 0)
    {
        return -1;
    }
    for (int i = 0; i < vectorSize; i++)
    {
        retVal = VecGetValueByIndex(usedStack->Items, i, &foundVal);
        if (0 != retVal)
        {
            printf("VecGetValueByIndex failed!: %d\n", __LINE__);
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\nStack2: ");
    vectorSize = VecGetCount(usedStack2->Items);
    if (vectorSize < 0)
    {
        return -1;
    }
    for (int i = 0; i < vectorSize; i++)
    {
        retVal = VecGetValueByIndex(usedStack2->Items, i, &foundVal);
        if (0 != retVal)
        {
            printf("VecGetValueByIndex failed!: %d\n", __LINE__);
            goto cleanup;
        }
        printf("%d ", foundVal);
    }
    printf("\n");*/

    //Check the values
    for (int i = 5; i >= 0; i--)
    {
        retVal = StPop(usedStack, &foundVal);
        if (0 != retVal)
        {
            printf("StPop failed!: %d\n", __LINE__);
            goto cleanup;
        }
        if (foundVal != values2[i])
        {
            printf("Invalid value after pop!: %d\n", __LINE__);
            retVal = -1;
            goto cleanup;
        }
    }

cleanup:
    if (-1 != StDestroy(NULL))
    {
        printf("StDestroy failed!: %d\n", __LINE__);
        retVal = -1;
    }
    if (NULL != usedStack)
    {
        if (0 != StDestroy(&usedStack))
        {
            printf("StDestroy failed!: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (NULL != usedStack2)
    {
        if (0 != StDestroy(&usedStack2))
        {
            printf("StDestroy failed!: %d\n", __LINE__);
            retVal = -1;
        }
    }
    if (-1 != StDestroy(&usedStack))
    {
        printf("StDestroy failed!: %d\n", __LINE__);
        retVal = -1;
    }
    if (-1 != StDestroy(&usedStack2))
    {
        printf("StDestroy failed!: %d\n", __LINE__);
        retVal = -1;
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