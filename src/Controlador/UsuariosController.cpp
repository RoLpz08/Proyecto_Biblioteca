#include "UsuariosController.h"
#include "../vista/Vista.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace UsuariosController {
    std::vector<Usuario> usuarios;

    void cargarUsuarios() {
        std::ifstream file("Users_Password_Rol.csv");
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo Users_Password_Rol.csv" << std::endl;
            return;
        }

        usuarios.clear();
        std::string linea;
        while (std::getline(file, linea)) {
            std::istringstream ss(linea);
            std::string username, password, rol_str;
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            std::getline(ss, rol_str);

            Rol rol;
            if (rol_str == "Admin") {
                rol = Rol::ADMINISTRADOR;
            } else if (rol_str == "Employee") {
                rol = Rol::EMPLEADO;
            } else {
                rol = Rol::CLIENTE;
            }

            usuarios.push_back({username, password, rol});
        }

        file.close();
    }

    void guardarUsuarios() {
        std::ofstream file("Users_Password_Rol.csv");
        if (!file.is_open()) {
            std::cout << "Error al abrir el archivo Users_Password_Rol.csv para escritura" << std::endl;
            return;
        }

        file << "Username,Password,Rol" << std::endl;
        for (const auto& usuario : usuarios) {
            std::string rol_str;
            switch (usuario.rol) {
                case Rol::ADMINISTRADOR:
                    rol_str = "Admin";
                    break;
                case Rol::EMPLEADO:
                    rol_str = "Employee";
                    break;
                case Rol::CLIENTE:
                    rol_str = "Client";
                    break;
            }
            file << usuario.username << "," << usuario.password << "," << rol_str << std::endl;
        }

        file.close();
    }

    void registrarUsuario() {
        Usuario nuevoUsuario;
        std::cout << "Ingrese el nombre de usuario: ";
        std::cin >> nuevoUsuario.username;
        std::cout << "Ingrese la contraseña: ";
        std::cin >> nuevoUsuario.password;
        std::cout << "Ingrese el rol (Admin (1), Employee (2) o Client (3)): ";
        int opcion;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                nuevoUsuario.rol = Rol::ADMINISTRADOR;
                break;
            case 2:
                nuevoUsuario.rol = Rol::EMPLEADO;
                break;
            case 3:
                nuevoUsuario.rol = Rol::CLIENTE;
                break;
            default:
                std::cout << "Opción inválida. Se utilizará el rol por defecto (Client)." << std::endl;
                nuevoUsuario.rol = Rol::CLIENTE;
                break;
        }

        usuarios.push_back(nuevoUsuario);
        guardarUsuarios();

        std::cout << "Usuario registrado exitosamente" << std::endl;
    }

    bool iniciarSesion(const std::string& username, const std::string& password) {
        for (const auto& usuario : usuarios) {
            if (usuario.username == username && usuario.password == password) {
                std::cout << "Inicio de sesión exitoso" << std::endl;
                std::cout << "Bienvenido " << (usuario.rol == Rol::ADMINISTRADOR ? "Administrador" : (usuario.rol == Rol::EMPLEADO ? "Empleado" : "Cliente")) << " " << usuario.username << "!" << std::endl;
                return true;
            }
        }
        std::cout << "Usuario o contraseña incorrectos" << std::endl;
        return false;
    }

    void accionesSegunRol(const std::string& username) {
        for (const auto& usuario : usuarios) {
            if (usuario.username == username) {
                switch (usuario.rol) {
                    case Rol::ADMINISTRADOR:
                        Vista::menuAdministrador();
                        break;
                    case Rol::EMPLEADO:
                        Vista::menuEmpleado();
                        break;
                    case Rol::CLIENTE:
                        Vista::menuCliente();
                        break;
                }
                break;
            }
        }
    }
}