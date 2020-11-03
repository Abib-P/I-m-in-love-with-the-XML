//
// Created by paula on 03/11/2020.
//

#include "../h_files/error_gestion.h"
#include <stdio.h>

void showError(ERROR* err) {
    printf("%s: %s", err->where, err->error_value);
}
