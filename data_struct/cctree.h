#pragma once

//This data structure implements an AVL tree


//Node of the tree
typedef struct _CC_TREE_NODE {
    struct _CC_TREE_NODE *Parent, *Left, *Right;
    int Value;
    int Height;
} CC_TREE_NODE, *PCC_TREE_NODE;

typedef struct _CC_TREE {
    // Members
    PCC_TREE_NODE Root;
    int Count;
} CC_TREE, *PCC_TREE;

int TreeCreate(CC_TREE **Tree);
int TreeDestroy(CC_TREE **Tree);

// Duplicates are allowed
int TreeInsert(CC_TREE *Tree, int Value);

// Removes all elements equal to Value
int TreeRemove(CC_TREE *Tree, int Value);

/*
 *  Return:
 *      1   - Tree contains value
 *      0   - Tree does not contain Value
 */
int TreeContains(CC_TREE *Tree, int Value);

int TreeGetCount(CC_TREE *Tree);
int TreeGetHeight(CC_TREE *Tree);
int TreeClear(CC_TREE *Tree);

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value);
int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value);
