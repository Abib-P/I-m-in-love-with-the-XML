//
// Created by hmeng on 04/11/2020.
//

#include "../h_files/read_dtd.h"

void initMyElem(element* myElem, int capacity) {
    for (int i = 0; i < capacity; ++i) {
        myElem[i].type = calloc(20, sizeof(char));
        myElem[i].name = calloc(20, sizeof(char));
        myElem[i].parameters.elements = calloc(40, sizeof(char));
        myElem[i].parameters.pcData = calloc(20, sizeof(char));
    }
}

// retrieve content of dtd -> [ _our_content_ ]
void getElements() {
    int size_myElem = 0;
    int capacity = 10;
    element* myElem = calloc(capacity, sizeof(element));
    initMyElem(myElem, capacity);

    FILE* f = fopen("H:/Projects/ESGI/I-m-in-love-with-the-XML/dtd_files/myDtd.dtd", "r");

    for (int i = fgetc(f); i != EOF; i = fgetc(f)) {
        printf("%c", i);
        if (i == '[') {
            printf(" : %ld\n", ftell(f));
            getElements_2(ftell(f), &myElem, &size_myElem);
            break;
        }
    }
}

// retrieve content of dtd_element -> [ < _our_content_ /> ]
void getElements_2(int pos, element** myElem, int* size_myElem) {
    FILE* f = fopen("H:/Projects/ESGI/I-m-in-love-with-the-XML/dtd_files/myDtd.dtd", "r");
    fseek(f, pos, SEEK_SET);

    for (int i = fgetc(f); i != ']'; i = fgetc(f)) {
        if (i == '<') {
            printf("\n");
            printf(" size : %d | ", *size_myElem);
            getElements_3(ftell(f), myElem, size_myElem);
            *size_myElem += 1;
        }
    }
}

// stock our dtd_element to manipulate it
void getElements_3(int pos, element** myElem, int* size_myElem) {
    FILE* f = fopen("H:/Projects/ESGI/I-m-in-love-with-the-XML/dtd_files/myDtd.dtd", "r");
    fseek(f, pos, SEEK_SET);
    char* str = calloc(255, sizeof(char));

    int i = 0;
    for (int c = fgetc(f); c != '>'; c = fgetc(f), i += 1) {
        str[i] = c;
    }
    str[i] = '\0';

    getElements_4(str, myElem, size_myElem);
    free(str);
}

// manipulates our dtd_element -> separates the type/name/param
void getElements_4(char* str, element** myElem, int* size_myElem) {
    int i = 0;
    for (; i < strlen((str)); i += 1) {
        if (str[i] == '!') {
            getType(str, &i, myElem, size_myElem);

            if (str[i] == ' ') {
                i += 1;
                getName(str, &i, myElem, size_myElem);

                if (str[i] == '(') {
                    i += 1;
                    getParam(str, &i, myElem, size_myElem);
                }
            }
        }
    }
}

// stock the type into an element
void getType(char* str, int* pos, element** myElem, int* size_myElem) {
    printf("Type :");
    int i = *pos;
    for (int j = 0; str[i] != ' '; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[*size_myElem]->type[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[*size_myElem]->type);
}

// stock the name into an element
void getName(char* str, int* pos, element** myElem, int* size_myElem) {
    printf(" | Name :");
    int i = *pos;
    for (int j = 0; str[i] != '('; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[*size_myElem]->name[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[*size_myElem]->name);
}

// stock params into an element
void getParam(char* str, int* pos, element** myElem, int* size_myElem) {
    printf("| Param :");
    int i = *pos;
    for (int j = 0; str[i] != ')'; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[*size_myElem]->parameters.pcData[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[*size_myElem]->parameters.pcData);
}