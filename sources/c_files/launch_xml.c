//
// Created by paula on 13/11/2020.
//

#include "../h_files/launch_xml.h"

XML_tree * launchXml(char *xmlFileName){

    File_information* xmlFileInfo = initialiseFileInformation(xmlFileName);
    XML_tree * xmlFile = NULL;

    if(xmlFileInfo != NULL) //no error during opening file
    {
        xmlFile = readXml(xmlFileInfo);

        if(xmlFileInfo->error != NULL)
        {
            showError(xmlFileInfo->error);
            return NULL;
        }
        else{
            if(xmlFile != NULL) {
                //freeXml_tree(xmlFile); todo implement free this free when we need it
                freeFileInformation(xmlFileInfo);
            }
        }
    } else{
        return NULL;
    }

    return xmlFile;
}