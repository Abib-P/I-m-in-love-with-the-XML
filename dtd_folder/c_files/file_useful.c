//
// Created by paula on 03/11/2020.
//

#include "../h_files/file_useful.h"

char getFirstCharacterAfterSpace(File_information *fileInformation) {

    char actualCharRead = (char)fgetc(fileInformation->fp);
    while(actualCharRead == ' ' || actualCharRead == '\n' || actualCharRead == '\t')
    {
        if(actualCharRead == '\n') {
            fileInformation->actualColumn = 0;
            fileInformation->actualLine++;
        } else{
            fileInformation->actualColumn++;
        }

        actualCharRead =  (char)fgetc(fileInformation->fp);
    }
    return actualCharRead;
}

char getNextCharacterInFile(File_information *fileInformation) {

    char actualCharRead = (char)fgetc(fileInformation->fp);
    if(actualCharRead == '\n') {
        fileInformation->actualColumn = 0;
        fileInformation->actualLine++;
    } else{
        fileInformation->actualColumn++;
    }

    return actualCharRead;
}
