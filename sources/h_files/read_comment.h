//
// Created by paula on 14/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_COMMENT_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_COMMENT_H

#include "file_information.h"
#include "xmlfile_read.h"

void readComment(File_information* fileInformation,struct XML_tree *xmlTree);

void readCommentInsideXml(File_information* fileInformation,struct XML_basic *xmlTree);

#endif //I_M_IN_LOVE_WITH_THE_XML_READ_COMMENT_H