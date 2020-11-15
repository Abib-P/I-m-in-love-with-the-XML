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

# Pour linux, va servir à correctement liers les signaux de notre application au code (Merci Noé)
if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")
endif (UNIX)

# Compile
add_executable(I_m_in_love_with_the_XML sources/c_files/main.c sources/c_files/read_xml.c sources/h_files/read_xml.h sources/c_files/read_dtd.c sources/h_files/read_dtd.h sources/c_files/file_useful.c sources/h_files/file_useful.h sources/c_files/error_gestion.c sources/h_files/error_gestion.h sources/c_files/file_information.c sources/h_files/file_information.h sources/c_files/char_useful.c sources/h_files/char_useful.h sources/c_files/read_attribute.c sources/h_files/read_attribute.h sources/h_files/includes.h sources/c_files/launch_xml.c sources/h_files/launch_xml.h sources/c_files/gtk_functions.c sources/h_files/gtk_functions.h sources/c_files/xmlfile_read.c sources/h_files/xmlfile_read.h sources/c_files/read_comment.c sources/h_files/read_comment.h)
target_link_libraries(I_m_in_love_with_the_XML ${GTK_LIBRARIES})