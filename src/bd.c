#include "bd.h"
#include <sqlite3.h>
#include <stddef.h>

void crear_base_de_datos() {
    sqlite3 *db;
    if (sqlite3_open("inventario.db", &db) != SQLITE_OK) return;
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS productos ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " nombre TEXT NOT NULL,"
        " cantidad INTEGER NOT NULL,"
        " precio REAL NOT NULL);",
        NULL, NULL, NULL);
    sqlite3_close(db);
}

void crear_tabla_usuarios() {
    sqlite3 *db;
    sqlite3_open("inventario.db", &db);
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS usuarios ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " usuario TEXT NOT NULL UNIQUE,"
        " clave TEXT NOT NULL,"
        " rol TEXT NOT NULL);",
        NULL, NULL, NULL);
    sqlite3_exec(db,
        "INSERT OR IGNORE INTO usuarios (usuario, clave, rol) "
        "VALUES ('admin','admin123','admin'),"
               "('vendedor','ventas123','vendedor');",
        NULL, NULL, NULL);
    sqlite3_close(db);
}

void crear_tabla_ventas() {
    sqlite3 *db;
    if (sqlite3_open("inventario.db", &db) != SQLITE_OK) return;
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS ventas ("
        " id INTEGER PRIMARY KEY AUTOINCREMENT,"
        " producto_id INTEGER,"
        " nombre TEXT,"
        " cantidad INTEGER,"
        " precio_unitario REAL,"
        " total REAL,"
        " fecha TEXT);",
        NULL, NULL, NULL);
    sqlite3_close(db);
}
