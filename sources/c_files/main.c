#include <stdio.h>
#include <string.h>
#include "../h_files/file_information.h" //TODO update the #include section
#include "../h_files/read_xml.h"

#define EXIT_SUCCESS 0 //todo install valgrind
#define EXIT_FAILURE 1 //todo install WSL for linux
//todo fix the column of file_information for the error
//todo treat the comment for the xml file
//todo treat the instruction markup (<?xml-stylesheet ... ?>)

int main() {
    char * fileName = "../resources/test.xml";
    File_information* xmlFileInfo = initialiseFileInformation(fileName);
    XML_basic* xmlFile;

    if(xmlFileInfo != NULL) //no error during opening file
    {
        xmlFile = readXml(xmlFileInfo);

        printf("%s : %s\n",xmlFile->elementName, xmlFile->value);
        printf("%s : Attribute %s\n",xmlFile->attributeList[0]->attributeName,xmlFile->attributeList[0]->attributeValue);
        printf("%s : Attribute %s\n",xmlFile->attributeList[1]->attributeName,xmlFile->attributeList[1]->attributeValue);
        printf("\t%s : %s\n",xmlFile->markupList[0]->elementName,xmlFile->markupList[0]->value);
        printf("\t%s : %s\n",xmlFile->markupList[1]->elementName,xmlFile->markupList[1]->value);
        printf("\t%s : Attribute %s\n",xmlFile->markupList[1]->attributeList[0]->attributeName,xmlFile->markupList[1]->attributeList[0]->attributeValue);
        printf("\t%s : %s\n",xmlFile->markupList[2]->elementName,xmlFile->markupList[2]->value);
        printf("\t%s : %s\n",xmlFile->markupList[3]->elementName,xmlFile->markupList[3]->value);
        printf("\t%s : %s\n",xmlFile->markupList[4]->elementName,xmlFile->markupList[4]->value);
        printf("\t\t%s : %s\n",xmlFile->markupList[4]->markupList[0]->elementName,xmlFile->markupList[4]->markupList[0]->value);
        printf("\t\t\t%s : %s\n",xmlFile->markupList[4]->markupList[0]->markupList[0]->elementName,xmlFile->markupList[4]->markupList[0]->markupList[0]->value);
        printf("\t\t\t%s : Attribute %s\n",xmlFile->markupList[4]->markupList[0]->markupList[0]->attributeList[0]->attributeName,xmlFile->markupList[4]->markupList[0]->markupList[0]->attributeList[0]->attributeValue);
        if(xmlFileInfo->error != NULL)
        {
            showError(xmlFileInfo->error);
        }
    } else{
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
