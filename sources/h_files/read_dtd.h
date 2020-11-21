//
// Created by hmeng on 04/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
#define I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H

#include "file_information.h"
#include "file_useful.h"

/* myDTD ########################################################## */
typedef struct attribute
{
    char* attribute_name;
    char* attribute_type;
    char* attribute_value;
} attribute;

typedef struct element
{
    char** elements;
    unsigned int elements_size;
    unsigned int elements_capacity;
} element;

typedef struct parameter
{
    char* parameter_type;

    char* category;  // corresponding to a #PCDATA
    element element;  // relative to !ELEMENT
    attribute attribute;  // relative to !ATTLIST
} parameter;

typedef struct markup
{
    char* markup_type;  // !DOCTYPE (root, parent), !ELEMENT (child), !ATTLIST (attribute)
    char* markup_name;
    parameter markup_parameters;
} markup;

typedef struct markupContainer {
    markup* markupArray;
    unsigned int size;
    unsigned int capacity;
} markupContainer;


/* PROTOTYPES ########################################################## */

markupContainer* find_dtd_content(File_information*);

void find_dtd_markups(File_information*, markupContainer*);

void find_dtd_markup(File_information*, markupContainer*);

void retrieve_dtd_info(char*, markupContainer*);

void get_dtd_type(char* str, int* i, markupContainer*);

void get_dtd_name(char* str, int* i, markupContainer*);

void find_typeOf_param(char* str, int* i, markupContainer*);

void get_dtd_param_category(char* str, int* pos, markupContainer* markupArray);

void get_dtd_param_element(char* str, int* pos, markupContainer* markupArray);

void get_dtd_param_attribute(char* str, int* pos, markupContainer* markupArray);

void getNextCharAfterSpace(char* str, int* pos) ;

#endif //I_M_IN_LOVE_WITH_THE_XML_READ_DTD_H
