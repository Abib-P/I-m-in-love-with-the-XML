//
// Created by hmeng on 04/11/2020.
//

#include "../h_files/read_dtd.h"

// init file
FILE* initFile() {
    char* path = "H:/Projects/ESGI/I-m-in-love-with-the-XML/dtd_files/myDtd.dtd";
    FILE* f = fopen(path, "r");
    return f;
}

// display file
void displayFile() {
    FILE* f = initFile();
    char c = fgetc(f);
    printf("\ndisplayFile: \n");
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(f);
    }
    printf("\n");
}

// retrieve content of <tag = element>
char** arrayElements() {
    int size_res = 0;
    int capacity = 10;
    char** res = malloc(sizeof(char) * capacity);

    printf("\narrayElements:");

    FILE* f = initFile();
    char c = fgetc(f);
    // read file
    while (c != EOF)
    {
        // '[' <our_elements> ']'
        if (c == '[')
        {
            c = fgetc(f);
            while (c != ']')
            {
                // '<' our_element '>'
                if (c == '<')
                {
                    c = fgetc(f);
                    char str[255] = "";
                    int i = 0;
                    for (; c != '>'; i++)
                    {
                        str[i] = c;
                        c = fgetc(f);
                    }
                    str[i] = '\0';
                    size_res += 1;
                    strcpy(res[size_res-1], str);
                    printf("\n%s", res[size_res-1]);
                }

                c = fgetc(f);
            }
        }

        c = fgetc(f);
    }

    return res;
}

// TODO
//void cut (char* str) {
//    for (int i = 0; str[i] != '\0'; ++i) {
//        // type
//        if (str[i] == '!') {
//            printf("\ntype : ");
//            while (str[i] != ' ') {
//                printf("%s", str[i]);
//            }
//        }
//    }
//}


// TODO
void getInfo(char* str) {
    printf("\ngetInfo:\n");
    printf("%s", str);
}