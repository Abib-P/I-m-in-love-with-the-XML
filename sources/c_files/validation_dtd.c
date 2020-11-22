//
// Created by CHINOISERIZ on 18/11/2020.
//

#include "../h_files/validation_dtd.h"
#include "../h_files/includes.h"

void init_validation_dtd(File_information* dtdFileInfo) {
    validation_rootElement(dtdFileInfo);
}

void read_dtd(File_information* dtdFileInfo) {
    for (char c = getNextCharacterInFile(dtdFileInfo); c != EOF; c = getNextCharacterInFile(dtdFileInfo)) {
        printf("%c", c);
    }
}

void validation_rootElement(File_information* dtdFileInfo) {
    char* str = get_rooTag(dtdFileInfo);
    verification_rootTag(str);
}

char* get_rooTag(File_information* dtdFileInfo) {
    char* result = malloc(sizeof(char) * 200);

    int reader = 1;
    char c = getNextCharacterInFile(dtdFileInfo);
    if (c != '<') {
        while (c != '<') {
            c = getNextCharacterInFile(dtdFileInfo);
            if (c == '>' || c == '['){
                printf("\nerreur < not find");
                break;
            }
        }
    }

    for (int i = 0; c != EOF; i+=1, c = getNextCharacterInFile(dtdFileInfo)) {
        result[i] = c;

        if (c == '[') {
            reader = 0;
            i += 1;
        }
        else if (c == ']') {
            reader = 1;
        }

        if (!reader) {
            i -= 1;
        }
    }

    return result;
}

void verification_rootTag(char* rootTag) {
    for (int i = 0; i < strlen(rootTag); i+=1) {
        printf("%c", rootTag[i]);
        if (rootTag[0] != '<') {
            printf("\nerreur: <");
            return;
        }
        else if (rootTag[1] != '!') {
            printf("\nerreur: !");
            return;
        }
    }
}