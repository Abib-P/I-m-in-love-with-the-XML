//
// Created by paula on 13/11/2020.
//

#include "../h_files/gtk_functions.h"
#include <gtk/gtk.h>

void startWindow(int argc, char **argv) {
    GtkWidget *fenetre_principale = NULL;
    GtkBuilder *builder = NULL;
    /* Initialisation de la librairie Gtk. */
    gtk_init(&argc, &argv);

    /* Ouverture du fichier Glade de la fenêtre principale
          Si le fichier n'existe pas ou n'est pas valide, cette fonction affichera une erreur
    et mettra fin au programme*/
    builder = gtk_builder_new_from_file("../resources/ui.glade");

    /* Récupération du pointeur de la fenêtre principale */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder, "MainWindow"));

    /* Affectation du signal "destroy" à la fonction gtk_main_quit(); pour la */
    /* fermeture de la fenêtre. */
    g_signal_connect (G_OBJECT (fenetre_principale), "destroy", (GCallback)gtk_main_quit, NULL);

    /* Affichage de la fenêtre principale. */
    gtk_widget_show_all (fenetre_principale);

    gtk_main();

    return 0;

}
