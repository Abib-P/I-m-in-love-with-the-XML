
#ifndef I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H
#define I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H

#include "includes.h"
#include "gtk_functions.h"

typedef struct ERROR{
    char* where;
    char* error_value;
} ERROR;

void showError(ERROR* error);

ERROR* createError(char* where, char* error_value);

#endif //I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H