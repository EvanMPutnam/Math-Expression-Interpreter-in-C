//
//  evaluator.c
//  Romance
//
//
// TODO: Figure out a way to do unary - operators the way I have it done.
// https://stackoverflow.com/questions/16425571/unary-minus-in-shunting-yard-expression-parser 
//
//  Created by Evan Putnam on 12/17/17.
//  Copyright © 2017 Evan Putnam. All rights reserved.
//
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include "evaluator.h"
#include "stack.h"
#include "queue.h"
#include "table.h"


typedef struct DoubleNode{
    double data;
}DoubleNode;

bool isConstant(char* expr){
    return strcmp(expr, "SIN") == 0 || strcmp(expr, "COS") == 0 || strcmp(expr, "TAN") == 0
    || strcmp(expr, "SQRT") == 0 || strcmp(expr, "ABS") == 0 || strcmp(expr, "@") == 0;
}

bool isNum(char s){
    return s == '0' || s == '1' ||  s == '2' ||  s == '3' ||  s == '4' ||  s == '5' ||
    s == '6' || s == '7' || s == '8' || s == '9' || s == '.';
}

bool isWholeNum(char* token){
    bool num = false;
    size_t size = strlen(token);
    for(size_t i = 0; i < size; i++){
        num = isNum(token[i]);
        if(num == false){
            break;
        }
    }
    return num;
}

void resetChars(char* chars, size_t size){
    for(size_t i = 0; i < size; i++){
        chars[i] = '\0';
    }
}

int getPrecedence(char* op){
    
    if(strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ){
        return 2;
    }
    
    if(strcmp(op, "/") == 0 || strcmp(op, "*") == 0 ){
        return 3;
    }
    
    if(strcmp(op, "SIN") == 0 || strcmp(op, "COS") == 0 || strcmp(op, "TAN") == 0 ||
       strcmp(op, "ABS") == 0 || strcmp(op, "SQRT") == 0 || strcmp(op, "@") == 0){
        return 4;
    }
    
    //Return -1 if not valid
    return -1;
}

bool isParenth(char s){
    return s == '(' || s == ')';
}

bool isOperator(char s){
    return s == '+' || s == '-' || s == '/' || s == '*';
}

bool isLeftBracket(char* c){
    if(strcmp(c, "(") == 0){
        return true;
    }
    return false;
}

bool isRightBracket(char* c){
    if(strcmp(c, ")") == 0){
        return true;
    }
    return false;
}


double evaluatePostfix(Queue* queue, Table* t){
    
    Stack* stack = createStack();
    
    while (queue->size != 0) {
        
        char* token = popQueue(queue);
        
        //If number // TODO: Add elem support
        if(isWholeNum(token)){
            DoubleNode* d = (DoubleNode*)malloc(sizeof(DoubleNode));
            d->data = atof(token);
            free(token);
            push(stack, d);
            continue;
        }
        
        if(hasTableElem(t, (void*)token)){
            DoubleNode* d = (DoubleNode*)malloc(sizeof(DoubleNode));
            Node* n = (Node*)getTableElem(t, token);
            d->data = n->data;
            free(token);
            push(stack, d);
            continue;
        }
        
        //If operator
        if(isConstant(token) || isOperator(token[0])){
            if(isConstant(token)){
                DoubleNode* val1 = (DoubleNode*)pop(stack);
                
                if(strcmp("SIN", token) == 0){
                    val1->data = sin(val1->data);
                }
                if(strcmp("COS", token) == 0){
                    //sprintf(value, "%lf", cos(v1));
                    val1->data = cos(val1->data);
                }
                if(strcmp("TAN", token) == 0){
                    //sprintf(value, "%lf", tan(v1));
                    val1->data = tan(val1->data);
                }
                if(strcmp("ABS", token) == 0){
                    //sprintf(value, "%lf", fabs(v1));
                    val1->data = fabs(val1->data);
                }
                if(strcmp("SQRT", token) == 0){
                    //sprintf(value, "%lf", sqrt(v1));
                    val1->data = sqrt(val1->data);
                }
                if(strcmp("@", token) == 0){
                    //sprintf(value, "%lf", sqrt(v1));
                    val1->data = 0 - val1->data;
                }
                push(stack, val1);
                free(token);
                continue;
            }
            
            if(isOperator(token[0])){
                DoubleNode* val1 = pop(stack);
                DoubleNode* val2 = pop(stack);
                
                if(token[0] == '+'){
                    //size_t needed = snprintf(NULL, 0, "%lf", v1 + v2) + 1;
                    val1->data = val1->data + val2->data;
                }
                if(token[0] == '-'){
                    //sprintf(value, "%lf", v2-v1);
                    val1->data = val2->data - val1->data;
                }
                if(token[0] == '/'){
                    //sprintf(value, "%lf", v2/v1);
                    val1->data = val2->data/val1->data;
                }
                if(token[0] == '*'){
                    //sprintf(value, "%lf", v1*v2);
                    val1->data = val1->data*val2->data;
                }
                
                free(val2);
                free(token);
                push(stack, val1);
                continue;
                
            }
        }
        
    }
    
    double d = 0.0;
    if(stack->size == 1){
        DoubleNode* value = (DoubleNode*)pop(stack);
        d = value->data;
        free(value);
    }
    
    destroyStack(stack);
    
    return d;
}


