#include "cctree.h"
#include "common.h"

static int TreeCreateNode(CC_TREE_NODE **Node, int Value);
static int TreeDestroyNode(CC_TREE_NODE **Node);

//Repairs the tree to preserve the red-black tree structure, starting from the inserted node;
static int TreeInsertRepair(CC_TREE_NODE *Node);

int TreeCreate(CC_TREE **Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }

    PCC_TREE tree = malloc(sizeof(CC_TREE));

    if (NULL == tree)
    {
        *Tree = NULL;
        return -1;
    }

    tree->Count = 0;
    tree->Root = NULL;

    *Tree = tree;

    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }


    return -1;
}

int TreeInsert(CC_TREE *Tree, int Value)
{
    if (NULL == Tree)
    {
        return -1;
    }


    PCC_TREE_NODE node;
    PCC_TREE_NODE it = Tree->Root;  //iterator

    if (0 != TreeCreateNode(&node, Value))
    {
        return -1;
    }

    if (NULL == Tree->Root)
    {
        Tree->Root = node;
    }
    else
    {
        while (NULL == node->Parent)
        {
            if (it->Value > Value)
            {
                if (NULL == it->Left)
                {
                    it->Left = node;
                    node->Parent = it;
                }
                else
                {
                    it = it->Left;
                }
            }
            else {
                if (NULL == it->Right)
                {
                    it->Right = node;
                    node->Parent = it;
                }
                else
                {
                    it = it->Right;
                }
            }
        }
    }
  
    return 0;
}

int TreeRemove(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    return -1;
}

int TreeGetHeight(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    return -1;
}

int TreeClear(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    return -1;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

static int TreeCreateNode(CC_TREE_NODE **Node, int Value)
{
    if (NULL == Node)
    {
        return -1;
    }

    PCC_TREE_NODE node = malloc(sizeof(CC_TREE_NODE));

    if (NULL == node)
    {
        *Node = NULL;
        return -1;
    }

    node->Parent = NULL;
    node->Left = NULL;
    node->Right = NULL;
    node->Color = RED;
    node->Value = Value;
    *Node = node;

    return 0;
}

int TreeDestroyNode(CC_TREE_NODE ** Node)
{
    if (NULL == Node)
    {
        return -1;
    }


    return -1;
}

int TreeInsertRepair(CC_TREE_NODE * Node)
{
    return -1;
}
