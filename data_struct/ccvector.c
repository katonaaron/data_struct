#include "ccvector.h"
#include "common.h"

static int VecResize(CC_VECTOR *Vector, int Up)
{
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
        if (1 == Vector->Size)
        {
            return VecClear(Vector);
        }
        newSize = Vector->Size / 2;
    }

    int *arr = (int *)realloc(Vector->Array, sizeof(int) * newSize);

    if (NULL == arr)
    {
        return -1;
    }

    Vector->Array = arr;
    Vector->Size = newSize;

    return 0;
}

int VecCreate(CC_VECTOR **Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    CC_VECTOR *vec = (CC_VECTOR *)malloc(sizeof(CC_VECTOR));

    if (NULL == vec)
    {
        return -1;
    }

    vec->Array = NULL;
    vec->Count = 0;
    vec->Size = 0;

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    if (NULL == Vector)
    {
        return -1;
    }

    CC_VECTOR *vec = *Vector;

    free(vec->Array);
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

    Vector->Array[Vector->Count++] = Value;
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
        Vector->Array[i] = Vector->Array[i - 1];
    }

    Vector->Array[0] = Value;
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
        Vector->Array[i] = Vector->Array[i - 1];
    }

    Vector->Array[Index + 1] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    if (NULL == Vector)
    {
        return -1;
    }

    if (Index < 0 && Index >= Vector->Count)
    {
        return -1;
    }

    for (int i = Index; i < Vector->Count - 1; i++)
    {
        Vector->Array[i] = Vector->Array[i + 1];
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

    *Value = Vector->Array[Index];

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

    free(Vector->Array);
    Vector->Array = NULL;
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
            j++;
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
    if (NULL == Vector || NULL == Vector->Array)
    {
        return -1;
    }

    QuickSort(Vector->Array, 0, Vector->Count - 1);
    return 0;
}
