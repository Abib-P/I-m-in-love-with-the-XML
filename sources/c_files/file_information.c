//
// Created by paula on 03/11/2020.
//

#include "../h_files/file_information.h"

File_information *initialiseFileInformation(char *fileName) {

    File_information* result = malloc(sizeof(File_information));
    result->fp = fopen(fileName,"r");

    if(result->fp == NULL) //error when fopen_s()
    {
        fprintf(stderr, "cannot open file '%s'\n",fileName);
        fclose(result->fp);
        return NULL;
    }

    result->actualLine = 1;
    result->fileName = fileName;
    result->actualColumn = 1;

    return result;
}
