#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

const string ARCHIVO_USUARIOS_CONTRASEÑAS = "Users_Password_Roles.csv";

enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

map<string, pair<string, Rol>> cargarUsuariosContraseñasRoles(const string& archivo) {
    map<string, pair<string, Rol>> usuariosContraseñasRoles;
    ifstream file(archivo);
    string linea, usuario, contraseña, rol_str;
    if (file.is_open()) {
        getline(file, linea); // Ignorar la primera línea (encabezados)
        while (getline(file, linea)) {
            stringstream ss(linea);
            getline(ss, usuario, ',');
            getline(ss, contraseña, ',');
            getline(ss, rol_str);
            Rol rol;
            if (rol_str == "admin") {
                rol = Rol::ADMINISTRADOR;
            } else if (rol_str == "employee") {
                rol = Rol::EMPLEADO;
            } else {
                rol = Rol::CLIENTE;
            }
            usuariosContraseñasRoles[usuario] = make_pair(contraseña, rol);
        }
        file.close();
    } else {
        cout << "Error al abrir el archivo " << archivo << endl;
    }
    return usuariosContraseñasRoles;
}

void accionesSegunRol(const Rol& rol) {
    switch (rol) {
        case Rol::ADMINISTRADOR:
            cout << "Acciones de un administrador" << endl;
            break;
        case Rol::EMPLEADO:
            cout << "Acciones de un empleado" << endl;
            break;
        case Rol::CLIENTE:
            cout << "Acciones de un cliente" << endl;
            break;
    }
}

bool iniciarSesion(const map<string, pair<string, Rol>>& usuariosContraseñasRoles, const string& username, const string& password) {
    auto it = usuariosContraseñasRoles.find(username);
    if (it != usuariosContraseñasRoles.end() && it->second.first == password) {
        accionesSegunRol(it->second.second);
        return true;
    } else {
        cout << "Usuario o contraseña incorrectos" << endl;
        return false;
    }
}

int main() {
    map<string, pair<string, Rol>> usuariosContraseñasRoles = cargarUsuariosContraseñasRoles(ARCHIVO_USUARIOS_CONTRASEÑAS);
    // Resto del código principal
    return 0;
}