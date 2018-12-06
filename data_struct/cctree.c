#include "cctree.h"
#include "common.h"

static int TreeCreateNode(CC_TREE_NODE **Node, int Value);
static int TreeDestroyNode(CC_TREE_NODE **Node, int Recursively);


//TreeRemoveNode removes a node from the tree
static int TreeRemoveNode(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeGetMinNode gives the Node parameter the address of the node with the value = Value, from the 
//subtree given by the Root node.
static int TreeFindNode(CC_TREE_NODE *Root, int Value, CC_TREE_NODE **Node);

//TreeGetHeight returns the height of the (sub)tree where Node is the root
static int TreeGetNodeHeight(CC_TREE_NODE *Node);

//TreeGetMinNode gives the Node parameter the address of the node with the smallest value in the 
//subtree given by the Root node.
static int TreeGetMinNode(CC_TREE_NODE *Root, CC_TREE_NODE **Node);

//TreeRotateLeft does a left rotation
static int TreeRotateLeft(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeRotateRight does a right rotation
static int TreeRotateRight(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeBalance makes rotations in order to balance the tree.
//The Node will be the starting point, from where we go up and check the other nodes;
static int TreeBalance(CC_TREE *Tree, CC_TREE_NODE *Node);

//TreeGetBalanceFactor returns the balance factor of the node:
//  height(left child) - hight(right child)
static int TreeGetBalanceFactor(CC_TREE_NODE *Node);

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

    if (-1 == TreeDestroyNode(&tree->Root, 1))
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
    if (NULL == Tree)
    {
        return -1;
    }

    PCC_TREE_NODE foundNode = NULL;

    if (0 != TreeFindNode(Tree->Root, Value, &foundNode))
    {
        return -1;
    }

    int found = 0;

    while (NULL != foundNode)
    {
        if (0 != TreeRemoveNode(Tree, foundNode))
        {
            return -1;
        }
        if (0 != TreeFindNode(Tree->Root, Value, &foundNode))
        {
            return -1;
        }
        found = 1;
        Tree->Count--;
    }

    if (!found)
    {
        return -1;
    }
    return 0;
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    return -1;
}

int TreeGetCount(CC_TREE *Tree)
{
    if (NULL == Tree)
    {
        return -1;
    }

    return Tree->Count;
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

static void TreeTemporaryPreorder(CC_TREE_NODE *Node, int *Index, int *Value)
{
    if (*Index == 0)
    {
        *Value = Node->Value;
        return;
    }
    if (Index > 0 && NULL != Node->Left)
    {
        (*Index)--;
        TreeTemporaryPreorder(Node->Left, Index, Value);
    }
    if (Index > 0 && NULL != Node->Right)
    {
        (*Index)--;
        TreeTemporaryPreorder(Node->Right, Index, Value);
    }
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    if (NULL == Tree || NULL == Value || Index < 0 || Index >= Tree->Count)
    {
        return -1;
    }

    TreeTemporaryPreorder(Tree->Root, &Index, Value);
    return 0;
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

int TreeDestroyNode(CC_TREE_NODE **Node, int Recursively)
{
    if (NULL == Node)
    {
        return -1;
    }

    if (Recursively)
    {
        PCC_TREE_NODE node = *Node;

        if (NULL != node->Left && 0 != TreeDestroyNode(&node->Left, 1))
        {
            return -1;
        }

        if (NULL != node->Right && 0 != TreeDestroyNode(&node->Right, 1))
        {
            return -1;
        }
    }

    free(*Node);
    *Node = NULL;

    return 0;
}

int TreeRemoveNode(CC_TREE *Tree, CC_TREE_NODE *Node)
{
    if (NULL == Node || NULL == Tree)
    {
        return -1;
    }

    PCC_TREE_NODE parent = Node->Parent;

    if (NULL == Node->Left || NULL == Node->Right)
    {
        PCC_TREE_NODE child = Node->Left ? Node->Left : Node->Right;

        if (NULL == child)
        {
            if (NULL == parent)
            {
                Tree->Root = NULL;
            }
            else if (parent->Left == Node)
            {
                parent->Left = NULL;
            }
            else
            {
                parent->Right = NULL;
            }

            if (0 != TreeDestroyNode(&Node, 0))
            {
                return -1;
            }
        }
        else
        {
            Node->Left = child->Left;
            Node->Right = child->Right;
            Node->Value = child->Value;
            Node->Height = child->Height;

            if (0 != TreeDestroyNode(&child, 0))
            {
                return -1;
            }
        }
    }
    else
    {
        PCC_TREE_NODE minNode = NULL;
        if (0 != TreeGetMinNode(Node->Right, &minNode) || NULL == minNode)
        {
            return -1;
        }

        Node->Value = minNode->Value;

        if (0 != TreeRemoveNode(Tree, minNode))
        {
            return -1;
        }
    }

    if (NULL != parent)
    {
        return TreeBalance(Tree, parent);
    }

    return 0;
}

int TreeFindNode(CC_TREE_NODE *Root, int Value, CC_TREE_NODE ** Node)
{
    if (NULL == Root || NULL == Node)
    {
        return -1;
    }

    if (Root->Value > Value)
    {
        if (NULL == Root->Left)
        {
            *Node = NULL;
            return 0;
        }
        return TreeFindNode(Root->Left, Value, Node);
    }
    else if (Root->Value < Value)
    {
        if (NULL == Root->Right)
        {
            *Node = NULL;
            return 0;
        }
        return TreeFindNode(Root->Right, Value, Node);
    }

    *Node = Root;
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

int TreeGetMinNode(CC_TREE_NODE * Root, CC_TREE_NODE ** Node)
{
    if (NULL == Root || NULL == Node)
    {
        return -1;
    }

    if (NULL == Root->Left)
    {
        *Node = Root;
    }
    else
    {
        TreeGetMinNode(Root->Left, Node);
    }

    return 0;
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

    while (Node)
    {
        int balance = TreeGetBalanceFactor(Node);
        Node->Height = 1 + Max(TreeGetNodeHeight(Node->Left), TreeGetNodeHeight(Node->Right));


        if (balance > 1)
        {

            if (TreeGetBalanceFactor(Node->Left) >= 0)
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
        else if (balance < -1)
        {
            if (TreeGetBalanceFactor(Node->Right) > 0)
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

int TreeGetBalanceFactor(CC_TREE_NODE * Node)
{
    return TreeGetNodeHeight(Node->Left) - TreeGetNodeHeight(Node->Right);
}

static int Max(int Num1, int Num2)
{
    return Num1 > Num2 ? Num1 : Num2;
}
