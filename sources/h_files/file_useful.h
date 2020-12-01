
#ifndef I_M_IN_LOVE_WITH_THE_XML_FILE_USEFUL_H
#define I_M_IN_LOVE_WITH_THE_XML_FILE_USEFUL_H

#include "includes.h"
#include "file_information.h"

char getFirstCharacterAfterSpace(struct File_information* fileInformation);

char getNextCharacterInFile(struct File_information* fileInformation);

char rewindOnce(struct File_information* fileInformation);

#endif //I_M_IN_LOVE_WITH_THE_XML_FILE_USEFUL_H