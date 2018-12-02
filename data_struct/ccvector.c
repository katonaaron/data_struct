#include "ccvector.h"
#include "common.h"

//VecResize increments or decrements the size of the dynamically allocated array
//int Up: selects the incrementation or the decrementation operation
//  Up == 1: increment
//  Up == 0: decrement
static int VecResize(CC_VECTOR *Vector, int Up);

int VecCreate(CC_VECTOR **Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    CC_VECTOR *vector = (CC_VECTOR *)malloc(sizeof(CC_VECTOR));

    if (NULL == vector)
    {
        *Vector = NULL;
        return -1;
    }

    vector->Items = NULL;
    vector->Count = 0;
    vector->Size = 0;

    *Vector = vector;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    free((*Vector)->Items);
    free(*Vector);

    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Size == Vector->Count)
    {
        if (-1 == VecResize(Vector, 1))
        {
            return -1;
        }
    }

    Vector->Items[Vector->Count++] = Value;
    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Size == Vector->Count)
    {
        if (-1 == VecResize(Vector, 1))
        {
            return -1;
        }
    }

    for (int i = Vector->Count; i > 0; i--)
    {
        Vector->Items[i] = Vector->Items[i - 1];
    }

    Vector->Items[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < -1 || Index >= Vector->Count)
    {
        return -1;
    }

    if (Vector->Size == Vector->Count)
    {
        if (-1 == VecResize(Vector, 1))
        {
            return -1;
        }
    }

    for (int i = Vector->Count; i > Index + 1; i--)
    {
        Vector->Items[i] = Vector->Items[i - 1];
    }

    Vector->Items[Index + 1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Count)
    {
        return -1;
    }

    for (int i = Index; i < Vector->Count - 1; i++)
    {
        Vector->Items[i] = Vector->Items[i + 1];
    }

    Vector->Count--;

    if (Vector->Count == Vector->Size / 4)
    {
        if (-1 == VecResize(Vector, 0))
        {
            return -1;
        }
    }

    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    if (NULL == Vector || NULL == Value)
    {
        return -1;
    }

    if (Index < 0 || Index >= Vector->Count)
    {
        return -1;
    }

    *Value = Vector->Items[Index];

    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    free(Vector->Items);
    Vector->Items = NULL;
    Vector->Size = 0;
    Vector->Count = 0;

    return 0;
}

static void QuickSort(int Array[], int Left, int Right)
{
    int i = Left, j = Right, tmp;
    int pivot = Array[(Left + Right) / 2];

    while (i <= j)
    {
        while (Array[i] < pivot)
        {
            i++;
        }
        while (Array[j] > pivot)
        {
            j--;
        }

        if (i <= j)
        {
            tmp = Array[j];
            Array[j] = Array[i];
            Array[i] = tmp;
            i++;
            j--;
        }
    }

    if (Left < j)
    {
        QuickSort(Array, Left, j);
    }
    if (i < Right)
    {
        QuickSort(Array, i, Right);
    }
}

int VecSort(CC_VECTOR *Vector)
{
    if (NULL == Vector || NULL == Vector->Items)
    {
        return -1;
    }

    QuickSort(Vector->Items, 0, Vector->Count - 1);
    return 0;
}

int VecSwap(CC_VECTOR *Vector, int Index1, int Index2)
{
    if (NULL == Vector || Index1 < 0 || Index1 >= Vector->Count || Index2 < 0 || Index2 >= Vector->Count)
    {
        return -1;
    }

    int tmp = Vector->Items[Index1];
    Vector->Items[Index1] = Vector->Items[Index2];
    Vector->Items[Index2] = tmp;
    return 0;
}

static int VecResize(CC_VECTOR *Vector, int Up)
{
    if (NULL == Vector)
    {
        return -1;
    }

    int newSize;

    if (Up)
    {
        if (0 == Vector->Size)
        {
            newSize = 1;
        }
        else
        {
            newSize = Vector->Size * 2;
        }
    }
    else
    {
        if (0 == Vector->Size)
        {
            return -1;
        }
        if (1 == Vector->Size)
        {
            return VecClear(Vector);
        }
        newSize = Vector->Size / 2;
    }

    int *array = (int *)realloc(Vector->Items, sizeof(int) * newSize);

    if (NULL == array)
    {
        return -1;
    }

    Vector->Items = array;
    Vector->Size = newSize;

    return 0;
}