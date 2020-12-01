
#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H

#include "includes.h"
#include "file_information.h"
#include "read_xml.h"
#include "char_useful.h"
#include "xmlfile_read.h"

typedef struct Attribute{
    char* attributeName;
    char* attributeValue;
} Attribute;

void addAttributeToXmlMarkup(struct File_information * fileInfo,struct XML_basic*  xmlMarkup);

void addAttributeToXmlInstruction(struct File_information *fileInfo,struct XML_instruction *xmlParent);

void freeAttribute(struct Attribute* attribute);

#endif //I_M_IN_LOVE_WITH_THE_XML_READ_ATTRIBUTE_H
