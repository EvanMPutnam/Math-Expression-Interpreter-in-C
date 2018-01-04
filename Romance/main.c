//  main.c
//  Romance
//
//
//
//  Envirornment for coding was X Code
//
//
//  Created by Evan Putnam on 12/14/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "table.h"


int main(int argc, const char * argv[]) {

    //Create a table to use for storing values
    Table* t = createTable();

    //Parse expressions
    startParseing(t);
    
    //Free the items inside of the table;
    char** keys = (char**)getTableKeys(t);
    Node** values = (Node**)getTableValues(t);
    size_t size = t->size;
    for(size_t s = 0; s < size; s++){
        free(keys[s]);
        free(values[s]);
    }
    free(keys);
    free(values);
    
    //Destroy table object
    destroyTable(t);
    

    return 0;
}
