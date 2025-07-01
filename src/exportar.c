#include "exportar.h"
#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdio.h>
#include <cairo.h>
#include <cairo-pdf.h>

void exportar_inventario_csv() {
    sqlite3 *db;
    sqlite3_stmt *st;
    FILE *f = fopen("inventario.csv", "w");
    if (!f) {
        g_print("Error creando inventario.csv\n");
        return;
    }
    fprintf(f, "ID,Nombre,Cantidad,Precio\n");
    if (sqlite3_open("inventario.db", &db) == SQLITE_OK) {
        sqlite3_prepare_v2(db, "SELECT id,nombre,cantidad,precio FROM productos", -1, &st, NULL);
        while (sqlite3_step(st) == SQLITE_ROW) {
            fprintf(f, "%d,%s,%d,%.2f\n",
                    sqlite3_column_int(st, 0),
                    sqlite3_column_text(st, 1),
                    sqlite3_column_int(st, 2),
                    sqlite3_column_double(st, 3));
        }
        sqlite3_finalize(st);
        sqlite3_close(db);
    }
    fclose(f);
    g_print("inventario.csv generado\n");
}

void exportar_ventas_csv() {
    g_print("Función exportar_ventas_csv aún no implementada.\n");
}

void exportar_inventario_pdf() {
    g_print("Función exportar_inventario_pdf aún no implementada.\n");
}

void exportar_ventas_pdf() {
    g_print("Función exportar_ventas_pdf aún no implementada.\n");
}

void on_exportar_datos_clicked(GtkButton *b, gpointer ud) {
    exportar_inventario_csv();
}

