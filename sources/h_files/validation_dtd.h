//
// Created by CHINOISERIZ on 18/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_VALIDATION_DTD_H
#define I_M_IN_LOVE_WITH_THE_XML_VALIDATION_DTD_H

#include "../h_files/file_information.h"
#include "../h_files/file_useful.h"
#include "includes.h"

void init_validation_dtd(File_information* dtdFileInfo);
void read_dtd(File_information* dtdFileInfo);
void validation_rootElement(File_information* dtdFileInfo);
void verification_rootTag(char* rootTag);
char* get_rooTag(File_information* dtdFileInfo);


#endif //I_M_IN_LOVE_WITH_THE_XML_VALIDATION_DTD_H
