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
    char* value; //todo refactor to value** to have a char* for each time you encounter a markup
    /*for :
     * <balise>blabla1
     *      <balise1></balise1>blabla2
     * </balise>
     *
     * elementName = "balise";
     * value[0] = "blabla1";
     * value[1] = "blabla2";
     */
    int valueSize;
    int valueCapacity;
    struct XML_basic** markupList;
    int markupSize;
    int markupCapacity;
    struct Attribute** attributeList;
    int attributeSize;
    int attributeCapacity;
} XML_basic;

XML_basic* readXml(File_information* fileInformation);

void readInsideXml(File_information* fileInfo, XML_basic* xmlParent);

XML_basic* createRootXmlBasic(File_information* fileInformation);

XML_basic* createXmlBasic(File_information* fileInformation, XML_basic* xmlParent);

void addNewXmlMarkupToParent(XML_basic* xmlParent, XML_basic* xmlChild);

void freeXml_basic(XML_basic *xmlMarkup);

void showXmlFile(XML_basic *xmlMarkup, int nbTab);

#endif //I_M_IN_LOVE_WITH_THE_XML_READXML_H
