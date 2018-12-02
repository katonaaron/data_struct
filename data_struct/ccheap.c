#include "ccheap.h"
#include "common.h"

//HpCreateHeap creates and initializes a heap
//CC_HEAP_TYPE Type parameter can be MIN_HEAP = 0 or MAX_HEAP = 1
//    this will define the type of the heap
static int HpCreateHeap(CC_HEAP **Heap, CC_HEAP_TYPE Type);

//HpHeapifyVector loads a CC_VECTOR into a CC_HEAP
static int HpHeapifyVector(CC_HEAP *Heap, CC_VECTOR* InitialElements);

//Compares two values according to the type of the heap.
//Returns:  1 - Num1 should be higher then Num2 in the tree. (So SiftUp might be needed)
//          0 - Num1 shouldn't be higher then Num2 in the tree.
//          -1 - Error
static int HpCompare(int Num1, int Num2, CC_HEAP_TYPE Type);

//HpSift sifts a node up to preserve the heap structure
static int HpSiftUp(CC_HEAP *Heap, int Node);

//HpSift sifts a node down to preserve the heap structure
static int HpSiftDown(CC_HEAP *Heap, int Node);

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    if (0 != HpCreateHeap(MaxHeap, MAX_HEAP))
    {
        return -1;
    }

    if (NULL != InitialElements)
    {
        if (0 != HpHeapifyVector(*MaxHeap, InitialElements))
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
        if (0 != HpHeapifyVector(*MinHeap, InitialElements))
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

    int vectorSize = VecGetCount(vector);

    if (vectorSize < 0)
    {
        return -1;
    }

    HpSiftUp(Heap, vectorSize - 1);

    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    if (NULL == Heap || NULL == Heap->Items)
    {
        return -1;
    }

    PCC_VECTOR vector = Heap->Items;

    int vectorSize = VecGetCount(vector), element;

    if (vectorSize < 0)
    {
        return -1;
    }

    for (int i = vectorSize - 1; i >= 0; i--)
    {
        if (0 != VecGetValueByIndex(vector, i, &element))
        {
            return -1;
        }
        if (element == Value)
        {
            if (0 != VecSwap(vector, i, vectorSize - 1))
            {
                return -1;
            }
            if (0 != VecRemoveByIndex(vector, vectorSize - 1))
            {
                return -1;
            }
            vectorSize--;
            if (vectorSize)
            {
                if (0 != HpSiftUp(Heap, i))
                {
                    return -1;
                }
                if (0 != HpSiftDown(Heap, i))
                {
                    return -1;
                }
            }
        }

    }

    return 0;
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
    int extremeValue;

    if (0 != HpGetExtreme(Heap, &extremeValue))
    {
        return -1;
    }
    if (0 != HpRemove(Heap, extremeValue))
    {
        return -1;
    }
    *ExtremeValue = extremeValue;

    return 0;
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
    if (NULL == Heap || NULL == Heap->Items || NULL == SortedVector)
    {
        return -1;
    }

    PCC_VECTOR vector = Heap->Items;
    int vectorSize = VecGetCount(vector), element;
    if (vectorSize < 0)
    {
        return -1;
    }

    for (int i = 0; i < vectorSize; i++)
    {
        if (0 != VecGetValueByIndex(vector, i, &element))
        {
            return -1;
        }
        if (0 != VecInsertTail(SortedVector, element))
        {
            return -1;
        }
    }

    if (0 != VecSort(SortedVector))
    {
        return -1;
    }
    return 0;
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

static int HpHeapifyVector(CC_HEAP *Heap, CC_VECTOR* InitialElements)
{
    if (NULL == Heap || NULL == Heap->Items || NULL == InitialElements)
    {
        return -1;
    }

    int vectorSize = VecGetCount(InitialElements), element;
    if (vectorSize < 0)
    {
        return -1;
    }

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

static int HpCompare(int Num1, int Num2, CC_HEAP_TYPE Type)
{
    switch (Type)
    {
    case MIN_HEAP:
        return Num1 < Num2;
        break;
    case MAX_HEAP:
        return Num1 > Num2;
        break;
    default:
        return -1;
        break;
    }
}

static int HpSiftUp(CC_HEAP *Heap, int Node)
{
    if (NULL == Heap || NULL == Heap->Items)
    {
        return -1;
    }

    PCC_VECTOR vector = Heap->Items;

    int vectorSize = VecGetCount(vector);

    if (vectorSize < 0 || Node < 0 || Node >= vectorSize)
    {
        return -1;
    }

    int parent, nodeValue, parentValue, compare;

    while (Node)
    {
        parent = (Node - 1) / 2;

        if (0 != VecGetValueByIndex(vector, Node, &nodeValue) || 0 != VecGetValueByIndex(vector, parent, &parentValue))
        {
            return -1;
        }

        compare = HpCompare(nodeValue, parentValue, Heap->Type);
        if (compare < 0)
        {
            return -1;
        }
        if (compare)
        {
            if (0 != VecSwap(vector, Node, parent))
            {
                return -1;
            }
        }

        Node = parent;
    }


    return 0;
}

static int HpSiftDown(CC_HEAP *Heap, int Node)
{
    if (NULL == Heap || NULL == Heap->Items)
    {
        return -1;
    }

    PCC_VECTOR vector = Heap->Items;

    int vectorSize = VecGetCount(vector);

    if (vectorSize < 0 || Node < 0 || Node >= vectorSize)
    {
        return -1;
    }

    int child, nodeValue, childValue, child2Value, compare;

    while ((child = Node * 2 + 1) < vectorSize)
    {

        if (0 != VecGetValueByIndex(vector, Node, &nodeValue) || 0 != VecGetValueByIndex(vector, child, &childValue))
        {
            return -1;
        }

        if (child + 1 < vectorSize)
        {
            if (0 != VecGetValueByIndex(vector, child + 1, &child2Value))
            {
                return -1;
            }

            compare = HpCompare(child2Value, childValue, Heap->Type);
            if (compare < 0)
            {
                return -1;
            }
            if (compare)
            {
                childValue = child2Value;
                child++;
            }
        }

        compare = HpCompare(childValue, nodeValue, Heap->Type);
        if (compare < 0)
        {
            return -1;
        }
        if (compare)
        {
            if (0 != VecSwap(vector, Node, child))
            {
                return -1;
            }
        }

        Node = child;
    }


    return 0;
}
