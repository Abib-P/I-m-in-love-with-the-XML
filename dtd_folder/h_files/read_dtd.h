//
// Created by hmeng on 04/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_gestion.h"
#include "file_information.h"


/* myDTD ########################################################## */

typedef struct data
{
    char* pcData;
    char** elements;  // child(s) + option(s)
    int elements_size;
    int elements_capacity;
} data;

typedef struct element
{
    char* type;  // !DOCTYPE (root, parent), !ELEMENT (child), !ATTLIST (attribute)
    char* name;
    data parameters;
} element;


/* PROTOTYPES ########################################################## */

void initMyElem(element* myElem, int capacity);
void getElements(File_information*);
void getElements_2(File_information*, int, element*, int* size_myElem);
void getElements_3(File_information*, int, element*, int size_myElem);
void getElements_4(char*, element*, int size_myElem);
void getType(char* str, int* i, element*, int size_myElem);
void getName(char* str, int* i, element*, int size_myElem);
void getParam(char* str, int* i, element*, int size_myElem);


#endif //I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
