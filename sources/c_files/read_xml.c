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
    if(fileInfo->error != NULL)
    {
        if(xmlRootElement != NULL)
            free(xmlRootElement);
        return NULL;
    }
    readInsideXml(fileInfo, xmlRootElement);

    return xmlRootElement;
}

void readInsideXml(File_information* fileInfo, XML_basic* xmlParent) {
    char actualCharRead = getFirstCharacterAfterSpace(fileInfo);
    while(1) {
        while (actualCharRead != '<' && actualCharRead != '>' && actualCharRead != EOF) {
            if(strcmp(xmlParent->elementName,"classrooms") == 0)
            {
                if(actualCharRead == 'c'){
                    for(int i = 0 ; i < 30 ; i++)
                    {
                        printf("%c",actualCharRead);
                        actualCharRead=fgetc(fileInfo->fp);
                    }
                }
            }
            addCharacterToStringValue(xmlParent, actualCharRead);
            actualCharRead = getNextCharacterInFile(fileInfo);

            /* //todo user enter an predefined entities (&amp; for & or &quot; for " )
             *if (actualCharRead == '&'){
             *
             * }
            */
        }
        if (actualCharRead == '>' || actualCharRead == EOF) {
            char buffer_where[1000]; //TODO taille arbitraire
            char buffer_error_value[1000]; //TODO taille arbitraire


            sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
            sprintf(buffer_error_value, "\'<\' character is expected");
            fileInfo->error = createError(buffer_where, buffer_error_value);
            return;
        } else {
                    removeFinalSpacesOfString(xmlParent->value);
                    actualCharRead = (char)fgetc(fileInfo->fp);
                    if(actualCharRead == '/')
                    {
                        fileInfo->actualColumn++;

                        char *bufferElementName = getElementName(fileInfo);
                        if(strcmp(xmlParent->elementName,bufferElementName) == 0)
                        {
                            if(getFirstCharacterAfterSpace(fileInfo) == '>')
                            {
                                return;
                            }
                            else{
                                char buffer_where[1000]; //TODO taille arbitraire
                                char buffer_error_value[1000]; //TODO taille arbitraire


                                sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
                                sprintf(buffer_error_value, "the markup must be closed by a \'>\' character");
                                fileInfo->error = createError(buffer_where, buffer_error_value);
                                return;
                            }
                        }
                        else
                        {
                            char buffer_where[1000]; //TODO taille arbitraire
                            char buffer_error_value[1000]; //TODO taille arbitraire


                            sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
                            sprintf(buffer_error_value, "the closing markup must match %s markup (actual is %s)", xmlParent->elementName, bufferElementName);
                            fileInfo->error = createError(buffer_where, buffer_error_value);
                            return;
                        }
                        if(fileInfo->error != NULL)
                        {
                            return;
                        }
                    }
                    else{
                        fseek(fileInfo->fp, -1 , SEEK_CUR);
                        XML_basic newXmlElement = createXmlBasic(fileInfo, xmlParent);

                        if(getFirstCharacterAfterSpace(fileInfo) == '/' ){
                            if(getNextCharacterInFile(fileInfo) == '>'){
                                addNewXmlMarkupToParent(xmlParent,newXmlElement);
                                actualCharRead = getFirstCharacterAfterSpace(fileInfo);
                            }
                            else{
                                char buffer_where[1000]; //TODO taille arbitraire
                                char buffer_error_value[1000]; //TODO taille arbitraire


                                sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
                                sprintf(buffer_error_value, "the character after \'/\' must be \'>\'");
                                fileInfo->error = createError(buffer_where, buffer_error_value);
                                return;
                            }
                        }
                        else{
                            addNewXmlMarkupToParent(xmlParent,newXmlElement);
                            readInsideXml(fileInfo,&newXmlElement);
                            actualCharRead = getFirstCharacterAfterSpace(fileInfo);
                        }
                        if(fileInfo->error != NULL)
                        {
                            return;
                        }
                    }
        }
    }
}

XML_basic createXmlBasic(File_information *fileInfo, XML_basic* xmlParent) {
    XML_basic result;

    result.elementName = getElementName(fileInfo);

    result.parent = xmlParent;

    result.markupList = NULL;
    result.markupCapacity = 0;
    result.markupSize = 0;

    result.value = NULL;
    result.valueSize = 0;
    result.valueCapacity = 0;

    /*
     * result.attributeList = NULL;
     * result.attributeSize = 0;
     * result.attributeCapacity = 0;
     */

    /*
     * if(getFirstCharacterAfterSpace(fileInfo) != >){
     *      result.attribute = getAttribute(fileInfo);
     * }
    */


    return result;
}

XML_basic *createRootXmlBasic(File_information *fileInfo) {
    XML_basic* result = malloc(sizeof(XML_basic));

    result->elementName = getElementName(fileInfo);

    result->parent = NULL;

    result->markupList = NULL;
    result->markupCapacity = 0;
    result->markupSize = 0;

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

void addNewXmlMarkupToParent(XML_basic *xmlParent, XML_basic xmlChild) {
    if(xmlParent->markupList == NULL){

        xmlParent->markupCapacity = 10;
        xmlParent->markupList = malloc(sizeof(XML_basic)*xmlParent->markupCapacity);
        xmlParent->markupSize = 0;
    }
    if(xmlParent->markupSize == xmlParent->markupCapacity){

        xmlParent->markupCapacity *= 2;
        XML_basic* newMarkupList = malloc(sizeof(XML_basic)*xmlParent->markupCapacity);
        for(int i = 0 ; i < xmlParent->markupSize ; i++){
            newMarkupList[i] = xmlParent->markupList[i];
        }
        free(xmlParent->markupList);
        xmlParent->markupList = newMarkupList;
    }
    xmlParent->markupList[xmlParent->markupSize] = xmlChild;
}
