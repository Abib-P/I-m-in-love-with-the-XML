//
// Created by paula on 22/10/2020.
//

#include "../h_files/read_xml.h"
#include "../h_files/file_useful.h"
#include "../h_files/char_useful.h"

XML_basic* readXml(File_information* fileInfo) {
    char actualCharRead = firstCharacterAfterSpace(fileInfo);
    if(actualCharRead != '<')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "\'<\' character is expected");
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }

    //tant que balise root fermante non trouvé

    XML_basic* xmlRootElement = createRootXmlBasic(fileInfo);

    return NULL; //TODO finish the fonction
}

XML_basic *createXmlBasic(File_information *fileInfo) {
    XML_basic* result = malloc(sizeof(XML_basic));

    result->elementName = getElementName(fileInfo);
    return result;
}

XML_basic *createRootXmlBasic(File_information *fileInfo) {
    XML_basic* result = malloc(sizeof(XML_basic));

    result->elementName = getElementName(fileInfo);
    result->parent = NULL;
    result->listCapacity = 10;
    result->list = malloc(sizeof(XML_basic)*result->listCapacity);
    result->listSize = 0;
    result->value = NULL;

    return result;
}
