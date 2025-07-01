#include "app.h"
#include "crud.h"
#include "exportar.h"
#include <gtk/gtk.h>
#include <string.h>

typedef struct {
    GtkWidget *ventana;
    GtkWidget *btn_exportar;
    GtkListStore *store;
} AppWidgets;

void on_exportar_clicked(GtkButton *b, gpointer user_data) {
    AppWidgets *w = user_data;
    on_exportar_datos_clicked(b, user_data);
}

void activar_interfaz(GtkApplication *app, gpointer user_data) {
    AppWidgets *w = g_malloc0(sizeof(AppWidgets));

    w->ventana = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(w->ventana), "Inventario GTK");
    gtk_window_set_default_size(GTK_WINDOW(w->ventana), 600, 400);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(w->ventana), grid);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    w->store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_DOUBLE);
    GtkWidget *tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(w->store));

    const char *cols[] = {"ID", "Nombre", "Cantidad", "Precio"};
    for (int i = 0; i < 4; ++i) {
        GtkCellRenderer *r = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *c = gtk_tree_view_column_new_with_attributes(cols[i], r, "text", i, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(tree), c);
    }

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), tree);
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);

    w->btn_exportar = gtk_button_new_with_label("Exportar Inventario CSV");
    g_signal_connect(w->btn_exportar, "clicked", G_CALLBACK(on_exportar_clicked), w);

    gtk_grid_attach(GTK_GRID(grid), scroll, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), w->btn_exportar, 0, 1, 1, 1);

    cargar_productos(w->store);
    gtk_widget_show_all(w->ventana);
}

