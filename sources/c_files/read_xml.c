//
// Created by paula on 22/10/2020.
//

#include "../h_files/read_xml.h"
#include "../h_files/file_useful.h"
#include "../h_files/char_useful.h"

XML_basic* readXml(File_information* fileInfo) {
    char actualCharRead = getFirstCharacterAfterSpace(fileInfo);
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

    readInsideXml(fileInfo, xmlRootElement);

    return xmlRootElement; //TODO finish the fonction
}

void readInsideXml(File_information* fileInfo, XML_basic* xmlParent) {
    char actualCharRead = getFirstCharacterAfterSpace(fileInfo);
    while(actualCharRead != '<' && actualCharRead != '>' && actualCharRead != EOF)
    {
        addCharacterToStringValue(xmlParent,actualCharRead);
        actualCharRead = getNextCharacterInFile(fileInfo);
        /* //todo user enter an predefined entities (&amp; for & or &quot; for " )
         *if (actualCharRead == '&'){
         *
         * }
        */
    }
    if(actualCharRead == '<')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "\'<\' character is expected");
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
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

    result->markerList = NULL;
    result->markerCapacity = 0;
    result->markerSize = 0;

    result->value = NULL;
    result->valueSize = 0;
    result->valueCapacity = 0;

    /*
     * result->attributeList = NULL;
     * result->attributeSize = 0;
     * result->attributeCapacity = 0;
     */

    /*
     * if(getFirstCharacterAfterSpace(fileInfo) != >){
     *      result->attribute = getAttribute(fileInfo);
     * }
    */

    printf("%c", getFirstCharacterAfterSpace(fileInfo)); //todo suppr
    return result;
}