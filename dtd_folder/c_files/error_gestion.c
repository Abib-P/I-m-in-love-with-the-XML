//
// Created by paula on 03/11/2020.
//

#include "../h_files/error_gestion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void showError(ERROR* err) {
    printf("Error in %s : %s", err->where, err->error_value);
}

ERROR *createError(char* where,char* error_value) {
    ERROR* result = malloc(sizeof(ERROR));
    result->where = malloc(strlen(where)*sizeof(char));
    strcpy(result->where,where);
    result->error_value = malloc(strlen(error_value)*sizeof(char));
    strcpy(result->error_value,error_value);
    return result;
}