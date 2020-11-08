//
// Created by paula on 03/11/2020.
//

#include "../h_files/file_information.h"

File_information *initialiseFileInformation(char *fileName) {

    File_information* result = malloc(sizeof(File_information));
    errno_t errFile = fopen_s(&result->fp,fileName,"r");

    if(errFile != 0) //error when fopen_s()
    {
        char errorBuffer[1000]; //todo taille arbitraire
        strerror_s(errorBuffer, sizeof errorBuffer, errFile);
        fprintf_s(stderr, "cannot open file '%s': %s\n",fileName, errorBuffer);
        fclose(result->fp);
        return NULL;
    }

    result->actualLine = 1;
    result->fileName = fileName;
    result->actualColumn = 1;

    return result;
}