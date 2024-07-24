#include "Vista.h"
#include <iostream>

using namespace std;

namespace Vista {
    void mostrarMenu() {
        cout << "BIENVENIDO AL SISTEMA DE BIBLIOTECA" << endl;
        cout << "1. Registrar nuevo usuario" << endl;
        cout << "2. Iniciar sesión" << endl;
        cout << "3. Salir" << endl;
    }

    void menuAdministrador() {
        cout << "Menu de administrador" << endl;
        cout << "1. Registrar usuarios" << endl;
        cout << "2. Borrar usuario" << endl;
        cout << "3. Mostrar libros" << endl;
        cout << "4. Cargar libros" << endl;
        cout << "5. Borrar libro" << endl;
        cout << "6. Modificar libro" << endl;
        cout << "7. Mostrar historial de préstamos" << endl;
        cout << "8. Salir" << endl;
    }

    void menuEmpleado() {
        cout << "Menu de empleado" << endl;
        cout << "1. Mostrar libros" << endl;
        cout << "2. Cargar libros" << endl;
        cout << "3. Borrar libro" << endl;
        cout << "4. Modificar libro" << endl;
        cout << "5. Salir" << endl;
    }

    void menuCliente() {
        cout << "Menu de cliente" << endl;
        cout << "1. Mostrar libros" << endl;
        cout << "2. Prestar libro" << endl;
        cout << "3. Devolver libro" << endl;
        cout << "4. Salir" << endl;
    }

    void mostrarLibros(const std::vector<Libro>& libros) {
        if (libros.empty()) {
            cout << "No hay libros disponibles" << endl;
            return;
        }

        cout << "Libros disponibles:" << endl;
        for (const auto& libro : libros) {
            cout << "Nombre: " << libro.nombre << ", Género: " << libro.genero << ", Estado: " << (libro.prestado ? "Prestado" : "Disponible") << endl;
        }
    }
}