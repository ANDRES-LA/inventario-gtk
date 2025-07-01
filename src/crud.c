#include "crud.h"
#include <sqlite3.h>
#include <gtk/gtk.h>

void insertar_producto(const char *n, int c, float p) {
    sqlite3 *db; sqlite3_stmt *st;
    if (sqlite3_open("inventario.db",&db)!=SQLITE_OK) return;
    sqlite3_prepare_v2(db,
        "INSERT INTO productos(nombre,cantidad,precio) VALUES(?,?,?)",
        -1,&st,NULL);
    sqlite3_bind_text  (st,1,n,-1,SQLITE_STATIC);
    sqlite3_bind_int   (st,2,c);
    sqlite3_bind_double(st,3,p);
    sqlite3_step(st);
    sqlite3_finalize(st);
    sqlite3_close(db);
}

void actualizar_producto(int id, const char *n, int c, float p) {
    sqlite3 *db; sqlite3_stmt *st;
    if (sqlite3_open("inventario.db",&db)!=SQLITE_OK) return;
    sqlite3_prepare_v2(db,
        "UPDATE productos SET nombre=?,cantidad=?,precio=? WHERE id=?",
        -1,&st,NULL);
    sqlite3_bind_text  (st,1,n,-1,SQLITE_STATIC);
    sqlite3_bind_int   (st,2,c);
    sqlite3_bind_double(st,3,p);
    sqlite3_bind_int   (st,4,id);
    sqlite3_step(st);
    sqlite3_finalize(st);
    sqlite3_close(db);
}

void eliminar_producto(int id) {
    sqlite3 *db; sqlite3_stmt *st;
    if (sqlite3_open("inventario.db",&db)!=SQLITE_OK) return;
    sqlite3_prepare_v2(db,"DELETE FROM productos WHERE id=?", -1,&st,NULL);
    sqlite3_bind_int(st,1,id);
    sqlite3_step(st);
    sqlite3_finalize(st);
    sqlite3_prepare_v2(db,"SELECT COUNT(*) FROM productos",-1,&st,NULL);
    if (sqlite3_step(st)==SQLITE_ROW && sqlite3_column_int(st,0)==0)
        sqlite3_exec(db,"DELETE FROM sqlite_sequence WHERE name='productos';",NULL,NULL,NULL);
    sqlite3_finalize(st);
    sqlite3_close(db);
}

void cargar_productos(GtkListStore *store) {
    sqlite3 *db; sqlite3_stmt *st;
    if (sqlite3_open("inventario.db",&db)!=SQLITE_OK) return;
    gtk_list_store_clear(store);
    sqlite3_prepare_v2(db,
        "SELECT id,nombre,cantidad,precio FROM productos ORDER BY id DESC",
        -1,&st,NULL);
    while (sqlite3_step(st)==SQLITE_ROW) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, sqlite3_column_int   (st,0),
            1, (const char*)sqlite3_column_text(st,1),
            2, sqlite3_column_int   (st,2),
            3, sqlite3_column_double(st,3),
           -1);
    }
    sqlite3_finalize(st);
    sqlite3_close(db);
}
