
#include "../h_files/xml_validation.h"

int xmlValidation(XML_tree *xmlTree, markupContainer *markupArray) {
    removeFinalSpacesOfString(markupArray->markupArray[0].markup_type);
    if(strcmp(markupArray->markupArray[0].markup_type,"!DOCTYPE") != 0)
        return 0;
    removeFinalSpacesOfString(markupArray->markupArray[0].markup_name);
    if(strcmp(xmlTree->rootMarkup->elementName,markupArray->markupArray[0].markup_name) != 0)
        return 0;
    return xmlMarkupValidation(xmlTree->rootMarkup, markupArray);
}

int xmlMarkupValidation(XML_basic *xmlMarkup, markupContainer *dtdMarkupArray) {
    int xmlMarkupExistInDtd = 0;
    for(int i = 0; i < dtdMarkupArray->size; i++)
    {
        removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_type);
        removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_name);
        if (strcmp(dtdMarkupArray->markupArray[i].markup_type, "!ELEMENT") == 0)
        {
            if (strcmp(dtdMarkupArray->markupArray[i].markup_name, xmlMarkup->elementName) == 0)
            {
                xmlMarkupExistInDtd = 1;
                if (strcmp(dtdMarkupArray->markupArray[i].markup_parameters.parameter_type, "category") == 0) {
                    if (xmlMarkup->value == NULL) {
                        return 0;
                    }
                    if (xmlMarkup->markupSize != 0) {
                        return 0;
                    }
                }
                else {
                    int markupChild[dtdMarkupArray->markupArray[i].markup_parameters.element.elements_size + 1];
                    for (int j = 0; j <= dtdMarkupArray->markupArray[i].markup_parameters.element.elements_size; j++) {
                        markupChild[j] = 0;
                    }
                    for (int j = 0; j < xmlMarkup->markupSize; j++) {
                        for (int k = 0; k <= dtdMarkupArray->markupArray[i].markup_parameters.element.elements_size; k++) {
                            removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k]);
                            char tempElementName[strlen(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k])];
                            char lastCharacterOfElementInDtd = lastCharacterOfString(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k]);
                            if (lastCharacterOfElementInDtd == '+' || lastCharacterOfElementInDtd == '?' || lastCharacterOfElementInDtd == '*') {
                                strncpy(tempElementName, dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k], strlen(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k]) - 1);
                                tempElementName[strlen(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k]) - 1] = 0;
                            }
                            else{
                                strcpy(tempElementName, dtdMarkupArray->markupArray[i].markup_parameters.element.elements[k]);
                            }
                            if(strcmp(xmlMarkup->markupList[j]->elementName,tempElementName) == 0){
                                markupChild[k]++;
                            }
                        }
                    }
                    for (int j = 0; j <= dtdMarkupArray->markupArray[i].markup_parameters.element.elements_size; j++) {
                        char lastCharacterOfElementInDtd = lastCharacterOfString(dtdMarkupArray->markupArray[i].markup_parameters.element.elements[j]);
                        if (lastCharacterOfElementInDtd == '+') {
                            if(markupChild[j] == 0){
                                return 0;
                            }
                        }
                        else if (lastCharacterOfElementInDtd == '?'){
                            if(markupChild[j] > 1)
                                return 0;
                        }
                        else if (lastCharacterOfElementInDtd == '*'){
                            //always good
                        }
                        else{
                            if(markupChild[j] != 1)
                                return 0;
                        }
                    }
                }
                break;
            }
        }
    }
    if(xmlMarkupExistInDtd == 0)
    {
        return 0;
    }
    int nbAttList = 0;
    for(int i = 0 ; i < dtdMarkupArray->size; i++) {
        if (strcmp(dtdMarkupArray->markupArray[i].markup_type, "!ATTLIST") == 0) {
            if (strcmp(dtdMarkupArray->markupArray[i].markup_name, xmlMarkup->elementName) == 0) {
                nbAttList++;
            }
        }
    }
    int markupAttribute[nbAttList];
    for (int i = 0; i < nbAttList; i++) {
        markupAttribute[i] = 0;
    }
    for(int i = 0 ; i < xmlMarkup->attributeSize ; i++)
    {
        int attributeExist = 0;
        int indexMarkup = 0;
        for(int j = 0 ; j < dtdMarkupArray->size; j++)
        {
            if (strcmp(dtdMarkupArray->markupArray[j].markup_type, "!ATTLIST") == 0) {
                if (strcmp(dtdMarkupArray->markupArray[j].markup_name, xmlMarkup->elementName) == 0) {
                    if (strcmp(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_name,xmlMarkup->attributeList[i]->attributeName) == 0){
                        attributeExist = 1;
                        if (strcmp(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type, "CDATA") == 0){
                            markupAttribute[indexMarkup] += 1;
                            if(strncmp(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value, "#FIXED",6) == 0){
                                int firstChar = 0;
                                while(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar] != '\"' && dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar] != 0){
                                    firstChar++;
                                }
                                if (dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar] == 0){
                                    return 0;
                                }
                                firstChar++;
                                if (dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar] == 0 || dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar] == '\"'){
                                    return 0;
                                }
                                int lastChar = firstChar+1;
                                while(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] != '\"' && dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] != 0){
                                    lastChar++;
                                }
                                if(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] == 0){
                                    return 0;
                                }
                                dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] = 0;
                                if(strcmp(&dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[firstChar],xmlMarkup->attributeList[i]->attributeValue) != 0){
                                    dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] = '\"';
                                    return 0;
                                }
                                dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_value[lastChar] = '\"';
                            }
                        }
                        else { //if attribute type == "(ent1|ent2|...|...|entN)"
                            markupAttribute[indexMarkup] += 1;
                            int firstChar = 1;
                            int actualChar = 0;
                            int attributeValueExist = 0;
                            if (dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] != '(')
                                return 0;
                            actualChar++;
                            while (dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] != ')' && dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] != 0){
                                if(dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] == '|'){
                                    dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = 0;
                                    if (strcmp(&dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[firstChar],xmlMarkup->attributeList[i]->attributeValue) == 0){
                                        dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = '|';
                                        attributeValueExist = 1;
                                        break;
                                    }
                                    else{
                                        dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = '|';
                                        firstChar = actualChar+1;
                                    }
                                }
                                actualChar++;
                            }
                            if (attributeValueExist == 0) {
                                if (dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] ==
                                    ')') {
                                    dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = 0;
                                    if (strcmp(
                                            &dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[firstChar],
                                            xmlMarkup->attributeList[i]->attributeValue) == 0) {
                                        dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = ')';
                                    } else {
                                        dtdMarkupArray->markupArray[j].markup_parameters.attribute.attribute_type[actualChar] = ')';
                                        return 0;
                                    }
                                }
                                else{
                                    return 0;
                                }
                            }
                        }
                        break;
                    }
                    else{
                        indexMarkup++;
                    }
                }
            }
        }
        if (attributeExist == 0)
        {
            return 0;
        }
    }
    //verif pour require attribute
    int indexMarkupAttribute = 0;
    for (int i = 0; i < dtdMarkupArray->size ; i++) {
        removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_type);
        if (strcmp(dtdMarkupArray->markupArray[i].markup_type, "!ATTLIST") == 0) {
            removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_name);
            if (strcmp(dtdMarkupArray->markupArray[i].markup_name, xmlMarkup->elementName) == 0) {
                removeFinalSpacesOfString(dtdMarkupArray->markupArray[i].markup_parameters.attribute.attribute_value);
                if (strcmp(dtdMarkupArray->markupArray[i].markup_parameters.attribute.attribute_value, "#REQUIRED") == 0){
                    if (markupAttribute[indexMarkupAttribute] == 0){
                        return 0;
                    }
                }
                if (markupAttribute[indexMarkupAttribute] > 1)
                    return 0;
                indexMarkupAttribute++;
            }
        }
    }
    for(int i = 0 ; i < xmlMarkup->markupSize ; i++){
        if(xmlMarkupValidation(xmlMarkup->markupList[i], dtdMarkupArray) == 0)
            return 0;
    }
    return 1;
}