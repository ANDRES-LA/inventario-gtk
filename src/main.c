#include <gtk/gtk.h>
#include "bd.h"
#include "login.h"
#include "app.h"

static void on_app_activate(GtkApplication *app, gpointer user_data) {
    mostrar_login(app);               // Login real
    activar_interfaz(app, user_data); // Interfaz real
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    crear_base_de_datos();
    crear_tabla_usuarios();
    crear_tabla_ventas();

    app = gtk_application_new("com.inventario.tienda", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_app_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

