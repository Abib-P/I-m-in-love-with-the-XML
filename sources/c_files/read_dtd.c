//
// Created by hmeng on 04/11/2020.
//

#include "../h_files/read_dtd.h"

/**
 * This method allow to create an array containing all information about a DTD
 * the different markups :
 *     - type (!DOCTYPE, !ELEMENT, !ATTLIST)
 *     - name
 *     - parameters (category, attribute, element)
 * @param fileInfo
 * @return markupContainer*
 */
markupContainer* find_dtd_content(File_information* fileInfo) {

    // init, malloc
    markupContainer* result = malloc(sizeof(markupContainer));
    result->size = 0;
    result->capacity = 10;
    result->markupArray = malloc(sizeof(markup) * result->capacity);
    char c;

    // chars expected at the beginning of DTD : '<'
    if ((c = getFirstCharacterAfterSpace(fileInfo)) == '<') {
        // separator '!' => markup_type
        if ((c = getNextCharacterInFile(fileInfo)) == '!') {

            // GET the !DOCTYPE markup of DTD
            // RETRIEVE markup_type
            result->markupArray[result->size].markup_type = malloc(sizeof(char) * 20);
            int i = 0;
            // read up to the markup_name indicate by the separator ' '
            for (; c != ' '; c = getNextCharacterInFile(fileInfo), i += 1) {
                result->markupArray[result->size].markup_type[i] = c;
            }
            result->markupArray[result->size].markup_type[i] = '\0';

            // RETRIEVE the markup_name
            result->markupArray[result->size].markup_name = malloc(sizeof(char) * 20);
            int j = 0;
            // read up to the separator '[' => body of the DTD
            c = getFirstCharacterAfterSpace(fileInfo);
            for (; c != '['; j += 1) {
                result->markupArray[result->size].markup_name[j] = c;
                c = getNextCharacterInFile(fileInfo);
            }
            result->markupArray[result->size].markup_name[j] = '\0';

            result->markupArray[result->size].markup_parameters.parameter_type = NULL;
            // next markup
            result->size += 1;

            // GET the other markups of DTD
            if (c == '[') {
                find_dtd_markups(fileInfo, result);
            }
        }
    }

    return result;
}

/**
 * This method allow to read the body of DTD, and to find each markup
 * '[' : start of DTD_body
 * ']' : end of DTD_body
 * @param fileInfo
 * @param markupArray
 */
void find_dtd_markups(File_information* fileInfo, markupContainer* container) {
    // read the file up to the END OF DTD => ']'
    for (char c = getNextCharacterInFile(fileInfo); c != ']'; c = getNextCharacterInFile(fileInfo)) {
        // foreach markups do that ...
        if (c == '<') {
            find_dtd_markup(fileInfo, container);
            container->size += 1;  // next markup

            if (container->size >= container->capacity) {
                container->capacity *= 2;
                container->markupArray = realloc(container->markupArray, sizeof(markup) * container->capacity);
            }
        }
    }
}

/**
 * This method allow to return a string containing a markup content
 * '<' : start of markup
 * '>' : end of markup
 * @param fileInfo
 * @param pos
 * @param markupArray
 */
void find_dtd_markup(File_information* fileInfo, markupContainer* container) {
    char* str = malloc(sizeof(char) * 255);
    int i = 0;
    for (char c = getNextCharacterInFile(fileInfo); c != '>'; c = getNextCharacterInFile(fileInfo), i += 1) {
        str[i] = c;
    }
    str[i] = '\0';
    retrieve_dtd_info(str, container);
    free(str);
}

/**
 * This method allow to retrieve the type, name, param of markup
 * @param fileInfo
 * @param str
 * @param markupArray
 */
void retrieve_dtd_info(char* str, markupContainer* container) {
    // read str (markup_content)
    for (int i = 0; i < strlen(str); i += 1) {

        // finds indicator of a markup_type
        if (str[i] == '!') {
            // RETRIEVE the markup_type
            get_dtd_type(str, &i, container);

            // RETRIEVE the markup_name
            i += 1;
            get_dtd_name(str, &i, container);

            // markup_type == !ELEMENT
            if (strcmp(container->markupArray[container->size].markup_type, "!ELEMENT") == 0) {
                if (str[i] == '(') {
                    i += 1;
                    find_typeOf_param(str, &i, container);
                }
            }  // markup_type == !ATTLIST
            else if (strcmp(container->markupArray[container->size].markup_type, "!ATTLIST") == 0) {
                get_dtd_param_attribute(str, &i, container);
            }
            else if (strcmp(container->markupArray[container->size].markup_type, "!ENTITY") == 0) {
                get_dtd_param_entity(str, &i, container);
            }
            break;
        }
    }
}

/**
 * This method allow to retrieve the type of markup
 * @param str
 * @param pos
 * @param container
 */
