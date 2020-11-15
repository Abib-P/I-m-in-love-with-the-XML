//
// Created by paula on 03/11/2020.
//

#include "../h_files/char_useful.h"

char *getElementName(File_information *fileInfo) {
    int bufferSize = 0;
    char buffer[1000]; //TODO taille arbitraire
    char actualCharRead = getNextCharacterInFile(fileInfo);
    if(actualCharRead == '>' || actualCharRead == '<' || actualCharRead == ' ' || actualCharRead == '/' || actualCharRead == '\n' || actualCharRead == EOF || actualCharRead == '=')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "Unexpected character \'%c\', you must enter the markup name", actualCharRead);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    buffer[bufferSize] = actualCharRead;
    bufferSize++;
    actualCharRead = getNextCharacterInFile(fileInfo);
    while(actualCharRead != '>' && actualCharRead != ' ' && actualCharRead != '<' && actualCharRead != '\n' && actualCharRead != EOF && actualCharRead != '/' && actualCharRead != '=')
    {
        buffer[bufferSize] = actualCharRead;
        bufferSize++;
        actualCharRead = getNextCharacterInFile(fileInfo);
    }
    buffer[bufferSize] = 0;
    if(actualCharRead == '<' || actualCharRead == EOF || actualCharRead == '='){
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "The element %s must be followed by either attribute specifications ,\">\" or \"/>\"", buffer);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    char* result = malloc(sizeof(char)*bufferSize);
    strcpy(result,buffer);
    rewindOnce(fileInfo);
    return result;
}

void addCharacterToStringValue(XML_basic* actualXmlMarkup, char characterToPut) {

    if(actualXmlMarkup->value == NULL)
    {
        actualXmlMarkup->valueCapacity = 20;
        actualXmlMarkup->value = malloc(sizeof(char)*actualXmlMarkup->valueCapacity);
        actualXmlMarkup->valueSize = 0;
        actualXmlMarkup->value[0] = 0;
    }

    if( (actualXmlMarkup->valueSize+1) == actualXmlMarkup->valueCapacity)
    {
        actualXmlMarkup->valueCapacity *= 2;
        char* newValue = malloc(sizeof(char)*actualXmlMarkup->valueCapacity);
        int index = 0;
        while(actualXmlMarkup->value[index]){
            newValue[index] = actualXmlMarkup->value[index];
            index++;
        }
        newValue[index] = 0;
        free(actualXmlMarkup->value);
        actualXmlMarkup->value = newValue;
    }

    actualXmlMarkup->value[actualXmlMarkup->valueSize] = characterToPut;
    actualXmlMarkup->valueSize++;
    actualXmlMarkup->value[actualXmlMarkup->valueSize] = 0;
}

void removeFinalSpacesOfString(char *string) {
    if(string == NULL)
        return;
    int indexForCut = -1;
    int index = 0;
    while(string[index] != 0)
    {
        if( (string[index] == ' ' || string[index] == '\n' || string[index] == '\t' || string[index] == '\r') && indexForCut == -1){
            indexForCut = index;
        }
        if( (string[index] != ' ' && string[index] != '\n' && string[index] != '\t' && string[index] != '\r') && indexForCut != -1) {
            indexForCut = -1;
        }
        index++;
    }
    if(indexForCut != -1)
    {
        string[indexForCut] = 0;
    }
}

char* getAttributeName(File_information *fileInfo) {
    int bufferSize = 0;
    char buffer[1000]; //TODO taille arbitraire
    char actualCharRead = getNextCharacterInFile(fileInfo);
    if(actualCharRead == '>' || actualCharRead == '<' || actualCharRead == ' ' || actualCharRead == '/' || actualCharRead == '\n' || actualCharRead == EOF || actualCharRead == '=')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "Unexpected character \'%c\', you must enter the attribute name", actualCharRead);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    buffer[bufferSize] = actualCharRead;
    bufferSize++;
    actualCharRead = getNextCharacterInFile(fileInfo);
    while(actualCharRead != '>' && actualCharRead != ' ' && actualCharRead != '<' && actualCharRead != '\n' && actualCharRead != EOF && actualCharRead != '/' && actualCharRead != '=')
    {
        buffer[bufferSize] = actualCharRead;
        bufferSize++;
        actualCharRead = getNextCharacterInFile(fileInfo);
    }
    buffer[bufferSize] = 0;
    if(actualCharRead != '='){
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "The attribute %s must be followed by attribute specifications <markup attribute=\"value\">", buffer);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    char* result = malloc(sizeof(char)*bufferSize);
    strcpy(result,buffer);
    return result;
}

char *getAttributeValue(File_information *fileInfo) {
    int bufferSize = 0;
    char buffer[1000]; //TODO taille arbitraire
    char actualCharRead = getNextCharacterInFile(fileInfo);
    if(actualCharRead != '\"')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "Unexpected character \'%c\', you must enter the attribute value like this <markup attribute=\"value\">", actualCharRead);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    actualCharRead = getNextCharacterInFile(fileInfo);
    while(actualCharRead != '>' && actualCharRead != '<' && actualCharRead != '\n' && actualCharRead != EOF && actualCharRead != '/' && actualCharRead != '=' && actualCharRead != '\"')
    {
        buffer[bufferSize] = actualCharRead;
        bufferSize++;
        actualCharRead = getNextCharacterInFile(fileInfo);
    }
    buffer[bufferSize] = 0;
    if(actualCharRead != '\"'){
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "Unexpected character \'%c\', attribute value must finished with a \"", actualCharRead);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    char* result = malloc(sizeof(char)*bufferSize);
    strcpy(result,buffer);
    return result;
}

void addCharacterToCommentOutside(struct XML_tree *xmlTree, char characterToPut) {

    if(xmlTree->comment == NULL)
    {
        xmlTree->commentCapacity = 20;
        xmlTree->comment = malloc(sizeof(char)*xmlTree->commentCapacity);
        xmlTree->commentSize = 0;
        xmlTree->comment[0] = 0;
    }

    if( (xmlTree->commentSize+1) == xmlTree->commentCapacity)
    {
        xmlTree->commentCapacity *= 2;
        char* newValue = malloc(sizeof(char)*xmlTree->commentCapacity);
        int index = 0;
        while(xmlTree->comment[index]){
            newValue[index] = xmlTree->comment[index];
            index++;
        }
        newValue[index] = 0;
        free(xmlTree->comment);
        xmlTree->comment = newValue;
    }

    xmlTree->comment[xmlTree->commentSize] = characterToPut;
    xmlTree->commentSize++;
    xmlTree->comment[xmlTree->commentSize] = 0;
}

void addCharacterToCommentInside(XML_basic *xmlParent, char characterToPut) {
    if(xmlParent->comment == NULL)
    {
        xmlParent->commentCapacity = 20;
        xmlParent->comment = malloc(sizeof(char)*xmlParent->commentCapacity);
        xmlParent->commentSize = 0;
        xmlParent->comment[0] = 0;
    }

    if( (xmlParent->commentSize+1) == xmlParent->commentCapacity)
    {
        xmlParent->commentCapacity *= 2;
        char* newValue = malloc(sizeof(char)*xmlParent->commentCapacity);
        int index = 0;
        while(xmlParent->comment[index]){
            newValue[index] = xmlParent->comment[index];
            index++;
        }
        newValue[index] = 0;
        free(xmlParent->comment);
        xmlParent->comment = newValue;
    }

    xmlParent->comment[xmlParent->commentSize] = characterToPut;
    xmlParent->commentSize++;
    xmlParent->comment[xmlParent->commentSize] = 0;
}
