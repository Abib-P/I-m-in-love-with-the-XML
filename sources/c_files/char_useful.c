//
// Created by paula on 03/11/2020.
//

#include "../h_files/char_useful.h"

char *getElementName(File_information *fileInfo) {
    int bufferSize = 0;
    char buffer[1000]; //TODO taille arbitraire
    char actualCharRead = (char)fgetc(fileInfo->fp);
    fileInfo->actualColumn++;
    if(actualCharRead == '>' || actualCharRead == '<' || actualCharRead == ' ' || actualCharRead == '/' || actualCharRead == '\n')
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
    while(actualCharRead != '>' && actualCharRead != ' ' && actualCharRead != '<' && actualCharRead != '\n')
    {
        buffer[bufferSize] = actualCharRead;
        bufferSize++;
        actualCharRead = (char)fgetc(fileInfo->fp);
        fileInfo->actualColumn++;
    }
    buffer[bufferSize] = 0;
    if(actualCharRead == '<'){
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
