//
// Created by paula on 15/11/2020.
//

#include "../h_files/launch_dtd.h"

markupContainer* launchDtd(char *dtdFileName) {
    File_information* dtdFileInfo = initialiseFileInformation(dtdFileName);
    markupContainer* markupArray = find_dtd_content(dtdFileInfo);
    return markupArray;
}

void showDtd(markupContainer* markupArray) {
    for (int i = 0; i < markupArray->size; i += 1) {
        printf("\n index : %d ", i);
        removeFinalSpacesOfString(markupArray->markupArray[i].markup_type);
        printf("| type : %s ", markupArray->markupArray[i].markup_type);
        removeFinalSpacesOfString(markupArray->markupArray[i].markup_name);
        printf("| name : %s", markupArray->markupArray[i].markup_name);

        if (markupArray->markupArray[i].markup_parameters.parameter_type != NULL) {
            if (strcmp(markupArray->markupArray[i].markup_parameters.parameter_type, "category") == 0) {
                removeFinalSpacesOfString(markupArray->markupArray[i].markup_name);
                printf(" | param : %s", markupArray->markupArray[i].markup_parameters.category);
            } else if (strcmp(markupArray->markupArray[i].markup_parameters.parameter_type, "element") == 0) {
                printf(" | param : ");
                for (int j = 0; j <= markupArray->markupArray[i].markup_parameters.element.elements_size; j += 1) {
                    removeFinalSpacesOfString(markupArray->markupArray[i].markup_parameters.element.elements[j]);
                    printf("%s ", markupArray->markupArray[i].markup_parameters.element.elements[j]);
                }
            } else {
                removeFinalSpacesOfString(markupArray->markupArray[i].markup_parameters.attribute.attribute_name);
                printf(" | param : %s, ", markupArray->markupArray[i].markup_parameters.attribute.attribute_name);
                removeFinalSpacesOfString(markupArray->markupArray[i].markup_parameters.attribute.attribute_type);
                printf("%s, ", markupArray->markupArray[i].markup_parameters.attribute.attribute_type);
                removeFinalSpacesOfString(markupArray->markupArray[i].markup_parameters.attribute.attribute_value);
                printf("%s", markupArray->markupArray[i].markup_parameters.attribute.attribute_value);
            }
        }
    }
}
