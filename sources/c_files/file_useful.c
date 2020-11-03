//
// Created by paula on 03/11/2020.
//

#include "../h_files/file_useful.h"

char firstCharacterAfterSpace(FILE *fp) {
    char actualCharRead = (char)fgetc(fp);
    while(actualCharRead == ' ' || actualCharRead == '\n')
    {
        actualCharRead =  (char)fgetc(fp);
    }
    return actualCharRead;
}
