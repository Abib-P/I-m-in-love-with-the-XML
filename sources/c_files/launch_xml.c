
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
                freeFileInformation(xmlFileInfo);
            }
        }
    } else{
        return NULL;
    }

    return xmlFile;
}