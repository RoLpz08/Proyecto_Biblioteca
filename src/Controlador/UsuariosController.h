#ifndef USUARIOS_CONTROLLER_H
#define USUARIOS_CONTROLLER_H

#include <string>
#include <vector>
#include "../modelo/Usuario.h"

namespace UsuariosController {
    extern std::vector<Usuario> usuarios;

    void cargarUsuarios();
    void guardarUsuarios();
    void registrarUsuario();
    bool iniciarSesion(const std::string& username, const std::string& password);
    void accionesSegunRol(const std::string& username);
}

#endif // USUARIOS_CONTROLLER_H