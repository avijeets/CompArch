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
    /*check the argument*/
    printf("Reading the FILE %s\n", argv[1]);
    
    /*call TKCreate() with the filename*/
    TKCreate(argv[1]);
    
    /*call TKPrint() with the returned object and print out the result + error message*/
    
    /*destroy all the dynamically allocated memory*/
    dummyFunc();
    
    return 0;
}
