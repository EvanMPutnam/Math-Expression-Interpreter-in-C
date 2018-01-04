//
//  table.h
//  Romance
//
//  Created by Evan Putnam on 12/15/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#ifndef table_h
#define table_h

#include <stdio.h>
#include <stdbool.h>
#include "node.h"

/**
 * Node holds key-value pairs of void*
 */
typedef struct TableNodes{
    void* key;
    void* value;
}TableNode;

/**
 * Table holds entries, capacitiy, and size attributes
 */
typedef struct Tables{
    TableNode** entries;
    size_t capacity;
    size_t size;
}Table;


//Can implement your own hash function as you see fit.
long hash(void* key, long modV);

//Equals function can change based on your own implementation.
bool equals(void* k1, void* k2);

/**
 * Create a table structure
 */
Table* createTable(void);

/**
 * Destroy the table structure
 */
void destroyTable(Table* t);

/**
 * Gets a table element if available
 */
void* getTableElem(Table* t, void* key);

/**
 * Checks to see if a table element is availalbe
 */
bool hasTableElem(Table* t, void* key);

/**
 * Get a list of keys from the table
 */
void** getTableKeys(Table* t);

/**
 * Put table key-value pair into table.
 * returns old value to manage if pair already present
 */
void* putTableElem(Table* t, void* key, void* value);

/**
 * Gets a list of values from the table
 */
void** getTableValues(Table* t);






#endif /* table_h */
