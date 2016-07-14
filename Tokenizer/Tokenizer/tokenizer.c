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
int isDigit(char exp){
    if (exp < '0') {
        return 0;
    }
    if (exp > '9') {
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
        if (exp[0] != '0'){
            return 0;
        }
        else {
            if (isDigit(*exp) == 1){
                if (exp[i] == '8' || exp[i] == '9'){
                    return 0;
                }
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
    int len;
    len = strlen(exp);
    if (len>=4){
        if (exp[1] == 'x' || exp[1] == 'X') {
            return 1;
        }
        else {
            return 0;
        }
    }
    return 0;
}

char* getType(char* tokenType) {
    char* type;
    if (strlen(tokenType) >= 2){ // for efficiency's sake, ask for strlen now and use it for determining type
        //float
        if (isFloat(tokenType)==1){
            type = "float";
            return type;
        }
        //hex
        if (isHex(tokenType)==1) {
            type = "hex";
            return type;
        }
        //octal
        if (isOctal(tokenType)==1){
            type = "octal";
            return type;
        }
        if(isDigit(*tokenType)==1) {
            type = "decimal";
            return type;
        }
    }
    else {
        if(isDigit(*tokenType)==1) { // same check and method call for if strlen(tokenType) is under 2
            type = "decimal";
            return type; //strlen(tokenType) can be any value, so called in both conditions
        }
    }
    type = "ERROR"; // no cases matched
    return type;
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
    }startPtr = check; //pointer now matches value of check string
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

TokenizerT *TKCreate(char * ts){
    TokenizerT *tk = malloc(sizeof(TokenizerT));
    //keeps track of head and tail of Linked List
    tk->head = NULL;
    tk->tail = NULL;
    
    //opens file
    FILE *new = fopen(ts, "r");
    char *line = (char *)malloc(50); // each line can only have maximum length of 50 characters
    char *p; //p represents string
    char *currentToken; //currentToken represents p called on TKGetNextToken
    while(fgets(line, 50, new) != NULL) {
        p = line;
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
            temp->data = currentToken; // data of node is currentToken
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
    free(line);
    fclose(new);//efficiency
    return tk;
}
void TKDestroy( TokenizerT * tk ) {
    struct Tokens_LL *trav, *ll;
    ll = tk->head;
    while(ll!=NULL){ //iterates with LL and frees all dynamically allocated memory
        trav = ll->next; //goes to next node with trav
        free(ll->data); //frees the token (data of LL)
        free(ll); // frees all of LL
        ll = trav; //equal so loop can iterate again
    }
    free(tk); //free everything brought in
}

void TKPrint(TokenizerT *tk){
    struct Tokens_LL *trav; // new LL node
    FILE *yes;
    FILE *no;
    trav = tk->head; //node is at the head of the linked list
    yes = fopen("result", "w"); // results file, everything working. writing.
    no = fopen("error.msg", "w"); //error file, things didn't work out. writing.
    while(trav != NULL){
        if(*(trav->type) == 'E'){ // looks for ERROR
            fprintf(no, "[0X%x]\n", *(trav->data)); // appending to error.msg
        }
        else {
            fprintf(yes, "%s %s\n", trav->type, trav->data); //appending to result
        }
        trav = trav->next;
    }
    
    fclose(yes); //everything done, close file
    fclose(no); //everything done, close file
}
