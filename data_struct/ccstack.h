#pragma once

typedef struct _CC_STACK{ 
    // Members
    int PlaceHolder; // placeholder to be removed when actual implementation is added
} CC_STACK; 
  
int StCreate(CC_STACK **Stack);
int StDestroy(CC_STACK **Stack);
 
int StPush(CC_STACK *Stack, int Value);
int StPop(CC_STACK *Stack, int *Value);
int StPeek(CC_STACK *Stack, int *Value); // gets top of stack without popping the value
int StIsEmpty(CC_STACK *Stack); // returns 1 if stack is empty and 0 otherwise
int StGetCount(CC_STACK *Stack); // returns the number of elements in the stack
int StClear(CC_STACK *Stack); // removes all elements from the stack

// StPushStack removes all the elements from the StackToPush and appends 
// them to the first stack 
// ex: Stack1: 1, 2, 3
//     Stack2: 1, 4, 5
// After push: Stack1: 1, 2, 3, 1, 4, 5
//             Stack2: empty
int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush); 
