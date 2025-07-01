# 🧾 Sistema de Inventario y Ventas en C con GTK+ y SQLite

Este es un sistema de inventario de escritorio desarrollado en lenguaje C, utilizando las bibliotecas **GTK+ 3** para la interfaz gráfica, **SQLite3** como base de datos embebida, y **Cairo** para la exportación a PDF.  
Forma parte del curso **IE-0117: Programación Bajo Plataformas Abiertas** en la Escuela de Ingeniería Eléctrica de la Universidad de Costa Rica.

---

## 📌 1. Descripción del proyecto

El sistema permite a un usuario administrar productos en inventario, registrar ventas y exportar reportes de forma sencilla.  
Está diseñado para funcionar en equipos con Linux y sin necesidad de conexión a internet, gracias al uso de tecnologías locales como GTK y SQLite.

### Características principales:

- ABM completo de productos (alta, baja y modificación)
- Registro de ventas
- Sistema de login con control de acceso por rol (administrador / vendedor)
- Exportación de reportes en formato CSV y PDF
- Estadísticas de productos más vendidos

---

## ⚙️ 2. Dependencias e instalación

Este proyecto está desarrollado en C y requiere algunas bibliotecas que puedes instalar desde tu terminal con `apt` (Debian/Ubuntu).

### 🔧 Dependencias

Ejecuta estos comandos para instalar todo lo necesario:

```bash
sudo apt update
sudo apt install build-essential libgtk-3-dev libsqlite3-dev libcairo2-dev
También debes tener git instalado:

bash
Copiar
Editar
sudo apt install git
🚀 3. Pasos para compilación y ejecución
Sigue estos pasos para compilar y correr el sistema desde tu terminal:

📥 Clonar el repositorio
bash
Copiar
Editar
git clone https://github.com/TU_USUARIO/inventario-gtk.git
cd inventario-gtk
(Reemplaza TU_USUARIO por tu nombre real de usuario en GitHub.)

🏗️ Compilar el proyecto
bash
Copiar
Editar
make
Este comando creará el ejecutable inventario.

▶️ Ejecutar el sistema
bash
Copiar
Editar
./inventario
👤 Usuario por defecto
El sistema crea por defecto el siguiente usuario administrador al iniciarse:

Usuario: admin

Contraseña: admin123

📁 Estructura del proyecto
java
Copiar
Editar
inventario-gtk/
├── src/         → Código fuente en C
├── include/     → Archivos de cabecera (.h)
├── obj/         → Objetos compilados
├── inventario   → Ejecutable final
├── Makefile     → Script de compilación
└── README.md    → Este archivo
📚 Créditos
Proyecto desarrollado como parte del curso IE-0117 – Programación Bajo Plataformas Abiertas
Universidad de Costa Rica – Escuela de Ingeniería Eléctrica
Ciclo I-2025
