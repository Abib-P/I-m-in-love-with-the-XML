#include <stdio.h>
#include <string.h>
#include "../h_files/read_dtd.h"


int main() {
    char* fileName = "H:\\Projects\\C\\I-m-in-love-with-the-XML\\dtd_folder\\dtd_files\\myDTD.dtd";
    File_information* dtdFileInfo = initialiseFileInformation(fileName);
    int size_elementList = 0;
    element* elementList = find_dtd_content(dtdFileInfo, &size_elementList);

    printf("\nDisplay elementList :\n");
    for (int i = 0; i < size_elementList; i += 1) {
        printf("\n index : %d ", i);
        printf("| type : %s ", elementList[i].type);
        printf("| name : %s ", elementList[i].name);

        // #PCDATA not exist, display element_child(s)
        if (strlen(elementList[i].parameters.pcData) == 0) {
            printf("| param(s) : ");
            for (int j = 0; j <= elementList[i].parameters.elements_size; j += 1) {
                printf("%s ", elementList[i].parameters.elements[j]);
            }
        }
        // // #PCDATA exist
        else {
            printf("| param : ");
            printf("%s ", elementList[i].parameters.pcData);
        }
    }
    return 0;
}