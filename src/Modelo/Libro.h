#ifndef LIBRO_H
#define LIBRO_H

#include <string>

struct Libro {
    std::string nombre;
    std::string genero;
    bool prestado;
    std::string usuario;
};

#endif // LIBRO_H
