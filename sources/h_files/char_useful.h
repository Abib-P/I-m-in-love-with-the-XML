
#ifndef I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H
#define I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H

#include "includes.h"
#include "file_information.h"
#include "read_xml.h"
#include "file_useful.h"

char * getElementName(struct File_information *fileInfo);

char * getAttributeName(struct File_information *fileInfo);

char * getAttributeValue(struct File_information *fileInfo);

void addCharacterToStringValue(struct XML_basic* ActualXmlMarkup, char characterToPut);

void addCharacterToCommentOutside(struct XML_tree* xmlTree, char characterToPut);

void addCharacterToCommentInside(struct XML_basic* xmlParent, char characterToPut);

void removeFinalSpacesOfString(char* string);

char lastCharacterOfString(char* string);

#endif //I_M_IN_LOVE_WITH_THE_XML_CHAR_USEFUL_H
