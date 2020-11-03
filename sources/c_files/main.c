#include <stdio.h>
#include <string.h>
#include "../h_files/file_information.h" //TODO update the #include section

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main() {
    char * fileName = "test.xml";
    File_information* fileInfo = initialiseFileInformation(fileName);

    if(fileInfo != NULL) //no error during opening file
    {
        char actualCharacter = (char)fgetc(fileInfo->fp);
        while(actualCharacter != EOF)
        {
            printf("%c",actualCharacter);
            actualCharacter = (char)fgetc(fileInfo->fp);
        }
    } else{
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
