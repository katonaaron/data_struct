#include "ccstack.h"
#include "common.h"

int StCreate(CC_STACK **Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    PCC_STACK stack = (PCC_STACK)malloc(sizeof(CC_STACK));

    if (NULL == stack)
    {
        *Stack = NULL;
        return -1;
    }

    if (0 != VecCreate(&stack->Items))
    {
        free(stack);
        *Stack = NULL;
        return -1;
    }

    *Stack = stack;
    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }

    if (0 != VecDestroy(&(*Stack)->Items))
    {
        return -1;
    }

    free(*Stack);
    *Stack = NULL;
    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    if (NULL == Stack)
    {
        return -1;
    }
    return VecInsertTail(Stack->Items, Value);
}

int StPop(CC_STACK *Stack, int *Value)
{
    if (NULL == Stack || NULL == Value)
    {
        return - 1;
    }

    int foundVal;
    int index = VecGetCount(Stack->Items);

    if (index < 1)
    {
        return -1;
    }

    if (0 != StPeek(Stack, &foundVal))
    {
        return -1;
    }
    
    if (0 != VecRemoveByIndex(Stack->Items, --index))
    {
        return -1;
    }

    *Value = foundVal;
    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    if(NULL == Stack || NULL == Value)
    {
        return -1;
    }

    int foundVal;
    int index = VecGetCount(Stack->Items);

    if (index < 1)
    {
        return -1;
    }

    if (0 != VecGetValueByIndex(Stack->Items, --index, &foundVal))
    {
        return -1;
    }
    
    *Value = foundVal;
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }
    int count = StGetCount(Stack);
    if (count < 0)
    {
        return -1;
    }
    return count == 0;
}

int StGetCount(CC_STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }
    return VecGetCount(Stack->Items);
}

int StClear(CC_STACK *Stack)
{
    if (NULL == Stack)
    {
        return -1;
    }
    return VecClear(Stack->Items);
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    if (NULL == Stack || NULL == StackToPush)
    {
        return -1;
    }

    int foundValue;
    int vectorSize = VecGetCount(StackToPush->Items);

    if (vectorSize < 0)
    {
        return -1;
    }

    for(int i=0; i<vectorSize; i++)
    {
        if (0 != VecGetValueByIndex(StackToPush->Items, i, &foundValue))
        {
            return -1;
        }
        if (0 != StPush(Stack, foundValue))
        {
            return -1;
        }
    }

    return VecClear(StackToPush->Items);
}
