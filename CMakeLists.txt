cmake_minimum_required(VERSION 3.15)
project(I_m_in_love_with_the_XML C)

set(CMAKE_C_STANDARD 11)

# Set project path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})
add_definitions(${GTK_CFLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK_LIBRARIES})

# Compile
add_executable(I_m_in_love_with_the_XML sources/c_files/main.c sources/c_files/read_xml.c sources/h_files/read_xml.h sources/c_files/read_dtd.c sources/h_files/read_dtd.h sources/c_files/file_useful.c sources/h_files/file_useful.h sources/c_files/error_gestion.c sources/h_files/error_gestion.h sources/c_files/file_information.c sources/h_files/file_information.h sources/c_files/char_useful.c sources/h_files/char_useful.h sources/c_files/read_attribute.c sources/h_files/read_attribute.h sources/h_files/includes.h)