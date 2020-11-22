//
// Created by paula on 21/11/2020.
//

#include "../h_files/test.h"

void startTest(){
    for (int i = 0; i < 4; i++) {
        char dtdOkName[40];
        char dtdErrorName[40];
        char xmlName[40];
        sprintf(dtdErrorName,"../resources/test%d_ERREUR.dtd",i);
        sprintf(dtdOkName,"../resources/test%d_OK.dtd",i);
        sprintf(xmlName,"../resources/test%d.xml",i);
        XML_tree * testXmlTree = launchXml(xmlName);
        if(testXmlTree != NULL)
        {
            printf("\n");
            markupContainer * errorMarkupContainer = launchDtd(dtdErrorName);
            markupContainer * okMarkupContainer = launchDtd(dtdOkName);
            if (errorMarkupContainer != NULL)
            {
                printf("test n %d avec erreur : ", i);
                if (!xmlValidation(testXmlTree,errorMarkupContainer)){
                    printf("erreur présente comme prévu\n");
                }else{
                    printf("HEUUUUUUUUUUUUU\n");
                }
            }
            if (okMarkupContainer != NULL)
            {
                printf("test n %d sans erreur : ", i);
                if (!xmlValidation(testXmlTree,okMarkupContainer)){
                    printf("HEUUUUUUUUUUUUU\n");
                }else{
                    printf("pas d'erreur, comme prévu\n");
                }
            }
            freeXml_tree(testXmlTree);
        }
        printf("\n###############################################\n");
    }
}

void startTestWithTerminal(){
    for (int i = 0; i < 4; i++) {
        char dtdOkName[40];
        char dtdErrorName[40];
        char xmlName[40];
        sprintf(dtdErrorName,"../resources/test%d_ERREUR.dtd",i);
        sprintf(dtdOkName,"../resources/test%d_OK.dtd",i);
        sprintf(xmlName,"../resources/test%d.xml",i);
        XML_tree * testXmlTree = launchXml(xmlName);
        if(testXmlTree != NULL)
        {
            printf("\n");
            showXmlFile(testXmlTree);
            printf("\n");
            markupContainer * errorMarkupContainer = launchDtd(dtdErrorName);
            markupContainer * okMarkupContainer = launchDtd(dtdOkName);
            if (errorMarkupContainer != NULL)
            {
                printf("test n %d avec erreur : ", i);
                if (!xmlValidation(testXmlTree,errorMarkupContainer)){
                    printf("erreur présente comme prévu\n");
                    showDtd(errorMarkupContainer);
                    printf("\n");
                    printf("\n");
                }else{
                    printf("HEUUUUUUUUUUUUU\n");
                }
            }
            if (okMarkupContainer != NULL)
            {
                printf("test n %d sans erreur : ", i);
                if (!xmlValidation(testXmlTree,okMarkupContainer)){
                    printf("HEUUUUUUUUUUUUU\n");
                }else{
                    printf("pas d'erreur, comme prévu\n");
                    showDtd(okMarkupContainer);
                    printf("\n");
                }
            }
            freeXml_tree(testXmlTree);
        }
        printf("\n###############################################\n");
    }
}