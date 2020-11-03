//
// Created by paula on 03/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H
#define I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H

#include <stdio.h>
#include "error_gestion.h"
#include <stdlib.h>
#include <string.h>

typedef struct File_information{
    FILE* fp;
    char* fileName;
    int actualLine;
    int actualColumn;
    ERROR* error;
} File_information;

File_information* initialiseFileInformation(char* fileName);

#endif //I_M_IN_LOVE_WITH_THE_XML_FILE_INFORMATION_H
