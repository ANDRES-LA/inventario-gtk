#ifndef EXPORTAR_H
#define EXPORTAR_H

#include <gtk/gtk.h>

void exportar_inventario_csv();
void exportar_ventas_csv();
void exportar_inventario_pdf();
void exportar_ventas_pdf();
void on_exportar_datos_clicked(GtkButton *b, gpointer ud);

#endif

