#include "../h_files/launch_xml.h"
#include "../h_files/gtk_functions.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1 //todo treat \r \n \t as invisible character of getCharacterAfterSpace
//todo fix the column of file_information for the error
//todo treat the comment for the xml file
//todo treat the instruction markup (<?xml-stylesheet ... ?>)
//todo free actual malloc when returning an error (to not lose the opportunity)
//todo the function that free file_information (and close the document)

int main(int argc, char **argv) {
    startWindow(argc,argv);
    launchXml("../resources/test.xml");
}
