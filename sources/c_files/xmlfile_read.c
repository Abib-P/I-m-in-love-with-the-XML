//
// Created by paula on 14/11/2020.
//

#include "../h_files/xmlfile_read.h"

XML_tree * readXml(File_information* fileInfo) {
    char actualCharRead = getFirstCharacterAfterSpace(fileInfo);
    if(actualCharRead != '<')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInfo);
        sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
        sprintf(buffer_error_value, "\'<\' character is expected");
        fileInfo->error = createError(buffer_where,buffer_error_value);
        return NULL;
    }
    XML_tree* xmlTree = createXmlTree();

    actualCharRead = getNextCharacterInFile(fileInfo);

    while(actualCharRead == '?' || actualCharRead == '!')
    {
        if(actualCharRead == '?')
        {
            readInstruction(fileInfo, xmlTree);
            if(fileInfo->error != NULL)
            {
                return xmlTree;
            }
        }
        else
        {
            actualCharRead = getNextCharacterInFile(fileInfo);
            if(actualCharRead == '-')
            {
                actualCharRead = getNextCharacterInFile(fileInfo);
                if(actualCharRead == '-')
                {
                    readComment(fileInfo, xmlTree);
                }
                else
                {
                    char buffer_where[1000]; //TODO taille arbitraire
                    char buffer_error_value[1000]; //TODO taille arbitraire

                    rewindOnce(fileInfo);
                    sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
                    sprintf(buffer_error_value, "xml comment must be construct like so : \"<!--comment--> \"");
                    fileInfo->error = createError(buffer_where,buffer_error_value);
                    return xmlTree;
                }
            }
            else
            {
                char buffer_where[1000]; //TODO taille arbitraire
                char buffer_error_value[1000]; //TODO taille arbitraire

                rewindOnce(fileInfo);
                sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
                sprintf(buffer_error_value, "xml comment must be construct like so : \"<!--comment--> \"");
                fileInfo->error = createError(buffer_where,buffer_error_value);
                return xmlTree;
            }
        }
        actualCharRead = getFirstCharacterAfterSpace(fileInfo);
        if(actualCharRead != '<')
        {
            char buffer_where[1000]; //TODO taille arbitraire
            char buffer_error_value[1000]; //TODO taille arbitraire

            rewindOnce(fileInfo);
            sprintf(buffer_where,"%s at %d:%d",fileInfo->fileName ,fileInfo->actualLine, fileInfo->actualColumn);
            sprintf(buffer_error_value, "\'<\' character is expected");
            fileInfo->error = createError(buffer_where,buffer_error_value);
            return xmlTree;
        }
        actualCharRead = getNextCharacterInFile(fileInfo);
        if(actualCharRead != '?' && actualCharRead != '!')
        {
            rewindOnce(fileInfo);
        }
    }

    xmlTree->rootMarkup = createRootXmlBasic(fileInfo);
    if(fileInfo->error != NULL)
    {
        return xmlTree;
    }
    readInsideXml(fileInfo, xmlTree->rootMarkup);

    return xmlTree;
}

XML_tree *createXmlTree() {
    XML_tree* result = malloc(sizeof(XML_tree));

    result->instructionList = NULL;
    result->instructionCapacity = 0;
    result->instructionSize = 0;

    result->comment = NULL;
    result->commentSize = 0;
    result->commentCapacity = 0;

    result->rootMarkup = NULL;

    return result;
}

void readInstruction(File_information *fileInformation, XML_tree *xmlTree) {
    if(xmlTree->instructionList == NULL)
    {
        xmlTree->instructionCapacity = 5;
        xmlTree->instructionList = malloc(sizeof(XML_instruction*)*xmlTree->instructionCapacity);
        xmlTree->instructionSize = 0;
    }
    if(xmlTree->instructionSize == xmlTree->instructionCapacity)
    {
        xmlTree->instructionCapacity *= 2;
        XML_instruction** newInstructionList = malloc(sizeof(XML_instruction*)*xmlTree->instructionCapacity);
        for (int i = 0; i < xmlTree->instructionSize; i++) {
            newInstructionList[i] = xmlTree->instructionList[i];
        }
        free(xmlTree->instructionList);
        xmlTree->instructionList = newInstructionList;
    }
    xmlTree->instructionList[xmlTree->instructionSize] = malloc(sizeof(struct XML_instruction));
    xmlTree->instructionList[xmlTree->instructionSize]->elementName = getElementName(fileInformation);
    if(fileInformation->error != NULL){
        return;
    }
    xmlTree->instructionList[xmlTree->instructionSize]->attributeList = NULL;
    char actualCharacterRead = getFirstCharacterAfterSpace(fileInformation);
    while(actualCharacterRead != '?'){
        rewindOnce(fileInformation);
        addAttributeToXmlInstruction(fileInformation, xmlTree->instructionList[xmlTree->instructionSize]);
        if(fileInformation->error != NULL)
        {
            return;
        }
        actualCharacterRead = getFirstCharacterAfterSpace(fileInformation);
    }
    actualCharacterRead = getNextCharacterInFile(fileInformation);
    if(actualCharacterRead != '>')
    {
        char buffer_where[1000]; //TODO taille arbitraire
        char buffer_error_value[1000]; //TODO taille arbitraire

        rewindOnce(fileInformation);
        sprintf(buffer_where, "%s at %d:%d", fileInformation->fileName, fileInformation->actualLine, fileInformation->actualColumn);
        sprintf(buffer_error_value, "the character after \'?\' must be \'>\' (actual is \'%c\')",actualCharacterRead);
        fileInformation->error = createError(buffer_where, buffer_error_value);
        return;
    }
    xmlTree->instructionSize++;
}

void freeXml_tree(XML_tree *xmlTree) {
    if (xmlTree->comment != NULL){
        free(xmlTree->comment);
    }
    if (xmlTree->rootMarkup != NULL){
        freeXml_basic(xmlTree->rootMarkup);
    }
    if (xmlTree->instructionList != NULL){
        for (int i = 0; i < xmlTree->instructionSize; i++) {
            freeXml_instruction(xmlTree->instructionList[i]);
        }
        free(xmlTree->instructionList);
    }
    free(xmlTree);
}

void freeXml_instruction(XML_instruction *xmlInstruction) {
    if (xmlInstruction->elementName != NULL)
    {
        free(xmlInstruction->elementName);
    }
    if (xmlInstruction->attributeList != NULL)
    {
        for (int i = 0; i < xmlInstruction->attributeSize; i++) {
            freeAttribute(xmlInstruction->attributeList[i]);
        }
        free(xmlInstruction->attributeList);
    }
    free(xmlInstruction);
}

void showXmlFile(XML_tree *xmlTree) {
    if(xmlTree->comment != NULL)
    {
        printf("<!--%s-->\n",xmlTree->comment);
    }
    if(xmlTree->instructionList != NULL) {
        for (int i = 0; i < xmlTree->instructionSize; ++i) {
            printf("<?%s", xmlTree->instructionList[i]->elementName);
            for (int j = 0; j < xmlTree->instructionList[i]->attributeSize; j++) {
                printf(" %s=\"%s\"", xmlTree->instructionList[i]->attributeList[j]->attributeName, xmlTree->instructionList[i]->attributeList[j]->attributeValue);
            }
            printf("?>\n");
        }
    }
    if(xmlTree->rootMarkup != NULL)
    {
        showXmlMarkup(xmlTree->rootMarkup,0);
    }
}

