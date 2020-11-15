#include "../h_files/launch_xml.h"
#include "../h_files/gtk_functions.h"
#include "../h_files/launch_dtd.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
//todo free actual malloc when returning an error (to not lose the opportunity)

int main(int argc, char **argv) {
#ifdef __unix__
    setenv("DISPLAY", "127.0.0.1:0", 1);
#endif
    //startWindow(argc,argv);
    launchXml("../resources/test.xml");
    launchDtd("../resources/myDtd.dtd");
    return EXIT_SUCCESS;
}