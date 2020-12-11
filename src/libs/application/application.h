#ifndef CTEXT_APPLICATION_H_
#define CTEXT_APPLICATION_H_

#include <gtk/gtk.h>

typedef struct {
  GtkWidget *w_main;                      // Pointer to text view object
  GtkFileChooser *w_dlg_file_choose;      // Pointer to file chooser dialog box
  GtkButton *btn_ok;                      // Ok buton in file chooser
  GtkImage *img_previewer;                // Image previewer on the main window
} app_widgets;

int launch_application(int argc, char **argv);

#endif //CTEXT_APPLICATION_H_
