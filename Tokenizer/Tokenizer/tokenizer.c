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
/* change the 'return NULL' after you finished the code */
/* functions specifications are in tokenizer.h */

void dummyFunc(){
    printf("I succesfully write a makefile\n");
}

TokenizerT *TKCreate(char * ts){
    /* fill in your code here */
    
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
    /* fill in your code here */
    return NULL;
}

void TKPrint(TokenizerT *tk){
    /* fill in your code here */
}
