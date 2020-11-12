#include <stdio.h>
#include <string.h>
#include "../h_files/file_information.h" //TODO update the #include section
#include "../h_files/read_xml.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1 //todo treat \r \n \t as invisible character of getCharacterAfterSpace
//todo fix the column of file_information for the error
//todo treat the comment for the xml file
//todo treat the instruction markup (<?xml-stylesheet ... ?>)
//todo free actual malloc when returning an error (to not lose the opportunity)
//todo the function that free file_information (and close the document)

int main() {
    char * fileName = "../resources/test.xml";

    File_information* xmlFileInfo = initialiseFileInformation(fileName);
    XML_basic* xmlFile = NULL;

    if(xmlFileInfo != NULL) //no error during opening file
    {
        xmlFile = readXml(xmlFileInfo);

        if (xmlFile != NULL){
            showXmlFile(xmlFile,0);
        }
        free(xmlFile);
        if(xmlFileInfo->error != NULL)
        {
            showError(xmlFileInfo->error);
        }
    } else{
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
