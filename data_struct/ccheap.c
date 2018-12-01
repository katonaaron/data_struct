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
    if (0 != HpCreateHeap(MaxHeap, MAX_HEAP))
    {
        return -1;
    }

    if (NULL != InitialElements)
    {
        if (0 != HpLoadVector(*MaxHeap, InitialElements))
        {
            HpDestroy(MaxHeap);
            return -1;
        }
    }

    return 0;
}

int HpCreateMinHeap(CC_HEAP **MinHeap, CC_VECTOR* InitialElements)
{
    if (0 != HpCreateHeap(MinHeap, MIN_HEAP))
    {
        return -1;
    }

    if (NULL != InitialElements)
    {
        if (0 != HpLoadVector(*MinHeap, InitialElements))
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

    if (NULL != (*Heap)->Items)
    {
        PCC_VECTOR vector = (*Heap)->Items;
        if (0 != VecDestroy(&vector))
        {
            return -1;
        }
    }

    free(*Heap);
    *Heap = NULL;
    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    if (NULL == Heap || NULL == Heap->Items)
    {
        return -1;
    }

    PCC_VECTOR vector = Heap->Items;

    if (0 != VecInsertTail(vector, Value))
    {
        return -1;
    }

    int child = VecGetCount(vector) - 1;
    int parent, childValue, parentValue;
    int mustSwap = 0;

    while (child)
    {
        parent = (child - 1) / 2;
        if (0 != VecGetValueByIndex(vector, child, &childValue)
            || 0 != VecGetValueByIndex(vector, parent, &parentValue))
        {
            return -1;
        }

        switch (Heap->Type)
        {
        case MIN_HEAP:
            mustSwap = childValue < parentValue;
            break;
        case MAX_HEAP:
            mustSwap = childValue > parentValue;
            break;
        default:
            return -1;
            break;
        }

        if (mustSwap)
        {
            if (0 != VecSwap(vector, child, parent))
            {
                return -1;
            }
        }

        child = parent;
    }

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    if (NULL == Heap || NULL == Heap->Items || NULL == ExtremeValue)
    {
        return -1;
    }

    int extreme;
    if (0 != VecGetValueByIndex(Heap->Items, 0, &extreme))
    {
        return -1;
    }

    *ExtremeValue = extreme;

    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    return -1;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    if (NULL == Heap || NULL == Heap->Items)
    {
        return -1;
    }

    return VecGetCount(Heap->Items);
}

int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);
    return -1;
}

static int HpCreateHeap(CC_HEAP **Heap, CC_HEAP_TYPE Type)
{
    if (NULL == Heap || MIN_HEAP != Type && MAX_HEAP != Type)
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

    PCC_VECTOR vector;

    if (0 != VecCreate(&vector))
    {
        HpDestroy(&heap);
        *Heap = NULL;
        return -1;
    }

    heap->Items = vector;
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
        if (0 != VecGetValueByIndex(InitialElements, i, &element))
        {
            return -1;
        }
        if (0 != HpInsert(Heap, element))
        {
            return -1;
        }
    }

    return 0;
}
