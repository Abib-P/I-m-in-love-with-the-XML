//
// Created by hmeng on 04/11/2020.
//

#include "../h_files/read_dtd.h"

void initMyElem(element* myElem, int capacity) {
    for (int i = 0; i < capacity; i += 1) {
        myElem[i].type = calloc(20, sizeof(char));
        myElem[i].name = calloc(20, sizeof(char));
        myElem[i].parameters.elements_size = 0;
        myElem[i].parameters.elements_capacity = 40;
        myElem[i].parameters.elements = calloc(myElem[i].parameters.elements_capacity, sizeof(char));
        myElem[i].parameters.pcData = calloc(20, sizeof(char));
    }
}

// retrieve content of dtd -> [ _our_content_ ]
void getElements(File_information* fileInfo) {
    int size_myElem = 0;
    int capacity = 10;
    element* myElem = calloc(capacity, sizeof(element));
    initMyElem(myElem, capacity);


    for (int i = fgetc(fileInfo->fp); i != EOF; i = fgetc(fileInfo->fp)) {
        printf("%c", i);
        if (i == '[') {
            printf(" : %ld\n", ftell(fileInfo->fp));
            getElements_2(fileInfo, ftell(fileInfo->fp), myElem, &size_myElem);
            break;
        }
    }
}

// retrieve content of dtd_element -> [ < _our_content_ /> ]
void getElements_2(File_information* fileInfo, int pos, element* myElem, int* size_myElem) {
    fseek(fileInfo->fp, pos, SEEK_SET);

    for (int i = fgetc(fileInfo->fp); i != ']'; i = fgetc(fileInfo->fp)) {
        if (i == '<') {
            printf("\n");
            printf(" size : %d | ", *size_myElem);
            getElements_3(fileInfo, ftell(fileInfo->fp), myElem, *size_myElem);
            *size_myElem += 1;
        }
    }
}

// stock our dtd_element to manipulate it
void getElements_3(File_information* fileInfo, int pos, element* myElem, int size_myElem) {
    fseek(fileInfo->fp, pos, SEEK_SET);
    char* str = calloc(255, sizeof(char));

    int i = 0;
    for (char c = fgetc(fileInfo->fp); c != '>'; c = fgetc(fileInfo->fp), i += 1) {
        str[i] = c;
    }
    str[i] = '\0';

    getElements_4(str, myElem, size_myElem);
    free(str);
}

// manipulates our dtd_element -> separates the type/name/param
void getElements_4(char* str, element* myElem, int size_myElem) {
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
void getType(char* str, int* pos, element* myElem, int size_myElem) {
    printf("Type :");
    int i = *pos;
    for (int j = 0; str[i] != ' '; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[size_myElem].type[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[size_myElem].type);
}

// stock the name into an element
void getName(char* str, int* pos, element* myElem, int size_myElem) {
    printf(" | Name :");
    int i = *pos;
    for (int j = 0; str[i] != '('; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[size_myElem].name[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[size_myElem].name);
}



// stock params into an element
void getParam(char* str, int* pos, element* myElem, int size_myElem) {
    printf("| Param :");
    int i = *pos;
    for (int j = 0; str[i] != ')'; j += 1, i += 1) {
//        printf("%c", str[i]);
        myElem[size_myElem].parameters.pcData[j] = str[i];
    }
    *pos = i;
    printf("%s", myElem[size_myElem].parameters.pcData);
}