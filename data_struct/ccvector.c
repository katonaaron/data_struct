#include "ccvector.h"
#include "common.h"

static int VecResize(CC_VECTOR *Vector, int Up)
{
	int new_size;

	if (Up)
	{
		if (0 == Vector->Size) 
		{
			new_size = 1;
		} 
		else
		{
			new_size = Vector->Size * 2;
		}
	}
	else
	{
		if (1 == Vector->Size)
		{
			return VecClear(Vector);
		}
		new_size = Vector->Size / 2;
	}

	int *arr = (int *)realloc(Vector->Array, sizeof(int) * new_size);

	if (NULL == arr)
	{
		return -1;
	}

	Vector->Array = arr;
	Vector->Size = new_size;

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

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    return -1;
}
