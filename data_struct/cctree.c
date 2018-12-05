#include "cctree.h"
#include "common.h"

static int TreeCreateNode(CC_TREE_NODE **Node, int Value);
static int TreeDestroyNode(CC_TREE_NODE **Node);

//TreeGetHeight returns the height of the (sub)tree where Node is the root
static int TreeGetNodeHeight(CC_TREE_NODE *Node);

//TreeRotateLeft does a left rotation
static int TreeRotateLeft(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeRotateRight does a right rotation
static int TreeRotateRight(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeBalance makes rotations in order to balance the tree.
//The Node will be the starting point, from where we go up and check the other nodes;
static int TreeBalance(CC_TREE *Tree, CC_TREE_NODE *Node);

//Returns the maximum of the given 2 integers
static int Max(int Num1, int Num2);

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

    PCC_TREE tree = *Tree;

    if (-1 == TreeDestroyNode(&tree->Root))
    {
        return -1;
    }

    free(*Tree);
    *Tree = NULL;

    return 0;
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

    Tree->Count++;

    if (NULL == Tree->Root)
    {
        Tree->Root = node;
        return 0;
    }

    while (NULL == node->Parent)
    {
        if (it->Value >= Value)
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

    return TreeBalance(Tree, node);
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
    if (NULL == Tree)
    {
        return -1;
    }

    return TreeGetNodeHeight(Tree->Root) - 1;
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
    node->Height = 1;
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

    PCC_TREE_NODE node = *Node;

    if (NULL != node->Left && 0 != TreeDestroyNode(&node->Left))
    {
        return -1;
    }

    if (NULL != node->Right && 0 != TreeDestroyNode(&node->Right))
    {
        return -1;
    }

    free(*Node);
    *Node = NULL;

    return 0;
}

int TreeGetNodeHeight(CC_TREE_NODE *Node)
{
    if (NULL == Node)
    {
        return 0;
    }
    return Node->Height;
}

static int TreeRotateLeft(CC_TREE *Tree, CC_TREE_NODE *Node)
{
    if (NULL == Node || NULL == Node->Right || NULL == Tree)
    {
        return -1;
    }

    PCC_TREE_NODE child = Node->Right, tmp;

    tmp = Node->Parent;
    Node->Parent = child;
    child->Parent = tmp;
    if (NULL == child->Parent)
    {
        Tree->Root = child;
    }
    else 
    {
        if (child->Parent->Left == Node)
        {
            child->Parent->Left = child;
        }
        else {
            child->Parent->Right = child;
        }
    }

    Node->Right = child->Left;
    child->Left = Node;

    Node->Height = 1 + Max(TreeGetNodeHeight(Node->Left), TreeGetNodeHeight(Node->Right));
    child->Height = 1 + Max(TreeGetNodeHeight(child->Left), TreeGetNodeHeight(child->Right));

    return 0;
}

static int TreeRotateRight(CC_TREE *Tree, CC_TREE_NODE *Node)
{
    if (NULL == Node || NULL == Node->Left || NULL == Tree)
    {
        return -1;
    }

    PCC_TREE_NODE child = Node->Left, tmp;

    tmp = Node->Parent;
    Node->Parent = child;
    child->Parent = tmp;
    if (NULL == child->Parent)
    {
        Tree->Root = child;
    }
    else
    {
        if (child->Parent->Left == Node)
        {
            child->Parent->Left = child;
        }
        else {
            child->Parent->Right = child;
        }
    }
   

    Node->Left = child->Right;
    child->Right = Node;

    Node->Height = 1 + Max(TreeGetNodeHeight(Node->Left), TreeGetNodeHeight(Node->Right));
    child->Height = 1 + Max(TreeGetNodeHeight(child->Left), TreeGetNodeHeight(child->Right));

    return 0;
}

static int TreeBalance(CC_TREE *Tree, CC_TREE_NODE *Node)
{
    if (NULL == Node || NULL == Tree)
    {
        return -1;
    }

    int leafValue = Node->Value;

    while (Node)
    {
        int balance = TreeGetNodeHeight(Node->Left) - TreeGetNodeHeight(Node->Right);
        Node->Height = 1 + Max(TreeGetNodeHeight(Node->Left), TreeGetNodeHeight(Node->Right));


        if (balance > 1)
        {
            
            if (Node->Left->Value >= leafValue)
            {
                //Left Left case
                if (0 != TreeRotateRight(Tree, Node))
                {
                    return -1;
                }
            }
            else
            {
                //Left Right case;
                if (0 != TreeRotateLeft(Tree, Node->Left))
                {
                    return -1;
                }
                if (0 != TreeRotateRight(Tree, Node))
                {
                    return -1;
                }
            }
        }
        else if(balance < -1)
        {
            if (Node->Right->Value >= leafValue)
            {
                //Right Left case
                if (0 != TreeRotateRight(Tree, Node->Right))
                {
                    return -1;
                }
                if (0 != TreeRotateLeft(Tree, Node))
                {
                    return -1;
                }
            }
            else
            {
                //Right Right case;
                if (0 != TreeRotateLeft(Tree, Node))
                {
                    return -1;
                }
            }
        }

        Node = Node->Parent;
    }

    return 0;
}

static int Max(int Num1, int Num2)
{
    return Num1 > Num2 ? Num1 : Num2;
}
