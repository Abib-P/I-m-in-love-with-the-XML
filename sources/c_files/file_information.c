
#include "../h_files/file_information.h"

File_information *initialiseFileInformation(char *fileName) {

    File_information* result = malloc(sizeof(File_information));
    result->fp = fopen(fileName,"r");

    if(result->fp == NULL)
    {
        fprintf(stderr, "cannot open file '%s'\n",fileName);
        if (result != NULL)
            free(result);
        return NULL;
    }

    result->nbColumnOnLastLine = 0;
    result->actualLine = 1;
    result->fileName = fileName;
    result->actualColumn = 1;
    result->error = NULL;

    return result;
}

void freeFileInformation(File_information *fileInfo) {
    if (fileInfo->fp != NULL)
    {
        fclose(fileInfo->fp);
    }
    free(fileInfo);
}