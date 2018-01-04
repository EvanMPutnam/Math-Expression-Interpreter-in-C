//
//  map.c
//  Romance
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#include "map.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 100



int moduloIndex(long x, long dim){
    int modV = (int)x%dim;
    if((modV > 0 && dim < 0) || (modV < 0 && dim > 0)){
        modV = (int)(modV + dim);
    }
    return modV;
}




Table* createTable(long(*hash)(char* key),
                   bool (*equals)(char* key1, char* key2)){

    Table* t = (Table*)malloc(sizeof(Table));
    if(t == NULL){
        fprintf(stderr, "Memory alloc for table failed\n");
        assert(NULL);
    }
    t->table = (TableEntry**)calloc(STARTING_CAPACITY, sizeof(TableEntry));
    t->equals = equals;
    t->hash = hash;
    t->capacity = STARTING_CAPACITY;
    t->size = 0;
    
    return t;
    
}

void destroyTable(Table* t){
    int cap = (int)t->capacity;
    for(int i = 0; i < cap; i++){
        if(t->table[i] != NULL){
            free(t->table[i]);
        }
    }
    free(t->table);
    free(t);
}

void *getTableItem(Table* t, char* key){
    int cap = t->capac
}

bool hasTableItem(Table* t, char* key);

char** getTableKeys(Table* t);

void* putTableValue(Table* t, char* key, void* value);

void** getTableValues(Table* t);
