//
//  tokenizer.c
//  Tokenizer
//
//  Created by Avijeet Sachdev on 7/1/16.
//  Copyright © 2016 Avijeet Sachdev. All rights reserved.
//

/*
 * CS211 CompArch
 * Liu Liu
 * tokenizer.c
 */

#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// change the 'return NULL' after you finished the code 
// functions specifications are in tokenizer.h 

void dummyFunc(){
    printf("I succesfully write a makefile\n");
}

TokenizerT *TKCreate(char * ts){
    TokenizerT *tk = malloc(sizeof(TokenizerT));
    tk->head = (Node *)malloc(sizeof(Node));
    tk->tail = (Node *)malloc(sizeof(Node));
    
    FILE *infile = fopen(ts, ("r"));
    char *line = (char *)malloc(50);
    char *p, *currentToken;
    while(fgets(line, 50, infile)) {
        while(strlen(p) >= 1) {
            while (*p == ' ' || *p == '\n') {
                if (strlen(p) == 1)
                    break;
                p++;
            }
            currentToken = TKGetNextToken(p);
            p+=strlen(currentToken);
        }
    }
    
    /* you might need more than a few helper functions */
    
    /* SAMPLE LOGIC:
     * traverse through the file line by line
     * in each line, repeatedly call TKGetNextToken() until the end of line
     * store the result from TKGetNextToken() to your structure
     * interpret the informations and store the interpretation in your structure
     */
    
    return NULL;
}
void TKDestroy( TokenizerT * tk ) {
    /* fill in your code here */
}

char *TKGetNextToken( char * start ) {
    char* check = start;
    char *startPtr = start;
    char* end = NULL;
    int length = 1;
    char *token;
    while (*check == ' '){
        if (strlen(startPtr) == 1){
            return NULL;
        }
        check++;
    }
    startPtr= check;
    while (*check != ' '){
        if(strlen(startPtr) == 1){
            length++;
            break;
        }
        check++;
        length++;
    }
    token = malloc(length+1);
    strncpy(token, startPtr, length);
    return token;
}

void TKPrint(TokenizerT *tk){
}
 /*
int state_octal(int index, TokenizerT* tk){ //keeps going until it encounters a non-digit, non-octal character
    if(isdigit(tk->currchar[index])){
        if(tk->currchar[index] != '8' && tk->currchar[index] != '9'){
            return state_octal(index+1, tk);
        }
        else {
            tk->tokentype = badinput;
            return index;
        }
    }
    else {
        return index;
    }
}

int state_hex(int index, TokenizerT* tk) { //keeps going until it finds something that isn't 0-9,a-f, A-F.
    if(isxdigit(tk->currchar[index])) { //isxdigit(int) tells me if the character is a hexidecimal or not.
        return state_hex(index+1, tk);
    }
    else {
        return index;
    }
}
int state_float(int index, TokenizerT* tk) { //prereq: previous character was a '+' or '-' sign.
    if(isdigit(tk->currchar[index])) {
        return state_float(index+1, tk);
    }
    else {
        tk->tokentype = floatnum;
        return index;
    }
}
*/
