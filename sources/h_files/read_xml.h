//
// Created by paula on 22/10/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READXML_H
#define I_M_IN_LOVE_WITH_THE_XML_READXML_H

#include <stdio.h>
#include "error_gestion.h"
#include "file_information.h"

typedef struct XML_basic{
    char* elementName ;
    char* value; //pcData
    int valueSize;
    int valueCapacity;
    struct XML_basic* parent;
    struct XML_basic* markupList;
    /*
     * struct Attribute attributeList;
     * int attributeSize;
     * int attributeCapacity;
     */
    int markupSize;
    int markupCapacity;
} XML_basic;

XML_basic* readXml(File_information* fileInformation);
void readInsideXml(File_information* fileInfo, XML_basic* xmlParent);
XML_basic* createRootXmlBasic(File_information* fileInformation);
XML_basic createXmlBasic(File_information* fileInformation, XML_basic* xmlParent);
void addNewXmlMarkupToParent(XML_basic* xmlParent, XML_basic xmlChild);

#endif //I_M_IN_LOVE_WITH_THE_XML_READXML_H
