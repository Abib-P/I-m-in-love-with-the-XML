//
// Created by paula on 19/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H
#define I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H

#include "xmlfile_read.h"
#include "read_dtd.h"

int xmlValidation(XML_tree* xmlTree, markupContainer* markupArray);

int xmlMarkupValidation(XML_basic * xmlMarkup, markupContainer* dtdMarkupArray);

#endif //I_M_IN_LOVE_WITH_THE_XML_XML_VALIDATION_H
