#ifndef CTEXT_APPLICATION_H_
#define CTEXT_APPLICATION_H_

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *w_main;                  // Pointer to text view object
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
} app_widgets;

int launch_application(int argc, char **argv);

#endif //CTEXT_APPLICATION_H_
