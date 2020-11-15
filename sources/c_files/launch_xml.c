//
// Created by paula on 13/11/2020.
//

#include "../h_files/launch_xml.h"

int launchXml(char *xmlFileName){

    File_information* xmlFileInfo = initialiseFileInformation(xmlFileName);
    XML_tree * xmlFile = NULL;

    if(xmlFileInfo != NULL) //no error during opening file
    {
        xmlFile = readXml(xmlFileInfo);

        if(xmlFileInfo->error != NULL)
        {
            showError(xmlFileInfo->error);
        }
        else{
            if(xmlFile != NULL) {
                if (xmlFile->rootMarkup != NULL) {
                    showXmlFile(xmlFile);
                }
                freeXml_tree(xmlFile);
            }
        }
    } else{
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}