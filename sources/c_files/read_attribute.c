//
// Created by paula on 08/11/2020.
//

#include "../h_files/read_attribute.h"

void addAttributeToXmlMarkup(File_information *fileInfo, XML_basic *xmlParent) {
    if(xmlParent->attributeList == NULL){
        xmlParent->attributeCapacity = 5;
        xmlParent->attributeList = malloc(sizeof(Attribute*)*xmlParent->attributeCapacity);
        xmlParent->attributeSize = 0;
    }
    if(xmlParent->attributeSize == xmlParent->attributeCapacity){
        xmlParent->attributeCapacity *= 2;
        Attribute** newAttributeList = malloc(sizeof(Attribute*)*xmlParent->attributeCapacity);
        for(int i = 0 ; i < xmlParent->attributeSize ; i++){
            newAttributeList[i] = xmlParent->attributeList[i];
            newAttributeList[i] = xmlParent->attributeList[i];
        }
        free(xmlParent->attributeList);
        xmlParent->attributeList = newAttributeList;
    }
    char * attributeName = getAttributeName(fileInfo);
    if(fileInfo->error != NULL){
        return;
    }
    char * attributeValue = getAttributeValue(fileInfo);
    if(fileInfo->error != NULL){
        if (attributeName != NULL) {
            free(attributeName);
        }
        return;
    }
    xmlParent->attributeList[xmlParent->attributeSize] = malloc(sizeof(struct Attribute));
    xmlParent->attributeList[xmlParent->attributeSize]->attributeValue = attributeValue;
    xmlParent->attributeList[xmlParent->attributeSize]->attributeName = attributeName;
    xmlParent->attributeSize++;
}

void freeAttribute(Attribute *attribute) {
    if(attribute != NULL)
    {
        if(attribute->attributeName != NULL)
        {
            free(attribute->attributeName);
        }
        if(attribute->attributeValue != NULL)
        {
            free(attribute->attributeValue);
        }
        free(attribute);
    }
}
