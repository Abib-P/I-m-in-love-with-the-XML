//
// Created by paula on 14/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_XMLFILE_READ_H
#define I_M_IN_LOVE_WITH_THE_XML_XMLFILE_READ_H

#include "read_xml.h"
#include "read_comment.h"

typedef struct XML_instruction{
    char* elementName;
    struct Attribute** attributeList;
    int attributeSize;
    int attributeCapacity;
} XML_instruction;

typedef struct XML_tree{
    XML_instruction** instructionList;
    int instructionSize;
    int instructionCapacity;
    char* comment;
    int commentSize;
    int commentCapacity;
    struct XML_basic* rootMarkup;
} XML_tree;

XML_tree* readXml(File_information* fileInformation);

XML_tree* createXmlTree();

void readInstruction(File_information* fileInformation, XML_tree* xmlTree);

void freeXml_tree(XML_tree *xmlTree);

#endif //I_M_IN_LOVE_WITH_THE_XML_XMLFILE_READ_H
