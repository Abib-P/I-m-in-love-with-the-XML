//
// Created by paula on 22/10/2020.
//

#include <stdio.h>
#include "error_gestion.h"
#include "file_information.h"

#ifndef I_M_IN_LOVE_WITH_THE_XML_READXML_H
#define I_M_IN_LOVE_WITH_THE_XML_READXML_H

typedef struct XML_basic{
    char* elementName ;
    char* value ;
    struct XML_basic* parent;
    struct XML_basic* list ;
    int listSize;
    int listCapacity;
} XML_basic;

XML_basic* readXml(File_information*);

#endif //I_M_IN_LOVE_WITH_THE_XML_READXML_H
