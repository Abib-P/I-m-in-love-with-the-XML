
#include "../h_files/gtk_functions.h"

void startWindow(int argc, char **argv) {
    /* Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale
          Si le fichier n'existe pas ou n'est pas valide, cette fonction affichera une erreur
    et mettra fin au programme*/
    application.builder = gtk_builder_new_from_file("../resources/ui.glade");

    /* Récupération du pointeur de la fenêtre principale */
    application.mainWindow = GTK_WIDGET(gtk_builder_get_object (application.builder, "MainWindow"));

    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (application.mainWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    application.openDTD = GTK_WIDGET(gtk_builder_get_object(application.builder,"openDTD"));
    application.openXML = GTK_WIDGET(gtk_builder_get_object(application.builder,"openXML"));
    application.verifXML = GTK_WIDGET(gtk_builder_get_object(application.builder,"verifXML"));
    application.message = GTK_WIDGET(gtk_builder_get_object(application.builder,"message"));
    application.verifXMLwithDTD = GTK_WIDGET(gtk_builder_get_object(application.builder,"verifXMLwithDTD"));

    gtk_builder_connect_signals(application.builder,NULL);

    application.exist = 1;
    application.dtd = NULL;
    application.xml = NULL;
    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (application.mainWindow);

    gtk_main();

}

void on_openDTD_activate(GtkImageMenuItem *b){

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open DTD File",
                                          GTK_WINDOW(application.mainWindow),
                                          action,
                                          ("_Cancel"),
                                          GTK_RESPONSE_CANCEL,
                                          ("_Open"),
                                          GTK_RESPONSE_ACCEPT,
                                          NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        application.dtd = launchDtd(filename);
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        if(application.dtd != NULL)
        {
            gtk_text_buffer_insert(buffer, &iter, "DTD Valid\n", -1);
        }
        else{
            gtk_text_buffer_insert(buffer, &iter, "DTD not Valid\n", -1);
        }
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

void on_openXML_activate(GtkImageMenuItem *b){

    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open XML File",
                                          GTK_WINDOW(application.mainWindow),
                                          action,
                                          ("_Cancel"),
                                          GTK_RESPONSE_CANCEL,
                                          ("_Open"),
                                          GTK_RESPONSE_ACCEPT,
                                          NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        if(application.xml != NULL)
        {
            freeXml_tree(application.xml);
        }
        application.xml = launchXml(filename);
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        if(application.xml != NULL)
        {
            gtk_text_buffer_insert(buffer, &iter, "XML Valid\n", -1);
        }
        else{
            gtk_text_buffer_insert(buffer, &iter, "XML not Valid\n", -1);
        }
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

void on_VerifXML_activate(GtkImageMenuItem *b){

}

void on_verifXMLwithDTD_activate(GtkImageMenuItem *b){
    if(application.xml == NULL){
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_buffer_insert(buffer, &iter, "You must open a XML file first\n", -1);
    } else if (application.dtd == NULL){
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_buffer_insert(buffer, &iter, "You must open a DTD file first\n", -1);
    } else if (xmlValidation(application.xml, application.dtd)){
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_buffer_insert(buffer, &iter, "!!! XML VALID WITH DTD !!!\n", -1);
    } else {
        GtkTextBuffer *buffer;
        GtkTextIter iter;
        buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(application.message));
        gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
        gtk_text_buffer_insert(buffer, &iter, "XML not valid with dtd\n", -1);
    }
}