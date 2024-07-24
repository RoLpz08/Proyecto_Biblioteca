#ifndef VISTA_H
#define VISTA_H

#include <vector>
#include "../modelo/Libro.h"

namespace Vista {
    void mostrarMenu();
    void menuAdministrador();
    void menuEmpleado();
    void menuCliente();
    void mostrarLibros(const std::vector<Libro>& libros);
}

#endif // VISTA_H