//
//  queue.h
//
//  Created by Evan Putnam on 12/26/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>

/**
 * Data structure for queue node
 */
typedef struct QueueNodes{
    void* data;
    struct QueueNodes* prev;
}QueueNode;

/**
 * Data structure for the queue
 */
typedef struct Queues{
    QueueNode* front;
    size_t size;
}Queue;


/**
 * Creates a queue
 */
Queue* createQueue(void);

/**
 * Destroys a queue
 */
void destroyQueue(Queue* queue);

/**
 * Adds a piece of data to the queue
 */
void addToQueue(Queue* queue, void* data);

/**
 * Pops a piece of data from the queue
 */
void* popQueue(Queue* queue);

/**
 * Peeks at the top data elmeent of the queue
 */
void* peekQueue(Queue* queue);

/**
 * Gets the size of the queue
 */
size_t getSize(Queue* queue);




#endif /* queue_h */
