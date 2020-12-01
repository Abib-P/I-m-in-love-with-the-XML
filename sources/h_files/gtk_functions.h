
#ifndef I_M_IN_LOVE_WITH_THE_XML_GTK_FUNCTIONS_H
#define I_M_IN_LOVE_WITH_THE_XML_GTK_FUNCTIONS_H

#include <gtk/gtk.h>
#include "launch_xml.h"
#include "xml_validation.h"

typedef struct App{
    int exist;

    GtkWidget *mainWindow;
    GtkBuilder *builder;
    GtkWidget *openDTD;
    GtkWidget *openXML;
    GtkWidget *verifXML;
    GtkWidget *message;
    GtkWidget *verifXMLwithDTD;

    struct markupContainer * dtd;
    struct XML_tree *xml;
} App;

App application;

#include "read_dtd.h"
#include "launch_dtd.h"

void startWindow();

#endif //I_M_IN_LOVE_WITH_THE_XML_GTK_FUNCTIONS_H