double evaluateTokens(char* expr, Table* t){
    
    char* toke = strtok(expr, " \n");
    Stack* stack = createStack();
    Queue* queue = createQueue();
    
    while (toke != NULL) {
        
        char* token = (char*)calloc(strlen(toke)+1, sizeof(char));
        strcpy(token, toke);
        

        //If token is number push to output queue
        if(isWholeNum(token) || hasTableElem(t, token)){
            addToQueue(queue, token);
        }
        
        if(isConstant(token) || isOperator(token[0])){
            
            while (stack->size != 0 && isLeftBracket((char*)peek(stack)) == false
                   && getPrecedence((char*)peek(stack)) >= getPrecedence(token)) {
                
                addToQueue(queue, pop(stack));
                
            }
            
            push(stack, token);
        }
        
        //If token is left bracket push onto operator stack
        if(isLeftBracket(token)){
            push(stack, token);
        }
        
        if(isRightBracket(token)){
            char* operator = (char*)peek(stack);
            while (isLeftBracket(operator) != true) {
                addToQueue(queue, pop(stack));
                operator = (char*)peek(stack);
            }
            char* popV = (char*)pop(stack);
            free(popV);
            free(token);
        }
        toke = strtok(NULL, " \n");
    }
    
    while (stack->size != 0) {
        addToQueue(queue, pop(stack));
    }
    
    
    double d = evaluatePostfix(queue, t);
    destroyStack(stack);
    destroyQueue(queue);
    return d;
}


//Function used to get rid of redundant minuses
char*  simplifyStr(char* str){
    char* newStr = (char*)calloc(strlen(str)*3, sizeof(char));
    size_t size = strlen(str);
    
    bool prevOp = true;
    
    size_t index = 0;
    for(size_t s = 0; s < size; s++){
        
        if (prevOp == true && str[s] == '-') {
            newStr[index] = '@';
            prevOp = true;
            index += 1;
            continue;
        }
        
        if(str[s] == ' '){
            continue;
        }
        
        newStr[index] = str[s];
        index += 1;
        prevOp = isOperator(str[s]) || str[s] == '(';
    }
    

    return newStr;
}



/**
 * Evaluates a string.
 * Need to handle things like *-1 and -----5
 * Have to seperate something like    * (-5)
 */
double evaluate(char* expr1, Table* t){
    
    char* expr = simplifyStr(expr1);
    
    size_t size = strlen(expr);
    char* exprBuffer = calloc(strlen(expr)*2+1, sizeof(char));
    size_t index = 0;
    
    
    bool isE = true;
    
    for(size_t i = 0; i < size; i++){
        if(isParenth(expr[i]) ||isOperator(expr[i]) || (expr[i] == '@' && isE == true)){
            exprBuffer[index] = ' ';
            index += 1;
            exprBuffer[index] = expr[i];
            index += 1;
            exprBuffer[index] = ' ';
            index += 1;
            isE = true;
        }else{
            exprBuffer[index] = expr[i];
            index += 1;
            isE = false;
        }
    }
    double rV = evaluateTokens(exprBuffer, t);
    free(exprBuffer);
    free(expr);
    
    return rV;
}
