
#include "../h_files/file_useful.h"

char getFirstCharacterAfterSpace(File_information *fileInformation) {

    char actualCharRead = ' ';
    while(actualCharRead == ' ' || actualCharRead == '\n' || actualCharRead == '\t' || actualCharRead == '\r')
    {
        actualCharRead =  getNextCharacterInFile(fileInformation);
    }
    return actualCharRead;
}

char getNextCharacterInFile(File_information *fileInformation) {

    char actualCharRead = (char)fgetc(fileInformation->fp);
    if(actualCharRead == '\n') {
        fileInformation->nbColumnOnLastLine = fileInformation->actualColumn;
        fileInformation->actualColumn = 1;
        fileInformation->actualLine++;
    } else{
        fileInformation->actualColumn++;
    }

    return actualCharRead;
}

char rewindOnce(File_information *fileInformation) {
    fseek(fileInformation->fp,-1,SEEK_CUR);
    if(fgetc(fileInformation->fp) == '\n')
    {
        fileInformation->actualColumn = fileInformation->nbColumnOnLastLine;
        fileInformation->actualLine--;
    }
    else{
        fileInformation->actualColumn--;
    }
    fseek(fileInformation->fp,-1,SEEK_CUR);
}
