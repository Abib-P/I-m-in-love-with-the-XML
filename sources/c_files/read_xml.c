//
// Created by paula on 22/10/2020.
//

#include "../h_files/read_xml.h"
#include "../h_files/file_useful.h"

XML_basic* readXml(File_information* fileInfo) {
    char actualCharRead = firstCharacterAfterSpace(fileInfo->fp);
    if(actualCharRead != '<')
    {
        sprintf(fileInfo->error->where,"XML at line %d",fileInfo->actualLine);
        sprintf(fileInfo->error->error_value, "\'<\' character is expected");
        return NULL;
    }

    return NULL; //TODO finish the fonction
}
