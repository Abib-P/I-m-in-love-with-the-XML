
#include "../h_files/launch_verification.h"

int launchVerification(char * dtd,char * xml){

    XML_tree * finalXml = launchXml(xml);
    if(finalXml == NULL)
    {
        return 0;
    }
    markupContainer * finalDtd = launchDtd(dtd);
    if(finalDtd == NULL)
    {
        return 0;
    }
    return xmlValidation(finalXml,finalDtd);
}