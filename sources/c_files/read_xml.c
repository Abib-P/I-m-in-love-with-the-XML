//
// Created by paula on 22/10/2020.
//

#include "../h_files/read_xml.h"

void readInsideXml(File_information* fileInfo, XML_basic* xmlParent) {
    char actualCharRead = getFirstCharacterAfterSpace(fileInfo);
    while(1) {
        while (actualCharRead != '>' && actualCharRead != EOF) {
            if(actualCharRead == '<')
            {
                if(getNextCharacterInFile(fileInfo) == '!')
                {
                    if(getNextCharacterInFile(fileInfo) == '-')
                    {
                        if(getNextCharacterInFile(fileInfo) == '-')
                        {
                            readCommentInsideXml(fileInfo,xmlParent);
                            actualCharRead = getNextCharacterInFile(fileInfo);
                        }
                        else{
                            char buffer_where[1000]; //TODO taille arbitraire
                            char buffer_error_value[1000]; //TODO taille arbitraire

                            rewindOnce(fileInfo);
                            sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
                            sprintf(buffer_error_value, "xml comment must be construct like so : \"<!--comment--> \"");
                            fileInfo->error = createError(buffer_where,buffer_error_value);
                            return;
                        }
                    }
                    else{
                        char buffer_where[1000]; //TODO taille arbitraire
                        char buffer_error_value[1000]; //TODO taille arbitraire

                        rewindOnce(fileInfo);
                        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
                        sprintf(buffer_error_value, "xml comment must be construct like so : \"<!--comment--> \"");
                        fileInfo->error = createError(buffer_where,buffer_error_value);
                        return;
                    }
                }
                else
                {
                    rewindOnce(fileInfo);
                    break;
                }
            }
            else{
                addCharacterToStringValue(xmlParent, actualCharRead);
                actualCharRead = getNextCharacterInFile(fileInfo);
            }
        }
        if (actualCharRead == '>' || actualCharRead == EOF) {
            char buffer_where[1000]; //TODO taille arbitraire
            char buffer_error_value[1000]; //TODO taille arbitraire

            rewindOnce(fileInfo);
            sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
            sprintf(buffer_error_value, "\'<\' character is expected");
            fileInfo->error = createError(buffer_where, buffer_error_value);
            return;
        } else {
                    removeFinalSpacesOfString(xmlParent->value);
                    actualCharRead = getNextCharacterInFile(fileInfo);
                    if(actualCharRead == '/')
                    {

                        char *bufferElementName = getElementName(fileInfo);
                        if(fileInfo->error != NULL)
                        {
                            return;
                        }
                        if(strcmp(xmlParent->elementName,bufferElementName) == 0)
                        {
                            if(getFirstCharacterAfterSpace(fileInfo) == '>')
                            {
                                free(bufferElementName);
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
                        rewindOnce(fileInfo);
                        XML_basic* newXmlElement = createXmlBasic(fileInfo, xmlParent);
                        if(fileInfo->error != NULL)
                        {
                            return;
                        }
                        if(getFirstCharacterAfterSpace(fileInfo) == '/' ){
                            if(getNextCharacterInFile(fileInfo) == '>'){
                                addNewXmlMarkupToParent(xmlParent,newXmlElement);
                                actualCharRead = getFirstCharacterAfterSpace(fileInfo);
                            }
                            else{
                                char buffer_where[1000]; //TODO taille arbitraire
                                char buffer_error_value[1000]; //TODO taille arbitraire

                                rewindOnce(fileInfo);
                                sprintf(buffer_where, "%s at %d:%d", fileInfo->fileName, fileInfo->actualLine, fileInfo->actualColumn);
                                sprintf(buffer_error_value, "the character after \'/\' must be \'>\'");
                                fileInfo->error = createError(buffer_where, buffer_error_value);
                                return;
                            }
                        }
                        else{
                            addNewXmlMarkupToParent(xmlParent,newXmlElement);
                            readInsideXml(fileInfo,newXmlElement);
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

XML_basic* createXmlBasic(File_information *fileInfo, XML_basic* xmlParent) {
    XML_basic* result = malloc(sizeof(XML_basic));

    result->elementName = getElementName(fileInfo);

    result->markupList = NULL;
    result->markupCapacity = 0;
    result->markupSize = 0;

    result->value = NULL;
    result->valueSize = 0;
    result->valueCapacity = 0;

    result->attributeList = NULL;
    result->attributeSize = 0;
    result->attributeCapacity = 0;

    result->comment = NULL;
    result->commentSize = 0;
    result->commentCapacity =0;

    char actualCharacterRead = getFirstCharacterAfterSpace(fileInfo);
    while(actualCharacterRead != '>' && actualCharacterRead != '/'){
        rewindOnce(fileInfo);
        addAttributeToXmlMarkup(fileInfo, result);
        if(fileInfo->error != NULL)
        {
            if(result->elementName == NULL)
                free(result->elementName);
            if(result == NULL)
                free(result);
            return NULL;
        }
        actualCharacterRead = getFirstCharacterAfterSpace(fileInfo);
    }
    rewindOnce(fileInfo);
    return result;
}

XML_basic *createRootXmlBasic(File_information *fileInfo) {
    XML_basic* result = malloc(sizeof(XML_basic));

    result->elementName = getElementName(fileInfo);

    result->markupList = NULL;
    result->markupCapacity = 0;
    result->markupSize = 0;

    result->value = NULL;
    result->valueSize = 0;
    result->valueCapacity = 0;

    result->attributeList = NULL;
    result->attributeSize = 0;
    result->attributeCapacity = 0;

    result->comment = NULL;
    result->commentSize = 0;
    result->commentCapacity =0;

    char actualCharacterRead = getFirstCharacterAfterSpace(fileInfo);
    while(actualCharacterRead != '>' && actualCharacterRead != '/'){
        rewindOnce(fileInfo);
        addAttributeToXmlMarkup(fileInfo, result);
        if(fileInfo->error != NULL)
        {
            free(result);
            return NULL;
        }
        actualCharacterRead = getFirstCharacterAfterSpace(fileInfo);
     }
    return result;
}

void addNewXmlMarkupToParent(XML_basic *xmlParent, XML_basic *xmlChild) {
    if(xmlParent->markupList == NULL){

        xmlParent->markupCapacity = 10;
        xmlParent->markupList = malloc(sizeof(XML_basic*)*xmlParent->markupCapacity);
        xmlParent->markupSize = 0;
    }
    if(xmlParent->markupSize == xmlParent->markupCapacity){

        xmlParent->markupCapacity *= 2;
        XML_basic** newMarkupList = malloc(sizeof(XML_basic*)*xmlParent->markupCapacity);
        for(int i = 0 ; i < xmlParent->markupSize ; i++){
            newMarkupList[i] = xmlParent->markupList[i];
        }
        free(xmlParent->markupList);
        xmlParent->markupList = newMarkupList;
    }
    xmlParent->markupList[xmlParent->markupSize] = xmlChild;
    xmlParent->markupSize++;
}

void freeXml_basic(XML_basic *xmlMarkup) {
    if(xmlMarkup != NULL){
        if(xmlMarkup->elementName != NULL)
        {
            free(xmlMarkup->elementName);
        }
        if(xmlMarkup->value != NULL)
        {
            free(xmlMarkup->value);
        }
        if(xmlMarkup->markupList != NULL)
        {
            for (int i = 0; i < xmlMarkup->markupSize; i++) {
                freeXml_basic(xmlMarkup->markupList[i]);
            }
            free(xmlMarkup->markupList);
        }
        if(xmlMarkup->attributeList != NULL)
        {
            for (int i = 0; i < xmlMarkup->attributeSize; i++) {
                freeAttribute(xmlMarkup->attributeList[i]);
            }
            free(xmlMarkup->attributeList);
        }
        if(xmlMarkup->comment != NULL)
        {
            free(xmlMarkup->comment);
        }
        free(xmlMarkup);
    }
}

void showXmlMarkup(XML_basic *xmlMarkup, int nbTab) {
    for (int i = 0; i < nbTab; i++) {
        printf("\t");
    }
    printf("<%s",xmlMarkup->elementName);
    for (int i = 0; i < xmlMarkup->attributeSize; i++) {
        printf(" %s=\"%s\"",xmlMarkup->attributeList[i]->attributeName,xmlMarkup->attributeList[i]->attributeValue);
    }
    if(xmlMarkup->value == NULL && xmlMarkup->markupList == NULL && xmlMarkup->comment == NULL) //nothing
    {
        printf("/>\n");
        return;
    }
    if(xmlMarkup->value == NULL  && xmlMarkup->markupList == NULL &&xmlMarkup->comment != NULL ) { //comment only
        printf("> <!--%s--> </%s>\n",xmlMarkup->comment,xmlMarkup->elementName);
        return;
    }
    if(xmlMarkup->value != NULL  && xmlMarkup->markupList == NULL &&xmlMarkup->comment == NULL ) { //value only
        printf(">%s</%s>\n",xmlMarkup->value,xmlMarkup->elementName);
        return;
    }
    printf(">\n");

    if(xmlMarkup->comment != NULL) {
        for (int i = 0; i < nbTab + 1; i++) {
            printf("\t");
        }
        printf("<!--%s-->\n",xmlMarkup->comment);
    }

    if(xmlMarkup->value != NULL) {
        for (int i = 0; i < nbTab + 1; i++) {
            printf("\t");
        }
        printf("%s\n",xmlMarkup->value);
    }

    for (int i = 0; i < xmlMarkup->markupSize; i++) {
        showXmlMarkup(xmlMarkup->markupList[i],nbTab+1);
    }
    for (int i = 0; i < nbTab; i++) {
        printf("\t");
    }
    printf("</%s>\n",xmlMarkup->elementName);
}