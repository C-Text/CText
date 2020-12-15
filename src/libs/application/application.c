#include "app.h"
#include "application.h"
#include "../image_manipulation/grayscale.h"
#include "../image_manipulation/otsu.h"
#include "../image_manipulation/bradley.h"

#define W_MAIN_ID     "org.ctext.main_window"
#define W_DIALG_ID    "org.ctext.file_chooser"
#define BTN_DIALG_OK  "org.ctext.file_chooser.btn_ok"
#define BTN_NEXT      "org.ctext.btn_next"
#define BTN_DEROUL    "org.ctext.btn_deroulant"
#define IMG_PREVIEWER "org.ctext.img_previewer"
#define LAYOUT_IMG    "org.ctext.layout_img"
#define S_BTN         "org.ctext.bradley.s"
#define T_BTN         "org.ctext.bradley.t"

gboolean resize_image(GtkWidget *widget, GdkRectangle *allocation,
                      app_widgets *widgets) {
  int x, w, h;
  GdkPixbuf *pxbscaled;
  GtkWidget *image = GTK_WIDGET(widgets->img_previewer);
  GdkPixbuf *pixbuf = widgets->pix_buf;

  if (allocation == NULL) {
    gtk_layout_move(GTK_LAYOUT(widget), image, 0, 0);
    pxbscaled = gdk_pixbuf_scale_simple(pixbuf, 539, 340, GDK_INTERP_BILINEAR);
    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
    return FALSE;
  }

  h = allocation->height;
  w = (gdk_pixbuf_get_width(pixbuf) * h) / gdk_pixbuf_get_height(pixbuf);

  pxbscaled = gdk_pixbuf_scale_simple(pixbuf, w, h, GDK_INTERP_BILINEAR);

  int max_w =allocation->width;
  if (w < max_w) {
    x = (max_w - w) / 2;
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
  gtk_grayscale(widgets->pix_buf);
  resize_image(GTK_WIDGET(widgets->layout_img), NULL, widgets);
  g_signal_connect(widgets->layout_img,
                   "size-allocate",
                   G_CALLBACK(resize_image),
                   widgets);
  gtk_widget_destroy(GTK_WIDGET(widgets->w_dlg_file_choose));
}

void on_next(__attribute__ ((unused))GtkButton *button,
             app_widgets *widgets) {

  gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn_next), FALSE);
  widgets->step += 1;
}

void on_choose_bin(__attribute__ ((unused))GtkComboBoxText *button,
                   app_widgets *widgets) {
  gtk_widget_set_sensitive(GTK_WIDGET(widgets->btn_next), TRUE);
  gchar *selected = gtk_combo_box_text_get_active_text(widgets->btn_deroul);
  if (selected[3] == 'u') {
    gtk_otsu_binarization(widgets->pix_buf);
  } else {
    //gtk_bradley(t, s, widgets->pix_buf);
    g_print("s: %u, t: %u\n",
            gtk_spin_button_get_value_as_int(widgets->btn_s),
            gtk_spin_button_get_value_as_int(widgets->btn_t));
  }

  resize_image(GTK_WIDGET(widgets->layout_img), NULL, widgets);
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
  widgets->btn_next = GTK_BUTTON(gtk_builder_get_object(builder, BTN_NEXT));
  widgets->btn_deroul = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,
                                                                  BTN_DEROUL));
  widgets->step = 0;
  widgets->img_previewer =
      GTK_IMAGE(gtk_builder_get_object(builder, IMG_PREVIEWER));
  widgets->btn_s = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, S_BTN));
  widgets->btn_t = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, T_BTN));

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
  g_signal_connect(widgets->btn_next,
                   "clicked",
                   G_CALLBACK(on_next),
                   widgets);
  g_signal_connect(widgets->btn_deroul,
                   "changed",
                   G_CALLBACK(on_choose_bin),
                   widgets);

  gtk_widget_show(widgets->w_main);

  gtk_main();

  g_free(widgets);

  return 0;
}