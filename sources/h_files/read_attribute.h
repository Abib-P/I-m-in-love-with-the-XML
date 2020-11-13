//
// Created by paula on 08/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H

#include "includes.h"
#include "file_information.h"
#include "read_xml.h"
#include "char_useful.h"

typedef struct Attribute{
    char* attributeName;
    char* attributeValue;
} Attribute;

void addAttributeToXmlMarkup(File_information * fileInfo,struct XML_basic*  xmlMarkup);
void freeAttribute(Attribute* attribute);

#endif //I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H
