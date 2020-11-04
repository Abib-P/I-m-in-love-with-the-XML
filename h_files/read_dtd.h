//
// Created by hmeng on 04/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* myDTD ########################################################## */

typedef union data
{
    char** elements;  // child(s) + option(s)
    char* pcData;
} data;

typedef struct element
{
    char* type;  // !DOCTYPE (root, parent), !ELEMENT (child), !ATTLIST (attribute)
    char* name;
    data parameters;
} element;


/* PROTOTYPES ########################################################## */

FILE* initFile();
void displayFile();
char** arrayElements();
void getInfo(char* str);

#endif //I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
