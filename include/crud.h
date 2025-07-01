#ifndef CRUD_H
#define CRUD_H

#include <gtk/gtk.h>

void insertar_producto(const char *n, int c, float p);
void actualizar_producto(int id, const char *n, int c, float p);
void eliminar_producto(int id);
void cargar_productos(GtkListStore *store);

#endif
