//
// Created by paula on 13/11/2020.
//

#include "../h_files/launch_xml.h"

int launchXml(char *xmlFileName){

    File_information* xmlFileInfo = initialiseFileInformation(xmlFileName);
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