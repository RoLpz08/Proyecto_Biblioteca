#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

const string ARCHIVO_USUARIOS_CONTRASEÑAS = "Users_Password.csv";

map<string, string> cargarUsuariosContraseñas(const string& archivo) {
    map<string, string> usuariosContraseñas;
    ifstream file(archivo);
    string linea, usuario, contraseña;

    if (file.is_open()) {
        getline(file, linea); // Ignorar la primera línea (encabezados)

        while (getline(file, linea)) {
            stringstream ss(linea);
            getline(ss, usuario, ',');
            getline(ss, contraseña);
            usuariosContraseñas[usuario] = contraseña;
        }

        file.close();
    } else {
        cout << "Error al abrir el archivo " << archivo << endl;
    }

    return usuariosContraseñas;
}

void registrarUsuario(map<string, string>& usuariosContraseñas) {
    string username, password;
    cout << "Ingrese el nombre de usuario: ";
    cin >> username;
    cout << "Ingrese la contraseña: ";
    cin >> password;
    usuariosContraseñas[username] = password;

    ofstream file(ARCHIVO_USUARIOS_CONTRASEÑAS, ios::app);
    if (file.is_open()) {
        file << username << "," << password << endl;
        file.close();
        cout << "Usuario registrado exitosamente" << endl;
    } else {
        cout << "Error al abrir el archivo " << ARCHIVO_USUARIOS_CONTRASEÑAS << " para escritura" << endl;
    }
}

bool iniciarSesion(const map<string, string>& usuariosContraseñas, const string& username, const string& password) {
    auto it = usuariosContraseñas.find(username);
    if (it != usuariosContraseñas.end() && it->second == password) {
        cout << "Inicio de sesión exitoso" << endl;
        return true;
    } else {
        cout << "Usuario o contraseña incorrectos" << endl;
        return false;
    }
}

void mostrarMenu() {
    cout << "1. Registrar nuevo usuario" << endl;
    cout << "2. Iniciar sesión" << endl;
    cout << "3. Salir" << endl;
}

int main() {
    map<string, string> usuariosContraseñas = cargarUsuariosContraseñas(ARCHIVO_USUARIOS_CONTRASEÑAS);

    bool continuar = true;

        while (continuar) {
        mostrarMenu();

        int opcion;
        cin >> opcion;

        string username, password;

        switch (opcion) {
            case 1:
                registrarUsuario(usuariosContraseñas);
                break;
            case 2:
                cout << "Ingrese el nombre de usuario: ";
                cin >> username;
                cout << "Ingrese la contraseña: ";
                cin >> password;
                if (iniciarSesion(usuariosContraseñas, username, password)) {
                    continuar = false; // Si el inicio de sesión es exitoso, dejamos de repetir el bucle
                } else {
                    cout << "Usuario o contraseña incorrectos" << endl;
                }
                break;
            case 3:
                return 0;
            default:
                cout << "Opción inválida" << endl;
                break;
        }

        cout << endl;
    }
    return 0;
}