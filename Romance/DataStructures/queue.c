//
//  queue.c
//
//  Created by Evan Putnam on 12/26/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


/**
 * Creates a queue struct and sets it to empty
 */
Queue* createQueue(void){
    Queue* queue = (Queue*)malloc(sizeof(struct Queues));
    queue->front = NULL;
    queue->size = 0;
    return queue;
}

/**
 * Adds an item to the queue
 */
void addToQueue(Queue* queue, void* data){
    if(queue->size == 0){
        QueueNode* queueNode = (QueueNode*)malloc(sizeof(struct QueueNodes));
        queueNode->data = data;
        queueNode->prev = NULL;
        queue->front = queueNode;
        queue->size += 1;
        return;
    }else{
        QueueNode* queueNode = (QueueNode*)malloc(sizeof(struct QueueNodes));
        queueNode->data = data;
        queueNode->prev = NULL;
        
        QueueNode* iterNode = queue->front;
        while(iterNode->prev != NULL){
            iterNode = iterNode->prev;
        }
        iterNode->prev = queueNode;
        queue->size += 1;
        return;
    }
    
}

/**
 * Pops a queue node off of the queue and returns the data of that node
 */
void* popQueue(Queue* queue){
    if(queue->size == 0){
        return NULL;
    }
    else if(queue->size == 1){
        QueueNode* queueNode = queue->front;
        queue->front = NULL;
        queue->size -= 1;
        void* data = queueNode->data;
        free(queueNode);
        return data;
    }else{
        QueueNode* queueNode = queue->front;
        queue->front = queueNode->prev;
        queue->size -= 1;
        void* data = queueNode->data;
        free(queueNode);
        return data;
    }
}

/**
 * Pops all elements and destroys the queue object.
 * NOTE: all data objects within queue nodes are clients responsibility to free.
 */
void destroyQueue(Queue* queue){
    size_t size = queue->size;
    for(size_t i = 0; i < size; i++){
        popQueue(queue);
    }
    free(queue);
}

/**
 * Peek at the top element of the queue
 */
void* peekQueue(Queue* queue){
    return queue->front->data;
}

/**
 * Get the size at the top of the queue
 */
size_t getSize(Queue* queue){
    return queue->size;
}
