//
//  table.c
//  Romance
//
//  Created by Evan Putnam on 12/15/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "table.h"


#define INIT_CAPACITY 100
#define RESIZE_MULTIPLE 2
#define REHASH_PERCENT .75

/**
 * Function to calculate modulo
 */
long moduloIndex(long x, long dim){
    long modV = x%dim;
    if((modV > 0 && dim < 0) || (modV < 0 && dim > 0)){
        modV = modV + dim;
    }
    return modV;
}


/**
 * Function to calculate the hash.  Is a string based hash that
 * sums up the values of each charachter and mods it by the modV value
 */
long hash(void* key, long modV){
    char* str = (char*)key;
    unsigned long size = strlen(str);
    long sum = 0;
    for(int i = 0; i < size; i++){
        sum += atol(&str[i]);
    }
    
    return moduloIndex(sum, modV);
}

/**
 * Equals function is if the two strings are equal
 */
bool equals(void* k1, void* k2){
    char* key1 = (char*)k1;
    char* key2 = (char*)k2;
    
    if(strcmp(key1, key2) == 0){
        return true;
    }
    return false;
    
}

/**
 * Creates and allocated memory for a table
 */
Table* createTable(){
    Table* table = (Table*)malloc(sizeof(Table));
    if(table == NULL){
        fprintf(stderr, "Error allocating table\n");
        exit(EXIT_FAILURE);
    }
    table->capacity = INIT_CAPACITY;
    table->size = 0;
    table->entries = (TableNode**)calloc(INIT_CAPACITY, sizeof(TableNode));
    return table;
}


/**
 * Destroy table by freeing all entries and table itself.
 */
void destroyTable(Table* t){
    size_t size = t->capacity;
    for(int i = 0; i < size; i++){
        if(t->entries[i] != NULL){
            free(t->entries[i]);
        }
    }
    free(t->entries);
    free(t);
}

/**
 *
 */
void* getTableElem(Table* t, void* key){
    size_t size = t->capacity;
    long index = hash(key, size);
    if(t->entries[index] == NULL){
        return NULL;
    }else if(equals(key, t->entries[index]->key)){
        return t->entries[index]->value;
    }
    
    bool found = true;
    if(t->entries[index] != NULL){
        while(!(equals(key, t->entries[index]->key))){
            
            index += 1;
            if(index == size){
                index = 0;
            }
            
            if(t->entries[index] == NULL){
                found = false;
                break;
            }
            
        }
    
        if(found == true){
            return t->entries[index]->value;
        }
        
    }
    return NULL;
    
}

/**
 * Finds if the table has an element in it
 */
bool hasTableElem(Table* t, void* key){
    size_t size = t->capacity;
    long index = hash(key, size);
    if(t->entries[index] == NULL){
        return false;
    }else if(equals(key, t->entries[index]->key)){
        return true;
    }
    
    bool found = true;
    if(t->entries[index] != NULL){
        while(!(equals(key, t->entries[index]->key))){
            index += 1;
            if(index == size){
                index = 0;
            }
            
            if(t->entries[index] == NULL){
                found = false;
                break;
            }
            
        }
        return found;
        
    }
    return false;

}


/**
 * Rehashes the table when called based on the defined multiple
 */
void rehashTable(Table* t){
    size_t capac = t->capacity;
    size_t newCapac = capac*RESIZE_MULTIPLE;
    TableNode** table;
    table = (TableNode**)calloc(newCapac,sizeof(TableNode));
    if(table == NULL){
        fprintf(stderr, "ERROR in rehashing heap");
        exit(EXIT_FAILURE);
    }
    
    for(unsigned long i = 0; i < capac; i++ ){
        if(t->entries[i] != NULL){
        
            long x = hash(t->entries[i]->key, newCapac);
            
            //Rehash it
            while(table[x] != NULL){
                x += 1;
                if(x >= newCapac){
                    x = 0;
                }
            }
            table[x] = t->entries[i];
            
        }
    }
    t->capacity = newCapac;
    free(t->entries);
    t->entries = table;

}

/**
 * Gets all the table keys
 */
void** getTableKeys(Table* t){
    
    size_t size = t->capacity;
    
    void** keys = calloc(t->size,sizeof(TableNode));
    if(keys == NULL){
        fprintf(stderr, "ERROR in getting table keys");
        exit(EXIT_FAILURE);
    }
    
    size_t index = 0;
    for(size_t i = 0; i < size; i++){
        if(t->entries[i] != NULL){
            keys[index] = t->entries[i]->key;
            index += 1;
        }
    }
    return keys;
    
}



/**
 * Puts an element in the table
 */
void* putTableElem(Table* t, void* key, void* value){
    double s = (double)t->size;
    double c = (double)t->capacity;
    if(s/c >= REHASH_PERCENT){
        rehashTable(t);
    }
    
    unsigned long capacity = t->capacity;
    
    long index = hash(key, capacity);
    
    while(t->entries[index] != NULL){
    
        if(equals(t->entries[index]->key, key)){
            void* rVal = t->entries[index]->value;
            t->entries[index]->value = value;
            return rVal;
            
        }
        
        index += 1;
        if(index == capacity){
            index = 0;
        }
        
        
    }
    t->entries[index] = (TableNode*)malloc(sizeof(TableNode));
    t->entries[index]->key = key;
    t->entries[index]->value = value;
    t->size += 1;
    
    return NULL;
    
}

/**
 * Get the values of the table
 */
void** getTableValues(Table* t){
    
    size_t size = t->capacity;
    
    void** values = calloc(t->size,sizeof(TableNode));
    if(values == NULL){
        fprintf(stderr, "ERROR in getting table values");
        exit(EXIT_FAILURE);
    }
    
    size_t index = 0;
    for(size_t i = 0; i < size; i++){
        if(t->entries[i] != NULL){
            values[index] = t->entries[i]->value;
            index += 1;
        }
    }
    return values;
    
    
}
