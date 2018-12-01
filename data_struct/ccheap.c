#include "ccheap.h"
#include "common.h"

//HpCreateHeap creates and initializes a heap
//CC_HEAP_TYPE Type parameter can be MIN_HEAP = 0 or MAX_HEAP = 1
//    this will define the type of the heap
static int HpCreateHeap(CC_HEAP **Heap, CC_HEAP_TYPE Type);

//HpLoadVector loads a CC_VECTOR into a CC_HEAP
static int HpLoadVector(CC_HEAP *Heap, CC_VECTOR* InitialElements);

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    if (-1 == HpCreateHeap(MaxHeap, MAX_HEAP))
    {
        return -1;
    }

    if (NULL != InitialElements)
    {
        if (-1 == HpLoadVector(*MaxHeap, InitialElements))
        {
            HpDestroy(MaxHeap);
            return -1;
        }
    }

    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    if (-1 == HpCreateHeap(MinHeap, MIN_HEAP))
    {
        return -1;
    }

    if (NULL != InitialElements)
    {
        if (-1 == HpLoadVector(*MinHeap, InitialElements))
        {
            HpDestroy(MinHeap);
            return -1;
        }
    }

    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    if (NULL == Heap)
    {
        return -1;
    }

    free((*Heap)->Items);
    free(*Heap);

    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    return -1;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    return -1;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    return -1;
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);
    return -1;
}

static int HpCreateHeap(CC_HEAP **Heap, CC_HEAP_TYPE Type)
{
    if (NULL == Heap)
    {
        return -1;
    }

    PCC_HEAP heap = (PCC_HEAP)malloc(sizeof(CC_HEAP));

    if (NULL == heap)
    {
        *Heap = NULL;
        return -1;
    }

    heap->Type = Type;
    heap->Items = NULL;
    heap->Count = 0;
    heap->Size = 0;

    *Heap = heap;
    return 0;
}

static int HpLoadVector(CC_HEAP *Heap, CC_VECTOR* InitialElements)
{
    if (NULL == Heap || NULL == InitialElements)
    {
        return -1;
    }

    int vectorSize = VecGetCount(InitialElements), element;
    for (int i = 0; i < vectorSize; i++)
    {
        if (-1 == VecGetValueByIndex(InitialElements, i, &element))
        {
            return -1;
        }
        if (-1 == HpInsert(Heap, element))
        {
            return -1;
        }
    }

    return 0;
}
