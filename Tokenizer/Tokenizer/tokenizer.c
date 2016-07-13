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

/*  Checks for data types:s
    1 if check passes, 0 if not 
*/
int isDigit(char* exp){
    if (*exp < '0' && *exp > '9') {
        return 0;
    }
    else {
        return 1;
    }
}
int isOctal(char* exp){
    int i;
    long len;
    len = strlen(exp);
    for (i = 0; i < len; i++){
        //first digit is 0, no digits then flase
        if (exp[0] == '0'){
            if (isDigit(exp) == 1){
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 1;
}
int isFloat(char* exp){
    char *expPtr = exp;
    if (strchr(expPtr, 'e') || strchr(expPtr, '.' ) || strchr(expPtr, 'E')) {
        return 1;
    }
    else {
        return 0;
    }
}
int isHex(char* exp){
    if (exp[1] == 'x' || exp[1] == 'X') {
        return 1;
    }
    else {
        return 0;
    }
}

char* getType(char* tokenType) {
    if (strlen(tokenType) >= 2){ // for efficiency's sake, ask for strlen now and use it for determining type
        //float
        if (isFloat(tokenType)==1){
            return "float";
        }
        //hex
        if (isHex(tokenType)==1) {
            return "hex";
        }
        //octal
        if (isOctal(tokenType)==1){
            return "octal";
        }
    }
    else {
        if(isDigit(tokenType)==1) {
            return "decimal";
        }
    }
    return "ERROR";
}

TokenizerT *TKCreate(char * ts){
    TokenizerT *tk = malloc(sizeof(TokenizerT));
    //keeps track of head and tail of Linked List
    tk->head = (Node *)malloc(sizeof(Node));
    tk->tail = (Node *)malloc(sizeof(Node));
    
    //opens file
    FILE *infile = fopen(ts, "r");
    char *line = (char *)malloc(50); // each line can only have maximum length of 50 characters
    char *p = line; //p represents string
    char *currentToken; //currentToken represents p called on TKGetNextToken
    while(fgets(line, 50, infile)) {
        while(strlen(p) > 0) { //applicable length
            while (*p == ' ' || *p == '\n') { //whitespace or \newline
                if (strlen(p) == 1)
                    break; // p can't be that short
                p++; // if it's applicable length, keep traversing
            }
            currentToken = TKGetNextToken(p);
            p += strlen(currentToken); // p, the index, goes to the next whitespace (end of currentToken length)
            struct Tokens_LL *temp; //new node called temp
            temp = (struct Tokens_LL*)malloc(sizeof(struct Tokens_LL)); // allocating memory for node
            temp->token = currentToken; // data of node is currentToken
            temp->type = getType(currentToken); //gets type: floating-point constant, integer constant in hex, decimal or octal
            if (tk->head == NULL){
                tk->head = temp; // if no nodes, temp is new head
            }
            else if (tk->tail == NULL) {
                tk->head->next = temp; //if no tail, temp is added to the end
                tk->tail = temp; // temp is new tail
            }
            else {
                tk->tail->next = temp; // add temp to end
                tk->tail = temp; // temp is new tail
            }
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
}

char *TKGetNextToken( char * start ) {
    char* check = start; // new string check
    char *startPtr = start; //pointer for called string
    int length = 1;
    char *token;
    while (*check == ' '){
        if (strlen(startPtr) == 1){ //has to be applicable length
            return NULL;
        }
        check++; //keep traversing if applicable length
    }
    startPtr = check; //pointer now matches value of check string
    while (*check != ' '){ // not whitespace
        if(strlen(startPtr) == 1){
            length++; // not applicable length, move on
            break;
        }
        length++; //length of string goes up
        check++; //keep traversing
    }
    token = malloc(length+1);
    strncpy(token, startPtr, length); //token is destination, startPtr is string to be copied, length is # of copies to be stored
    return token;
}

void TKPrint(TokenizerT *tk){
    FILE *yes, *no;
    
    yes = fopen("results", "w"); // results file, everything working
    no = fopen("error.msg", "w"); //error file, things didn't work out
    
    struct Tokens_LL *trav; // new LL node
    trav = tk->head; //node is at the head of the linked list
    
    while(trav != NULL){
        if(*trav->token == 'e'){
            fprintf(no, "[0X%s]\n", trav->token);
        }
        else {
            fprintf(yes, "%s %s\n", trav->type, trav->token);
        }
        trav = trav->next;
    }
    
    fclose(yes); //everything done, close file
    fclose(no); //everything done, close file
}
