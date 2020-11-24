#include "../h_files/gtk_functions.h"
#include "../h_files/test.h"
#include "../h_files/launch_verification.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
//todo free actual malloc when returning an error (to not lose the opportunity)
//todo pop error when reach end of file in a comment
//todo railway programing doc


int main(int argc, char **argv) {
#ifdef __unix__
    setenv("DISPLAY", "127.0.0.1:0", 1);
#endif
    if (argc == 2)
    {
        if (strcmp(argv[1],"test") == 0){
            startTest();
        }
        if (strcmp(argv[1],"printTest") == 0){
            startTestWithTerminal();
        }
    }
    else if (argc == 3)
    {
        if (launchVerification(argv[1],argv[2])){
            printf("XML Valid\n");
        }
        else {
            printf("XML not valid\n");
        }
    }
    else{
        startWindow(argc,argv);
    }
    return EXIT_SUCCESS;
}