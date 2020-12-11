#include "application.h"

#define W_MAIN_ID "org.ctext.main_window"
#define W_DIALG_ID "org.ctext.file_chooser"

G_MODULE_EXPORT void __attribute__ ((unused))on_button1_clicked(__attribute__ ((unused))GtkButton *button, __attribute__ ((unused))gpointer user_data) {
    g_print("Check point 1\n");
}

G_MODULE_EXPORT void __attribute__ ((unused))on_button2_clicked(__attribute__ ((unused))GtkButton *button, __attribute__ ((unused))gpointer user_data) {
    g_print("Check point 2\n"); //to help debugging
}

int launch_application(int argc, char **argv) {
    GtkBuilder *builder;
    GError *error = NULL;
    app_widgets *widgets = g_slice_new(app_widgets);

    // Init gtk
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "src/assets/interface.glade", &error) == 0) {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    /* Connect signal handlers to the constructed widgets. */
    widgets->w_main = GTK_WIDGET(gtk_builder_get_object(builder, W_MAIN_ID));
    widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, W_DIALG_ID));

    // Connect signals
    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    g_signal_connect(widgets->w_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show(widgets->w_main);

    gtk_main();


    return 0;
}