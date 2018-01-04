//
//  stack.c
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Creates a stack object for manipulation
 */
Stack* createStack(){
    Stack* stack;
    stack = (Stack*)malloc(sizeof(Stack));
    stack->size = 0;
    return stack;
}

/**
 * Pushes an object onto the stack.
 */
void push(Stack* stack, void* node){
    StackNode* sNode = (StackNode*)malloc(sizeof(StackNode));
    sNode->data = node;
    if(stack->size >= 1){
        sNode->next = stack->topOfStack;
        stack->topOfStack = sNode;
        stack->size += 1;
    }else{
        stack->size += 1;
        stack->topOfStack = sNode;
    }
    
}

/**
 * Gets the top object of the stack
 */
void* peek(Stack* stack){
    if (stack->size == 0) {
        return NULL;
    }
    return stack->topOfStack->data;
}

/**
 * Pops the top element off the the stack.
 */
void* pop(Stack* stack){
    int stackSize = stack->size;
    if(stackSize == 0){
        return NULL;
    }
    
    if(stackSize == 1){
        stack->size -= 1;
        Node* node = stack->topOfStack->data;
        free(stack->topOfStack);
        return node;
    }else{
        stack->size -= 1;
        Node* node = stack->topOfStack->data;
        StackNode* topOfStack = stack->topOfStack;
        stack->topOfStack = topOfStack->next;
        free(topOfStack);
        return node;
    }
    
    
}

/**
 * Gets the size of the items on the stack
 */
int getStackSize(Stack* stack){
    return stack->size;
}


/**
 * Destroys all elements on the stack.
 * Does not free the nodes directly.  Client has to do that.
 */
bool destroyStack(Stack* stack){
    int size = stack->size;
    for (int i = 0; i < size; i++ ) {
        pop(stack);
    }
    
    free(stack);
    return true;
}

