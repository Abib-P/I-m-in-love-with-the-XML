#include <stdio.h>
#include <string.h>
#include "../h_files/read_dtd.h"


int main() {
    displayFile();

    char** myStr_Array = arrayElements();
    char* test = "c'est un test";
    printf("%s", test);

    return EXIT_SUCCESS;
}