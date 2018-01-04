//
//  parser.c
//  Romance
//
//  Language parser that processes the language features described when typeing HELP()
//  
//  Created by Evan Putnam on 1/1/18.
//  Copyright © 2018 Evan Putnam. All rights reserved.
//


#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "table.h"
#include "evaluator.h"

#define BUFFER_SIZE 512


/**
 * Outputs all the key value pairs inside of the hash table.
 */
void debugPrint(Table* t){
    size_t size = t->capacity;
    for(size_t i = 0; i < size; i++){
        if(t->entries[i] != NULL){
            Node* n = t->entries[i]->value;
            printf("%s = %lf\n", t->entries[i]->key, n->data);
        }
    }
}

/**
 * Processes the LET x = someExpression
 */
void handleLet(char* value, char* expr, Table* t){
    
    char expN[BUFFER_SIZE+1];
    size_t index = 0;
    size_t size = strlen(expr);
    
    //Bool to indicate when can start reading expression
    bool start = false;
    
    //Get the expression part
    for(size_t s = 0; s < size; s++){
        if(start == true && expr[s] != '\n' && expr[s] != ' '){
            expN[index] = expr[s];
            index += 1;
        }
        if(expr[s] == '='){
            start = true;
        }
    }
    
    //Evaluate expression
    double d = evaluate(expN, t);
    
    //Create node to store the data
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = d;
    
    //Copy into dynamic
    char* val = (char*)calloc(strlen(value)+1, sizeof(char));
    strcpy(val, value);
    
    //If already set then need to free previous
    bool hasAlready = false;
    hasAlready = hasTableElem(t, val);
    if(hasTableElem(t, val)){
        Node* nF = (Node*)putTableElem(t, val, n);
        free(nF);
    }else{
        putTableElem(t, val, n);
    }
    
}

/**
 * Parses expressions in the language.  Language features can be read below
 */
void startParseing(Table* t){
    
    //Buffer to store stuff
    char buffer[BUFFER_SIZE];
    
    while (true) {
        printf(">>>");
        fgets(buffer, BUFFER_SIZE, stdin);
        printf("%s", buffer);
        
        //Handles exit function
        if(strcmp("EXIT()\n", buffer) == 0){
            printf("Goodbye!\n");
            return;
        }
        
        //Handles displaying all variables
        if(strcmp("VARS()\n", buffer) == 0){
            debugPrint(t);
            continue;
        }
        
        //Handles getting help
        if(strcmp("HELP()\n", buffer) == 0){
            printf("Functions:\n");
            printf("    HELP() is this function...\n");
            printf("    VARS() displays all active variables\n");
            printf("    EXIT() exits\n");
            printf("Features:\n");
            printf("    SIN(x) is sin\n");
            printf("    COS(x) is cos\n");
            printf("    TAN(x) is tangent\n");
            printf("    SQRT(x) is square root\n");
            printf("    ABS(x) is absolute value\n");
            printf("Operators:\n");
            printf("    +, -, /, *");
            printf("Assignment and Usage:\n");
            printf("    LET x = (SIN(TAN(20/2))");
            printf("    Can then display by typeing x\n");
            printf("Other Notes:\n");
            printf("    You can include parenthesis if they are matched correctly\n");
            printf("    No extensive error checking has been done so it will crash on invalid expressions\n");
            
        }
        
        
        //Process specifc errors
        if(strlen(buffer) >= BUFFER_SIZE){
            fprintf(stderr ,"ERROR: Exceeded buffer size");
            return;
        }
        
        
        //Maintain buffer
        char secondaryBuffer[BUFFER_SIZE+1];
        strcpy(secondaryBuffer, buffer);
        
        char variable[BUFFER_SIZE+1];
        char* token = strtok(buffer, "= \n");
        bool let = false;
        while (token != NULL) {
            if(let == true){
                strcpy(variable, token);
                break;
            }
            if (strcmp(token, "LET") == 0) {
                let = true;
                token = strtok(NULL, "= \n");
                continue;
            }
            token = strtok(NULL, "= \n");
        }
        
        //If let was triggered then assignment
        if(let == false){
            double d = evaluate(secondaryBuffer, t);
            printf("%lf\n", d);
        }else{
            handleLet(variable, secondaryBuffer, t);
        }
        
        
        
    }
    
}
