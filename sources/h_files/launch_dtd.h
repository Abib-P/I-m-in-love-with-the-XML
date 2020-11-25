//
// Created by paula on 15/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_LAUNCH_DTD_H
#define I_M_IN_LOVE_WITH_THE_XML_LAUNCH_DTD_H

#include "includes.h"
#include "file_information.h"
#include "read_dtd.h"
#include "char_useful.h"

struct markupContainer* launchDtd(char *xmlFileName);

void showDtd(struct markupContainer* markupArray);

#endif //I_M_IN_LOVE_WITH_THE_XML_LAUNCH_DTD_H