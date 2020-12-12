#include "application.h"

#define W_MAIN_ID     "org.ctext.main_window"
#define W_DIALG_ID    "org.ctext.file_chooser"
#define BTN_DIALG_OK  "org.ctext.file_chooser.btn_ok"
#define IMG_PREVIEWER "org.ctext.img_previewer"
#define LAYOUT_IMG    "org.ctext.layout_img"

gboolean resize_image(GtkWidget *widget, GdkRectangle *allocation,
                      app_widgets *widgets) {
  int x, w, h;
  GdkPixbuf *pxbscaled;
  GtkWidget *image = GTK_WIDGET(widgets->img_previewer);
  GdkPixbuf *pixbuf = widgets->pix_buf;

  h = allocation->height;
  w = (gdk_pixbuf_get_width(pixbuf) * h) / gdk_pixbuf_get_height(pixbuf);

  pxbscaled = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);

  if (w < allocation->width) {
    x = (allocation->width - w) / 2;
    gtk_layout_move(GTK_LAYOUT(widget), image, x, 0);
  }

  gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
  g_object_unref(pxbscaled);
  return FALSE;
}

void on_file_selected(__attribute__ ((unused))GtkButton *button,
                      app_widgets *widgets) {

  gchar *filename = gtk_file_chooser_get_filename(widgets->w_dlg_file_choose);
  widgets->pix_buf = gdk_pixbuf_new_from_file(filename, NULL);
  gtk_image_set_from_pixbuf(widgets->img_previewer, widgets->pix_buf );
  gtk_widget_destroy(GTK_WIDGET(widgets->w_dlg_file_choose));
  g_signal_connect(widgets->layout_img,
                   "size-allocate",
                   G_CALLBACK(resize_image),
                   widgets);
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
  widgets->layout_img = GTK_LAYOUT(gtk_builder_get_object(builder, LAYOUT_IMG));
  widgets->w_dlg_file_choose =
      GTK_FILE_CHOOSER(gtk_builder_get_object(builder, W_DIALG_ID));
  widgets->btn_ok = GTK_BUTTON(gtk_builder_get_object(builder, BTN_DIALG_OK));
  widgets->btn_deroul = GTK_BUTTON(gtk_builder_get_object(builder, "org.ctext"
                                                          ".btn_deroulant"));
  widgets->img_previewer =
      GTK_IMAGE(gtk_builder_get_object(builder, IMG_PREVIEWER));

  // Connect signals
  gtk_builder_connect_signals(builder, widgets);

  g_object_unref(builder);

  g_signal_connect(widgets->w_main,
                   "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(widgets->btn_ok,
                   "clicked",
                   G_CALLBACK(on_file_selected),
                   widgets);

  gtk_widget_show(widgets->w_main);

  gtk_main();

  g_free(widgets);

  return 0;
}