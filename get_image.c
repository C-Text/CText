#include <gtk/gtk.h>
#include <glib/gi18n.h>

typedef struct Ui
{
		GtkWidget* window;
		GtkWidget* open_image;
		GtkWidget* box_image;
		GtkWidget* button;
		GtkWidget* button_box;
		GtkWidget* image;

}Ui;
Ui ui;

static void on_open_image (GtkButton* button_image, gpointer user_data)
{
	ui.image = GTK_WIDGET (user_data);
	GtkWidget *toplevel = gtk_widget_get_toplevel (ui.image);
	GtkFileFilter *filter = gtk_file_filter_new ();
	GtkWidget *dialog = gtk_file_chooser_dialog_new (_("Open image"),
	                                                 GTK_WINDOW (toplevel),
	                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
	                                                 GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
	                                                 GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                                 NULL);

	gtk_file_filter_add_pixbuf_formats (filter);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (dialog),
	                             filter);

	switch (gtk_dialog_run (GTK_DIALOG (dialog)))
	{
		case GTK_RESPONSE_ACCEPT:
		{
			gchar *filename =
				gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
			gtk_image_set_from_file (GTK_IMAGE (ui.image), filename);
			break;
		}
		default:
			break;
	}
	gtk_widget_destroy (dialog);
}

static GtkWidget* create_window (void)
{

	/* Set up the UI */
	ui.window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (ui.window), "CText");

	/*Make a button */
	ui.box_image = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	ui.open_image = gtk_button_new_with_label (_("Open image"));
	ui.image = gtk_image_new ();

	gtk_box_pack_start (GTK_BOX (ui.box_image), ui.image, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (ui.box_image), ui.open_image, FALSE,
	FALSE, 0);

	gtk_container_add (GTK_CONTAINER (ui.window), ui.box_image);

	return ui.window;
}

int main (int argc, char *argv[])
{

#ifdef ENABLE_NLS

	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	gtk_init (&argc, &argv);

	ui.window = create_window ();

	/* Connect signals */

	/*Show open dialog when opening a file */
	g_signal_connect (ui.open_image, "clicked", G_CALLBACK (on_open_image),
	ui.image);

	/* Exit when the window is closed */
	g_signal_connect (ui.window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	gtk_widget_show_all(ui.window);

	gtk_main ();

	return 0;
}