void get_dtd_type(char* str, int* pos, markupContainer* container) {
    // init, malloc
    container->markupArray[container->size].markup_type = malloc(sizeof(char) * 20);

    // RETRIEVE markup_type
    for (int i = 0; str[*pos] != ' '; i += 1, *pos += 1) {
        container->markupArray[container->size].markup_type[i] = str[*pos];
        if (str[*pos+1] == ' ') {
            container->markupArray[container->size].markup_type[i+1] = '\0';
        }
    }
}

/**
 * This method allow to retrieve the name of markup
 * @param str
 * @param pos
 * @param container
 */
void get_dtd_name(char* str, int* pos, markupContainer* container) {
    // init, malloc
    container->markupArray[container->size].markup_name = malloc(sizeof(char) * 20);

    // markup_type == !ELEMENT
    if (strcmp(container->markupArray[container->size].markup_type, "!ELEMENT") == 0) {
        // read until '(' + RETRIEVE markup_name
        for (int j = 0; str[*pos] != '('; j += 1, *pos += 1) {
            if (str[*pos+1] == '(' || str[*pos] == ' ') {
                container->markupArray[container->size].markup_name[j] = '\0';
            }
            else {
                container->markupArray[container->size].markup_name[j] = str[*pos];
            }
        }
        removeFinalSpacesOfString(container->markupArray[container->size].markup_name);
    }
    else {  // markup_type == !ATTLIST
        // read until ' ' + RETRIEVE markup_name
        for (int j = 0; str[*pos] != ' '; j += 1, *pos += 1) {
            container->markupArray[container->size].markup_name[j] = str[*pos];
            if (str[*pos+1] == ' ') {
                container->markupArray[container->size].markup_name[j+1] = '\0';
            }
        }
        *pos += 1;
    }
}

/**
 * This method allow to determinate if markup_parameters is a category or element
 * @param str
 * @param pos
 * @param container
 */
void find_typeOf_param(char* str, int* pos, markupContainer* container) {
    // parameter = #PCDATA
    if (str[*pos] == '#') {
        get_dtd_param_category(str, pos, container);
    }
    // parameter(s) = child(s)
    else {
        get_dtd_param_element(str, pos, container);
    }
}

/**
 * This method allow to retrieve the category value (context: parameter)
 * @param str
 * @param pos
 * @param container
 */
void get_dtd_param_category(char* str, int* pos, markupContainer* container) {
    // init, malloc
    container->markupArray[container->size].markup_parameters.category = malloc(sizeof(char) * 20);
    // SET parameter_type at "category"
    container->markupArray[container->size].markup_parameters.parameter_type = malloc(sizeof(char) * 10);
    strcpy(container->markupArray[container->size].markup_parameters.parameter_type, "category");

    for (int i = 0; str[*pos] != ')'; i += 1, *pos += 1) {
        container->markupArray[container->size].markup_parameters.category[i] = str[*pos];
        if (str[*pos+1] == ')') {
            container->markupArray[container->size].markup_parameters.category[i+1] = '\0';
        }
    }
}

/**
 * This method allow to retrieve the element data (context: parameter)
 * @param str
 * @param pos
 * @param container
 */
void get_dtd_param_element(char* str, int* pos, markupContainer* container) {
    // init, malloc
    container->markupArray[container->size].markup_parameters.element.elements_size = 0;
    container->markupArray[container->size].markup_parameters.element.elements_capacity = 10;
    container->markupArray[container->size].markup_parameters.element.elements = malloc(sizeof(char*) * container->markupArray[container->size].markup_parameters.element.elements_capacity);
    container->markupArray[container->size].markup_parameters.element.elements[container->markupArray[container->size].markup_parameters.element.elements_size] = malloc(sizeof(char) * 20);
    // SET parameter_type at "element"
    container->markupArray[container->size].markup_parameters.parameter_type = malloc(sizeof(char) * 10);
    strcpy(container->markupArray[container->size].markup_parameters.parameter_type, "element");

    for (int j = 0; str[*pos] != ')'; j += 1, *pos += 1) {

        // find an other parameter, indicate by ','
        if (str[*pos] == ',') {
            // init, malloc once again to prepare a new instance
            container->markupArray[container->size].markup_parameters.element.elements[container->markupArray[container->size].markup_parameters.element.elements_size][j] = '\0';
            j = 0;
            container->markupArray[container->size].markup_parameters.element.elements_size += 1;
            container->markupArray[container->size].markup_parameters.element.elements[container->markupArray[container->size].markup_parameters.element.elements_size] = malloc(sizeof(char) * 20);
        }
        else if (str[*pos+1] == ')') {  // end of markup_parameters
            container->markupArray[container->size].markup_parameters.element.elements[container->markupArray[container->size].markup_parameters.element.elements_size][j+1] = '\0';
        }

        // doesn't want to stock separators
        if (str[*pos] == ',' || str[*pos] == ' ') {
            j -= 1;
        }
        else {
            container->markupArray[container->size].markup_parameters.element.elements[container->markupArray[container->size].markup_parameters.element.elements_size][j] = str[*pos];
        }
    }
}

