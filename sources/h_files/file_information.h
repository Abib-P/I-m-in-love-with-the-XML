//
// Created by paula on 03/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H
#define I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H

#include "includes.h"
#include "error_gestion.h"

typedef struct File_information{
    FILE* fp;
    char* fileName;
    int actualLine;
    int actualColumn;
    int nbColumnOnLastLine;
    ERROR* error;
} File_information;

File_information* initialiseFileInformation(char* fileName);

void freeFileInformation(File_information* fileInfo);

#endif //I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H