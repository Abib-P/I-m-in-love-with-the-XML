#include <stdio.h>
#include <string.h>
#include "../h_files/read_dtd.h"


int main() {

    displayFile();

    char* test = "\nc'est un test";

    char** myStr_Array = arrayElements();
    getInfo(myStr_Array[0]);

    return EXIT_SUCCESS;
}