/**
 * THis method allow to retrieve the attribute data (context: parameter)
 * @param str
 * @param pos
 * @param container
 */
void get_dtd_param_attribute(char* str, int* pos, markupContainer* container) {
    // évite la casse s'il y a un espace perdu à la fin
    removeFinalSpacesOfString(str);

    // init, malloc
    container->markupArray[container->size].markup_parameters.attribute.attribute_name = malloc(sizeof(char) * 40);
    container->markupArray[container->size].markup_parameters.attribute.attribute_type = malloc(sizeof(char) * 40);
    container->markupArray[container->size].markup_parameters.attribute.attribute_value = malloc(sizeof(char) * 40);
    // SET parameter_type at "attribute"
    container->markupArray[container->size].markup_parameters.parameter_type = malloc(sizeof(char) * 20);
    strcpy(container->markupArray[container->size].markup_parameters.parameter_type, "attribute");

    getNextCharAfterSpace(str, pos);

    // RETRIEVE attribute_name
    for (int i = 0; str[*pos] != ' '; i += 1, *pos += 1) {
        container->markupArray[container->size].markup_parameters.attribute.attribute_name[i] = str[*pos];
        if (str[*pos+1] == ' ') {
            container->markupArray[container->size].markup_parameters.attribute.attribute_name[i+1] ='\0';
        }
    }

    getNextCharAfterSpace(str, pos);

    // RETRIEVE attribute_type
    for (int i = 0; str[*pos] != ' '; i += 1, *pos += 1) {
        container->markupArray[container->size].markup_parameters.attribute.attribute_type[i] = str[*pos];
        if (str[*pos+1] == ' ') {
            container->markupArray[container->size].markup_parameters.attribute.attribute_type[i+1] = '\0';
        }
    }

    getNextCharAfterSpace(str, pos);

    // RETRIEVE attribute_value
    for (int i = 0; str[*pos] != '\0'; i += 1, *pos += 1) {
        container->markupArray[container->size].markup_parameters.attribute.attribute_value[i] = str[*pos];

        int fixedExist = 0;

        // end of current word
        if (str[*pos+1] == '\0' || str[*pos+1] == ' ') {
            container->markupArray[container->size].markup_parameters.attribute.attribute_value[i+1] = '\0';
            removeFinalSpacesOfString(container->markupArray[container->size].markup_parameters.attribute.attribute_value);

            // #FIXED
            if (strcmp(container->markupArray[container->size].markup_parameters.attribute.attribute_value, "#FIXED") == 0)
                fixedExist = 1;
        }

        // USE CASE MANAGEMENT : #FIXED & multiple attributes
        if (fixedExist == 1) {
            printf("!! SUCCESS !!");
            container->markupArray[container->size].markup_parameters.attribute.attribute_value[i+1] = str[*pos+1];
            i += 1;
            *pos += 1;
        }
        else if (str[*pos] == ' ') {
            getNextCharAfterSpace(str, pos);
            if (str[*pos] != '\0') {

                container->size += 1;
                if (container->size >= container->capacity) {
                    container->capacity *= 2;
                    container->markupArray = realloc(container->markupArray, sizeof(markup) * container->capacity);
                }

                container->markupArray[container->size].markup_type = malloc(sizeof(char) * 20);
                strcpy(container->markupArray[container->size].markup_type, container->markupArray[container->size-1].markup_type);
                container->markupArray[container->size].markup_name = malloc(sizeof(char) * 20);
                strcpy(container->markupArray[container->size].markup_name, container->markupArray[container->size-1].markup_name);
                get_dtd_param_attribute(str, pos, container);
                break;
            }
        }
    }
}


void get_dtd_param_entity(char* str, int* pos, markupContainer* container) {
    // SET parameter_type at "attribute"
    container->markupArray[container->size].markup_parameters.parameter_type = malloc(sizeof(char) * 20);
    strcpy(container->markupArray[container->size].markup_parameters.parameter_type, "entity");
    container->markupArray[container->size].markup_parameters.entity = malloc(sizeof(char) * 40);

    for (int i = 0; str[*pos] != '\0'; i+=1, *pos+=1) {
        container->markupArray[container->size].markup_parameters.entity[i] = str[*pos];
        if (str[*pos+1] == '\0') {
            container->markupArray[container->size].markup_parameters.entity[i+1] ='\0';
        }
    }
}


// get the next character
void getNextCharAfterSpace(char* str, int* pos) {
    if (str[*pos] == ' ' || str[*pos] == '\n') {
        while (str[*pos] == ' ' || str[*pos] == '\n') {
            *pos += 1;
        }
    }
}