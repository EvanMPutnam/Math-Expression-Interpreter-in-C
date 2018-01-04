//
//  stack.h
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//


#ifndef stack_h
#define stack_h


#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


/**
 * Structure to hold individual stack nodes
 */
typedef struct StackNodes{
    void* data;
    struct StackNodes* next;
}StackNode;


/**
 * Structure to keep track of top of stack
 */
typedef struct  Stacks{
    StackNode* topOfStack;
    int size;
    
}Stack;


/**
 * Creates the stack
 */
Stack* createStack(void);

/**
 * Destroys the stack
 */
bool destroyStack(Stack* stack);

/**
 * Pushes a piece of data onto the stack
 */
void push(Stack* stack, void* data);

/**
 * Get data at top of stack
 */
void* peek(Stack* stack);

/**
 * Pop the data at the top of the stack
 */
void* pop(Stack* stack);

/**
 * Get size of the queue
 */
int getStackSize(Stack* stack);






#endif /* stack_h */
