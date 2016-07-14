//
//  main.c
//  Tokenizer
//
//  Created by Avijeet Sachdev on 7/1/16.
//  Copyright © 2016 Avijeet Sachdev. All rights reserved.
//

#include "tokenizer.h"
/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the file name.
 */

int main(int argc, char ** argv){
    /*call TKCreate() with the filename*/
    TokenizerT *tokenizer = TKCreate(argv[1]);
    
    /*check the argument*/
    if (tokenizer == NULL){
        printf("Problem with input. Exiting program.");
        return 0;
    }

    /*call TKPrint() with the returned object and print out the result + error message*/
    TKPrint(tokenizer);
    /*destroy all the dynamically allocated memory*/
    TKDestroy(tokenizer);
    
    return 0;
}
