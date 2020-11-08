//
// Created by paula on 03/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H
#define I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H

#include "file_information.h"
#include "read_xml.h"

char * getElementName(File_information *fileInfo);
void addCharacterToStringValue(XML_basic* ActualXmlMarkup, char characterToPut);
void removeFinalSpacesOfString(char* string);

#endif //I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H
