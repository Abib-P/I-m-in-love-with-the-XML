cmake_minimum_required(VERSION 3.15)
project(I_m_in_love_with_the_XML C)

set(CMAKE_C_STANDARD 11)

add_executable(I_m_in_love_with_the_XML sources/c_files/main.c sources/c_files/read_xml.c sources/h_files/read_xml.h sources/c_files/read_dtd.c sources/h_files/read_dtd.h sources/c_files/file_useful.c sources/h_files/file_useful.h sources/c_files/error_gestion.c sources/h_files/error_gestion.h sources/c_files/file_information.c sources/h_files/file_information.h)