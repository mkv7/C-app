#include <gtk/gtk.h>

// Callback for the "Add Game" button
static void add_game(GtkWidget *widget, gpointer data) {
    // Implement the logic to add a game
    g_print("Add Game button clicked\n");
}

// Callback for the "Remove Game" button
static void remove_game(GtkWidget *widget, gpointer data) {
    // Implement the logic to remove a selected game
    g_print("Remove Game button clicked\n");
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *add_button, *remove_button;
    GtkWidget *name_entry, *price_entry;
    GtkWidget *label;

    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Game Shop Management");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a grid and attach it to the window
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Name entry
    name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), name_entry, 0, 0, 1, 1);

    // Price entry
    price_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), price_entry, 1, 0, 1, 1);

    // Add Game button
    add_button = gtk_button_new_with_label("Add Game");
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_game), NULL);
    gtk_grid_attach(GTK_GRID(grid), add_button, 0, 1, 1, 1);

    // Remove Game button
    remove_button = gtk_button_new_with_label("Remove Game");
    g_signal_connect(remove_button, "clicked", G_CALLBACK(remove_game), NULL);
    gtk_grid_attach(GTK_GRID(grid), remove_button, 1, 1, 1, 1);

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
