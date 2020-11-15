cmake_minimum_required(VERSION 3.17)
project(I_m_in_love_with_the_XML C)

# Set project path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(I_m_in_love_with_the_XML
        sources/c_files/main.c
        sources/c_files/read_dtd.c
        sources/c_files/error_gestion.c
        sources/c_files/file_information.c
        sources/c_files/file_useful.c
        sources/h_files/includes.h
        sources/c_files/launch_dtd.c
        sources/h_files/launch_dtd.h)