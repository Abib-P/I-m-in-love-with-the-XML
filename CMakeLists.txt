cmake_minimum_required(VERSION 3.17)
project(ESGI C)

set(CMAKE_C_STANDARD 99)

add_executable(I-m-in-love-with-the-XML
        dtd_folder/c_files/main.c
        dtd_folder/c_files/read_dtd.c
        dtd_folder/c_files/error_gestion.c
        dtd_folder/c_files/file_information.c
        dtd_folder/c_files/file_useful.c
        dtd_folder/dtd_files/myDTD.dtd
    )