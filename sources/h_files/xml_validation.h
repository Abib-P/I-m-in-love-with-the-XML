//
// Created by paula on 19/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H
#define I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H

#include "xmlfile_read.h"
#include "read_dtd.h"

int xmlValidation(struct XML_tree* xmlTree,struct markupContainer* markupArray);

int xmlMarkupValidation(struct XML_basic * xmlMarkup,struct markupContainer* dtdMarkupArray);

#endif //I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H
