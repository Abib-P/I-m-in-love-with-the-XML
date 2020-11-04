#include <stdio.h>
#include <string.h>
#include "../h_files/file_information.h" //TODO update the #include section
#include "../h_files/read_xml.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main() {
    char * fileName = "test.xml";
    File_information* xmlFileInfo = initialiseFileInformation(fileName);
    XML_basic* xmlFile;

    if(xmlFileInfo != NULL) //no error during opening file
    {
        xmlFile = readXml(xmlFileInfo);
        if(xmlFileInfo->error != NULL)
        {
            showError(xmlFileInfo->error);
        }
    } else{
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
