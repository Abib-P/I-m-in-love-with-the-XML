//
// Created by paula on 14/11/2020.
//

#include "../h_files/read_comment.h"

void readComment(File_information *fileInfo, struct XML_tree* xmlTree) {
    char actualCharRead = getNextCharacterInFile(fileInfo);
    while(actualCharRead != EOF){
        if(actualCharRead == '-')
        {
            if(getNextCharacterInFile(fileInfo) == '-')
            {
                if(getNextCharacterInFile(fileInfo) == '>')
                {
                    return;
                }
                else
                {
                    rewindOnce(fileInfo);
                    rewindOnce(fileInfo);
                }
            }
            else{
                rewindOnce(fileInfo);
            }
        }
        addCharacterToCommentOutside(xmlTree,actualCharRead);
        actualCharRead = getNextCharacterInFile(fileInfo);
    }
}

void readCommentInsideXml(File_information* fileInfo,struct XML_basic *xmlParent){
    char actualCharRead = getNextCharacterInFile(fileInfo);
    while(actualCharRead != EOF){
        if(actualCharRead == '-')
        {
            if(getNextCharacterInFile(fileInfo) == '-')
            {
                if(getNextCharacterInFile(fileInfo) == '>')
                {
                    return;
                }
                else
                {
                    rewindOnce(fileInfo);
                    rewindOnce(fileInfo);
                }
            }
            else{
                rewindOnce(fileInfo);
            }
        }
        addCharacterToCommentInside(xmlParent,actualCharRead);
        actualCharRead = getNextCharacterInFile(fileInfo);
    }
}
