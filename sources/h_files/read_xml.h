//
// Created by paula on 22/10/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READXML_H
#define I_M_IN_LOVE_WITH_THE_XML_READXML_H

#include "includes.h"
#include "file_information.h"
#include "read_attribute.h"

typedef struct XML_basic{
    char* elementName ;
    char* value;
    int valueSize;
    int valueCapacity;
    struct XML_basic** markupList;
    int markupSize;
    int markupCapacity;
    struct Attribute** attributeList;
    int attributeSize;
    int attributeCapacity;
    char* comment;
    int commentSize;
    int commentCapacity;
} XML_basic;

void readInsideXml(struct File_information* fileInfo, XML_basic* xmlParent);

XML_basic* createRootXmlBasic(struct File_information* fileInformation);

XML_basic* createXmlBasic(struct File_information* fileInformation, XML_basic* xmlParent);

void addNewXmlMarkupToParent(XML_basic* xmlParent, XML_basic* xmlChild);

void freeXml_basic(XML_basic *xmlMarkup);

void showXmlMarkup(XML_basic *xmlMarkup, int nbTab);

#endif //I_M_IN_LOVE_WITH_THE_XML_READXML_H
