//
// Created by paula on 03/11/2020.
//

#include "../h_files/char_useful.h"

char *getElementName(File_information *fileInfo) {
    int bufferSize = 0;
    char buffer[1000]; //TODO taille arbitraire
    char actualCharRead = (char)fgetc(fileInfo->fp);
    fileInfo->actualColumn++;
    if(actualCharRead == '>' || actualCharRead == '<' || actualCharRead == ' ' || actualCharRead == '/' || actualCharRead == '\n' || actualCharRead == EOF)
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "Unexpected character \'%c\'", actualCharRead);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    buffer[bufferSize] = actualCharRead;
    bufferSize++;
    actualCharRead = (char)fgetc(fileInfo->fp);
    fileInfo->actualColumn++;
    while(actualCharRead != '>' && actualCharRead != ' ' && actualCharRead != '<' && actualCharRead != '\n' && actualCharRead != EOF )
    {
        buffer[bufferSize] = actualCharRead;
        bufferSize++;
        actualCharRead = (char)fgetc(fileInfo->fp);
        fileInfo->actualColumn++;
    }
    buffer[bufferSize] = 0;
    if(actualCharRead == '<' || actualCharRead == EOF){
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "The element %s must be followed by either attribute specifications ,\">\" or \"/>\"", buffer);
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    char* result = malloc(sizeof(char)*bufferSize);
    strcpy(result,buffer);
    fseek(fileInfo->fp, -1 , SEEK_CUR);
    fileInfo->actualColumn--;
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
