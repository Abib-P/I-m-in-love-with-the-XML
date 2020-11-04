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
    printf("\n");
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
    char** res = malloc(sizeof(char) * size_res);

    FILE* f = initFile();
    char c = fgetc(f);
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
//                    printf("\n%s", res[size_res-1]);
                }

                c = fgetc(f);
            }
        }

        c = fgetc(f);
    }

    return res;
}

// TODO
void getInfo(char* str) {
    printf("%s", str);
}