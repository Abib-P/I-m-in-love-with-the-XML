//
// Created by paula on 03/11/2020.
//

#include "../h_files/error_gestion.h"

void showError(ERROR* err) {
    printf("Error in %s : %s", err->where, err->error_value);
    if(application.exist){
        char finalMessage[1000];
        sprintf(finalMessage,"Error in %s : %s", err->where, err->error_value);
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_buffer_insert(buffer, &iter, finalMessage, -1);
    }
}

ERROR *createError(char* where,char* error_value) {
    ERROR* result = malloc(sizeof(ERROR));
    result->where = malloc(strlen(where)*sizeof(char));
    strcpy(result->where,where);
    result->error_value = malloc(strlen(error_value)*sizeof(char));
    strcpy(result->error_value,error_value);
    return result;
}