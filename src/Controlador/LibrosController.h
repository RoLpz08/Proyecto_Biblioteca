#ifndef LIBROS_CONTROLLER_H
#define LIBROS_CONTROLLER_H

#include <vector>
#include "../modelo/Libro.h"

namespace LibrosController {
    extern std::vector<Libro> libros;

    void cargarLibros();
    void guardarLibros();
    void mostrarLibros();
    void borrarLibro(int indice);
    void modificarLibro(int indice, const Libro& nuevoLibro);
}

#endif // LIBROS_CONTROLLER_H