#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "grayscale.h"

typedef struct Ui
{
		GtkWidget* window;				//gui's window
		GtkButton* open_image;			//open image button
		GtkWidget* box_image;			//box of the open image's button
		GtkButton* grayscale_button;	//grayscale button
		GtkWidget* grayscale_box;		//grayscale button box
		GtkWidget* image;				//image to process
		GtkWidget* grayscale;			//grayscaled image
		GtkApplication* app;

}Ui;
Ui ui;

/*This is the callback function. It is a handler function which
reacts to the signal. In this case, it will cause the button label's
string to reverse.*/
static void button_clicked (GtkButton *button, gpointer user_data)
{
    const char *old_label;
    char *new_label;

    old_label = gtk_button_get_label (ui.grayscale_button);
    new_label = g_utf8_strreverse (old_label, -1);

    gtk_button_set_label (ui.grayscale_button, new_label);
    g_free (new_label);
}

static void activate (GtkApplication *app, gpointer user_data)
{
  	/*Create a window with a title and a default size*/
  	ui.window = gtk_application_window_new (ui.app);
  	gtk_window_set_title (GTK_WINDOW (ui.window), "CText");
  	gtk_window_set_default_size (GTK_WINDOW (ui.window), 300, 300);

	ui.image = gtk_image_new_from_file ("/root/Pictures/zelda.bmp");

  	gtk_container_add (GTK_CONTAINER (ui.window), GTK_WIDGET (ui.image));

    /*Create a button with a label, and add it to the window*/
    ui.grayscale_box = gtk_button_new_with_label ("Click Me");
    gtk_container_add (GTK_CONTAINER (ui.window), ui.grayscale_box);

    /*Connecting the clicked signal to the callback function*/
    g_signal_connect (GTK_BUTTON (ui.grayscale_button),
                      "clicked",
                      G_CALLBACK (button_clicked),
                      G_OBJECT (ui.window));

	gtk_widget_show_all (GTK_WIDGET (ui.window));
}

int main (int argc, char **argv)
{
  int status;

  ui.app = gtk_application_new ("org.gtk.example",G_APPLICATION_FLAGS_NONE);
  g_signal_connect (ui.app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (ui.app), argc, argv);
  g_object_unref (ui.app);
  return status;
}
