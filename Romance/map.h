//
//  map.h
//  Romance
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <stdbool.h>


typedef struct TableEnts{
    char* key;
    void* value;
}TableEntry;


typedef struct Tables{
    TableEntry** table;
    size_t size;
    size_t capacity;
    long (*hash)(char* key);
    bool (*equals)(char* key1, char* key2);
}Table;


Table* createTable(long(*hash)(char* key),
              bool (*equals)(char* key1, char* key2));

void destroyTable(Table* t);

void *getTableItem(Table* t, char* key);

bool hasTableItem(Table* t, char* key);

char** getTableKeys(Table* t);

void* putTableValue(Table* t, char* key, void* value);

void** getTableValues(Table* t);




#endif /* map_h */
