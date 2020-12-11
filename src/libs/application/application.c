#include "application.h"

#define W_MAIN_ID     "org.ctext.main_window"
#define W_DIALG_ID    "org.ctext.file_chooser"
#define BTN_DIALG_OK  "org.ctext.file_chooser.btn_ok"
#define IMG_PREVIEWER "org.ctext.img_previewer"

void on_file_selected(__attribute__ ((unused))GtkButton *button,
                      app_widgets* widgets) {
  gtk_image_set_from_file(widgets->img_previewer,
                          gtk_file_chooser_get_filename(widgets->w_dlg_file_choose));
  gtk_widget_destroy (GTK_WIDGET(widgets->w_dlg_file_choose));
}

int launch_application(int argc, char **argv) {
  GtkBuilder *builder;
  GError *error = NULL;
  app_widgets *widgets = g_slice_new(app_widgets);

  // Init gtk
  gtk_init(&argc, &argv);

  builder = gtk_builder_new();
  if (gtk_builder_add_from_file(builder, "src/assets/interface.glade", &error)
      == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  /* Connect signal handlers to the constructed widgets. */
  widgets->w_main = GTK_WIDGET(gtk_builder_get_object(builder, W_MAIN_ID));
  widgets->w_dlg_file_choose =
      GTK_WIDGET(gtk_builder_get_object(builder, W_DIALG_ID));
  widgets->btn_ok = GTK_BUTTON(gtk_builder_get_object(builder, BTN_DIALG_OK));
  widgets->img_previewer = GTK_IMAGE(gtk_builder_get_object(builder, IMG_PREVIEWER));

  // Connect signals
  gtk_builder_connect_signals(builder, widgets);

  g_object_unref(builder);

  g_signal_connect(widgets->w_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(widgets->btn_ok,
                   "clicked",
                   G_CALLBACK(on_file_selected),
                   widgets);
  gtk_widget_show(widgets->w_main);

  gtk_main();

  return 0;
}