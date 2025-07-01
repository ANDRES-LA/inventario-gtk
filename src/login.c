#include "login.h"
#include <gtk/gtk.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

void mostrar_login(GtkApplication *app) {
    GtkWidget *dialogo, *grid, *entry_usuario, *entry_clave, *lbl_error;
    while (1) {
        dialogo = gtk_dialog_new_with_buttons(
            "Iniciar sesión", NULL,
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
            "_Salir", GTK_RESPONSE_REJECT,
            "_Ingresar", GTK_RESPONSE_ACCEPT,
            NULL);

        grid = gtk_grid_new();
        gtk_container_set_border_width(GTK_CONTAINER(grid), 10);
        gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
        gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

        entry_usuario = gtk_entry_new();
        entry_clave   = gtk_entry_new();
        gtk_entry_set_visibility(GTK_ENTRY(entry_clave), FALSE);
        gtk_entry_set_invisible_char(GTK_ENTRY(entry_clave), '*');

        lbl_error = gtk_label_new(NULL);
        gtk_widget_set_halign(lbl_error, GTK_ALIGN_START);

        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Usuario:"),    0,0,1,1);
        gtk_grid_attach(GTK_GRID(grid), entry_usuario,                1,0,2,1);
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Contraseña:"), 0,1,1,1);
        gtk_grid_attach(GTK_GRID(grid), entry_clave,                  1,1,2,1);
        gtk_grid_attach(GTK_GRID(grid), lbl_error,                    0,2,3,1);

        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialogo))),
                           grid, TRUE, TRUE, 0);
        gtk_widget_show_all(dialogo);

        if (gtk_dialog_run(GTK_DIALOG(dialogo)) == GTK_RESPONSE_REJECT) {
            gtk_widget_destroy(dialogo);
            exit(0);
        }

        const char *usuario = gtk_entry_get_text(GTK_ENTRY(entry_usuario));
        const char *clave   = gtk_entry_get_text(GTK_ENTRY(entry_clave));
        sqlite3 *db; sqlite3_open("inventario.db", &db);
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db,
          "SELECT rol FROM usuarios WHERE usuario=? AND clave=?",
          -1, &stmt, NULL);
        sqlite3_bind_text(stmt,1,usuario,-1,SQLITE_STATIC);
        sqlite3_bind_text(stmt,2,clave,  -1,SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char *rol = (const char*)sqlite3_column_text(stmt,0);
            g_object_set_data(G_OBJECT(app), "rol_usuario", g_strdup(rol));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            gtk_widget_destroy(dialogo);
            break;
        } else {
            gtk_label_set_text(GTK_LABEL(lbl_error), "Usuario o contraseña incorrectos.");
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }

        gtk_widget_destroy(dialogo);
    }
}

