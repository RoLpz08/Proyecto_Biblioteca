#ifndef USUARIO_H
#define USUARIO_H

#include <string>

enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

struct Usuario {
    std::string username;
    std::string password;
    Rol rol;
};

#endif // USUARIO_H