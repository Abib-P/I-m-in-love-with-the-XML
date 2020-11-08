#include <stdio.h>
#include <string.h>
#include "../h_files/read_dtd.h"


int main() {
    char* fileName = "H:\\Projects\\C\\I-m-in-love-with-the-XML\\dtd_folder\\dtd_files\\myDTD.dtd";
    File_information* dtdFileInfo = initialiseFileInformation(fileName);
    find_dtd_content(dtdFileInfo);
    return 0;

}