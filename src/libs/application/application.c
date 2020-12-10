#include "application.h"

#define IDENTIFIER "com.ctext.ctext"
#define TITLE       "CText"
#define HEIGHT      200
#define WIDTH       200

static void launch_file_chooser(GtkWindow *parent_window) {
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;

  dialog = gtk_file_chooser_dialog_new("Open File",
                                       parent_window,
                                       action,
                                       "Cancel",
                                       GTK_RESPONSE_CANCEL,
                                       "Open",
                                       GTK_RESPONSE_ACCEPT,
                                       NULL);

  res = gtk_dialog_run(GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT) {
    char *filename;
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    filename = gtk_file_chooser_get_filename(chooser);
    g_print("%s", filename);
    g_free(filename);
  }

  gtk_widget_destroy(dialog);
}

static void activate(GtkApplication *app,
                     __attribute__ ((unused)) gpointer user_data) {
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW (window), TITLE);
  gtk_window_set_default_size(GTK_WINDOW (window), WIDTH, HEIGHT);
  gtk_widget_show_all(window);
  launch_file_chooser(GTK_WINDOW (window));
}

int launch_application(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new(IDENTIFIER, G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}