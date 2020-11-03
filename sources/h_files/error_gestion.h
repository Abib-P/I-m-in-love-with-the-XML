//
// Created by paula on 03/11/2020.
//

#ifndef I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H
#define I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H

typedef struct ERROR{
    char* where;
    char* error_value ;
} ERROR;

void showError(ERROR*);

ERROR* createError(char* );

#endif //I_M_IN_LOVE_WITH_THE_XML_ERROR_GESTION_H
