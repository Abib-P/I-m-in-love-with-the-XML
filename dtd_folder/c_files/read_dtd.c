//
// Created by hmeng on 04/11/2020.
//

#include "../h_files/read_dtd.h"

// todo
void initMyElem(element* myElem, int capacity) {
    for (int i = 0; i < capacity; i += 1) {
        myElem[i].type = calloc(20, sizeof(char));
        myElem[i].name = calloc(20, sizeof(char));
        myElem[i].parameters.elements_size = 0;
        myElem[i].parameters.elements_capacity = 10;
        myElem[i].parameters.elements = calloc(myElem[i].parameters.elements_capacity, sizeof(char));
        myElem[i].parameters.pcData = calloc(20, sizeof(char));
    }
}

// retrieve content of dtd -> [ _our_content_ ]
element* find_dtd_content(File_information* fileInfo, int* size) {
    int size_myElem = *size;
    int capacity = 10;
    element* result = calloc(capacity, sizeof(element));
    initMyElem(result, capacity);

    for (char c = getFirstCharacterAfterSpace(fileInfo); c != EOF; c = getNextCharacterInFile(fileInfo)) {
        if (c == '[') {
            find_dtd_elements(fileInfo, ftell(fileInfo->fp), result, &size_myElem);
            break;
        }
    }

    *size =size_myElem;
    return result;
}

// retrieve content of dtd_element -> [ < _our_content_ /> ]
void find_dtd_elements(File_information* fileInfo, int pos, element* myElem, int* size_myElem) {
    fseek(fileInfo->fp, pos, SEEK_SET);

    for (char c = getFirstCharacterAfterSpace(fileInfo); c != ']'; c = getNextCharacterInFile(fileInfo)) {
        if (c == '<') {
            find_dtd_element(fileInfo, ftell(fileInfo->fp), myElem, *size_myElem);
            *size_myElem += 1;
        }
    }
}

// stock our dtd_element to manipulate it
void find_dtd_element(File_information* fileInfo, int pos, element* myElem, int size_myElem) {
    fseek(fileInfo->fp, pos, SEEK_SET);
    char* str = calloc(255, sizeof(char));

    int i = 0;
    for (char c = getFirstCharacterAfterSpace(fileInfo); c != '>'; c = getNextCharacterInFile(fileInfo), i += 1) {
        str[i] = c;
    }
    str[i] = '\0';

    retrieve_dtd_info(str, myElem, size_myElem);
    free(str);
}

// manipulates our dtd_element -> separates the type/name/param
void retrieve_dtd_info(char* str, element* myElem, int size_myElem) {
    int i = 0;
    for (; i < strlen((str)); i += 1) {
        if (str[i] == '!') {
            get_dtd_type(str, &i, myElem, size_myElem);

            if (str[i] == ' ') {
                i += 1;
                get_dtd_name(str, &i, myElem, size_myElem);

                if (str[i] == '(') {
                    i += 1;
                    get_dtd_param(str, &i, myElem, size_myElem);
                }
            }
        }
    }
}

// stock the type into an element
void get_dtd_type(char* str, int* pos, element* myElem, int size_myElem) {
    int i = *pos;
    for (int j = 0; str[i] != ' '; j += 1, i += 1) {
        myElem[size_myElem].type[j] = str[i];
    }
    *pos = i;
}

// stock the name into an element
void get_dtd_name(char* str, int* pos, element* myElem, int size_myElem) {
    int i = *pos;
    for (int j = 0; str[i] != '('; j += 1, i += 1) {
        myElem[size_myElem].name[j] = str[i];
    }
    *pos = i;
}

// stock params into an element
void get_dtd_param(char* str, int* pos, element* myElem, int size_myElem) {
    int i = *pos;

    // parameter = #PCDATA
    if (str[*pos] == '#') {
        for (int j = 0; str[i] != ')'; j += 1, i += 1) {
            myElem[size_myElem].parameters.pcData[j] = str[i];
        }
    }
    // parameter(s) = child(s)
    else {
        strcpy(myElem[size_myElem].parameters.pcData, "\0");
        myElem[size_myElem].parameters.elements[myElem[size_myElem].parameters.elements_size] = malloc(sizeof(char) * 20);
        for (int j = 0; str[i] != ')'; j += 1, i += 1) {

            // another parameter
            if (str[i] == ',') {
                myElem[size_myElem].parameters.elements[myElem[size_myElem].parameters.elements_size][j] = '\0';
                j = 0;
                myElem[size_myElem].parameters.elements_size += 1;
                myElem[size_myElem].parameters.elements[myElem[size_myElem].parameters.elements_size] = malloc(sizeof(char) * 20);
            }
            // end of parameters
            else if (str[i+1] == ')') {
                myElem[size_myElem].parameters.elements[myElem[size_myElem].parameters.elements_size][j+1] = '\0';
            }

            // stock char
            if (str[i] == ',' || str[i] == ' ') {
                j -= 1;
            }
            else {
                myElem[size_myElem].parameters.elements[myElem[size_myElem].parameters.elements_size][j] = str[i];
            }
        }
    }

    *pos = i;
}