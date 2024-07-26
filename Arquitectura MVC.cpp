#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>
#include <stdexcept>

using namespace std;

map<string, tuple<string, bool, string>> librosPrestados;
const string ARCHIVO_USUARIOS_CONTRASEÑAS = "C:\\Users\\Ronal\\Desktop\\Documents\\bin\\Users_Password_Rol.csv";
const string ARCHIVO_LIBROS_GENERO = "C:\\Users\\Ronal\\Desktop\\Documents\\bin\\Books_Gender.csv";
map<string, string> librosGenero;
enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

void logError(const string& errorMessage) {
    cerr << errorMessage << endl;
}

map<string, string> cargarLibros(const string& archivo) {
    map<string, string> libros;
    try {
        ifstream file(archivo);
        if (!file.is_open()) throw runtime_error("No se pudo abrir el archivo " + archivo);

        string linea;
        while (getline(file, linea)) {
            istringstream ss(linea);
            string nombre, genero;
            getline(ss, nombre, ',');
            getline(ss, genero, ',');
            libros[nombre] = genero;
        }
        file.close();
    } catch (const exception& e) {
        logError(e.what());
    }
    return libros;
}

map<string, pair<string, Rol>> cargarUsuariosContraseñas(const string& archivo) {
    map<string, pair<string, Rol>> usuariosContraseñas;
    try {
        ifstream file(archivo);
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo " + archivo);

        string linea, usuario, contraseña, rol_str;
        getline(file, linea); // Ignorar la primera línea (encabezados)
        while (getline(file, linea)) {
            stringstream ss(linea);
            getline(ss, usuario, ',');
            getline(ss, contraseña, ',');
            getline(ss, rol_str);
            Rol rol;
            if (rol_str == "Admin") {
                rol = Rol::ADMINISTRADOR;
            } else if (rol_str == "Employee") {
                rol = Rol::EMPLEADO;
            } else {
                rol = Rol::CLIENTE;
            }
            usuariosContraseñas[usuario] = make_pair(contraseña, rol);
        }
        file.close();
    } catch (const exception& e) {
        logError(e.what());
    }
    return usuariosContraseñas;
}

void registrarUsuario(map<string, pair<string, Rol>>& usuariosContraseñas) {
    string username, password, rol_str;
    try {
        cout << "Ingrese el nombre de usuario: ";
        cin >> username;
        cout << "Ingrese la contraseña: ";
        cin >> password;
        cout << "Ingrese el rol (Admin (1), Employee (2) o Client (3)): ";
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            rol_str = "Admin";
        } else if (opcion == 2) {
            rol_str = "Employee";
        } else if (opcion == 3) {
            rol_str = "Client";
        } else {
            cout << "Opción inválida. Se utilizará el rol por defecto (Client)." << endl;
            rol_str = "Client";
        }

        ofstream file(ARCHIVO_USUARIOS_CONTRASEÑAS, ios::app); // Abrir el archivo una sola vez aquí
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo " + ARCHIVO_USUARIOS_CONTRASEÑAS + " para escritura");

        file << username << "," << password << "," << rol_str << endl;
        file.close(); // Cerrar el archivo después de completar el registro del usuario
        cout << "Usuario registrado exitosamente" << endl;

        Rol rol;
        if (rol_str == "Admin") {
            rol = Rol::ADMINISTRADOR;
        } else if (rol_str == "Employee") {
            rol = Rol::EMPLEADO;
        } else {
            rol = Rol::CLIENTE;
        }
        usuariosContraseñas[username] = make_pair(password, rol);
    } catch (const exception& e) {
        logError(e.what());
    }
}

bool iniciarSesion(const map<string, pair<string, Rol>>& usuariosContraseñas, const string& username, const string& password) {
    try {
        auto it = usuariosContraseñas.find(username);
        if (it != usuariosContraseñas.end() && it->second.first == password) {
            cout << "Inicio de sesión exitoso" << endl;
            cout << "Bienvenido " << (it->second.second == Rol::ADMINISTRADOR ? "Administrador" : (it->second.second == Rol::EMPLEADO ? "Empleado" : "Cliente")) << " " << username << "!" << endl;
            return true;
        } else {
            throw runtime_error("Usuario o contraseña incorrectos");
        }
    } catch (const exception& e) {
        logError(e.what());
        return false;
    }
}

void guardarUsuarios(const string& archivo, const map<string, pair<string, Rol>>& usuariosContraseñas) {
    try {
        ofstream file(archivo);
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo " + archivo + " para escritura");

        file << "Usuario,Contraseña,Rol" << endl;
        for (const auto& usuario : usuariosContraseñas) {
            file << usuario.first << "," << usuario.second.first << ",";
            if (usuario.second.second == Rol::ADMINISTRADOR) {
                file << "Admin";
            } else if (usuario.second.second == Rol::EMPLEADO) {
                file << "Employee";
            } else {
                file << "Client";
            }
            file << endl;
        }
        file.close();
        cout << "Usuarios guardados exitosamente" << endl;
    } catch (const exception& e) {
        logError(e.what());
    }
}

void borrarUsuario(map<string, pair<string, Rol>>& usuariosContraseñas) {
    string username;
    try {
        cout << "Ingrese el nombre de usuario a borrar: ";
        cin >> username;
        if (usuariosContraseñas.erase(username)) {
            guardarUsuarios(ARCHIVO_USUARIOS_CONTRASEÑAS, usuariosContraseñas);
            cout << "Usuario borrado exitosamente" << endl;
        } else {
            throw runtime_error("Usuario no encontrado");
        }
    } catch (const exception& e) {
        logError(e.what());
    }
}

void mostrarPrestamos() {
    try {
        ifstream file("Rent_Books.csv");
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo Rent_Books.csv");

        string line;
        getline(file, line); // Ignoramos la primera línea que contiene los encabezados
        cout << "Libros Prestados:" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            string nombre, genero, estado, usuario;
            getline(ss, nombre, ',');
            getline(ss, genero, ',');
            getline(ss, estado, ',');
            getline(ss, usuario);
            cout << "Nombre: " << nombre << ", Genero: " << genero << ", Estado: " << estado << ", Usuario: " << usuario << endl;
        }
        if (line.empty()) {
            cout << "No hay libros prestados" << endl;
        }
        file.close();
    } catch (const exception& e) {
        logError(e.what());
    }
}

map<string, string> cargarLibrosGenero(const string& nombreArchivo) {
    map<string, string> librosGenero;
    ifstream file(nombreArchivo);
    if (file.is_open()) {
        string line;
        getline(file, line); // Ignoramos la primera línea que contiene los encabezados
        while (getline(file, line)) {
            stringstream ss(line);
            string nombre, genero;
            getline(ss, nombre, ',');
            getline(ss, genero);
            librosGenero[nombre] = genero;
        }
        file.close();
    } else {
        throw runtime_error("Error al abrir el archivo " + nombreArchivo);
    }
    return librosGenero;
}

void mostrarLibros(const map<string, string>& librosGenero) {
    for (const auto& libro : librosGenero) {
        cout << "Libro: " << libro.first << ", Genero: " << libro.second << endl;
    }
}

void mostrarLibrosDesdeArchivoCSV(const string& nombreArchivo) {
    try {
        map<string, string> librosGenero = cargarLibrosGenero(nombreArchivo);
        mostrarLibros(librosGenero);
    } catch (const exception& e) {
        logError(e.what());
    }
}

void guardarPrestados() {
    try {
        ofstream file("Rent_Books.csv");
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo Rent_Books.csv");

        file << "Nombre,Genero,Prestado,Usuario" << endl;
        for (const auto& libro : librosPrestados) {
            file << libro.first << "," << get<0>(libro.second) << "," << (get<1>(libro.second) ? "Prestado" : "Disponible") << "," << get<2>(libro.second) << endl;
        }
        file.close();
        cout << "Libros prestados guardados en Rent_Books.csv" << endl;
    } catch (const exception& e) {
        logError(e.what());
    }
}

void cargarLibros(map<string, string>& librosGenero) {
    try {
        librosGenero = cargarLibrosGenero(ARCHIVO_LIBROS_GENERO);
    } catch (const exception& e) {
        logError(e.what());
    }
}

void borrarLibro(map<string, string>& librosGenero) {
    string libro;
    try {
        cout << "Ingrese el nombre del libro a borrar: ";
        cin >> libro;
        if (librosGenero.erase(libro)) {
            cout << "Libro borrado exitosamente" << endl;
        } else {
            throw runtime_error("Libro no encontrado");
        }
    } catch (const exception& e) {
        logError(e.what());
    }
}
void agregarLibro(map<string, string>& librosGenero) {
    string libro, genero;
    try {
        cout << "Ingrese el nombre del libro: ";
        cin >> libro;
        cout << "Ingrese el genero del libro: ";
        cin >> genero;
        librosGenero[libro] = genero;
        cout << "Libro agregado exitosamente" << endl;
    } catch (const exception& e) {
        logError(e.what());
    }
}

void modificarLibro(map<string, string>& librosGenero) {
    string libro, genero;
    try {
        cout << "Ingrese el nombre del libro a modificar: ";
        cin >> libro;
        if (librosGenero.find(libro) == librosGenero.end()) throw runtime_error("Libro no encontrado");

        cout << "Ingrese el nuevo género del libro: ";
        cin >> genero;
        librosGenero[libro] = genero;
    } catch (const exception& e) {
        logError(e.what());
    }
}

void prestarLibro(map<string, string>& librosGenero) {
    string libro;
    try {
        cout << "Ingrese el nombre del libro: ";
        cin >> libro;
        if (librosGenero.find(libro) == librosGenero.end()) throw runtime_error("Libro no encontrado");

        cout << "Libro prestado exitosamente" << endl;
        librosGenero[libro] = "Prestado";
    } catch (const exception& e) {
        logError(e.what());
    }
}

void devolverLibro(map<string, string>& librosGenero) {
    string libro;
    try {
        cout << "Ingrese el nombre del libro: ";
        cin >> libro;
        if (librosGenero.find(libro) == librosGenero.end()) throw runtime_error("Libro no encontrado");

        cout << "Libro devuelto exitosamente" << endl;
        librosGenero[libro] = "Disponible";
    } catch (const exception& e) {
        logError(e.what());
    }
}

void mostrarMenu() {
    cout << "1. Registrar nuevo usuario" << endl;
    cout << "2. Iniciar sesión" << endl;
    cout << "3. Salir" << endl;
}

void menuCliente() {
    int opcion = 0;
    while (opcion != 4) {
        cout << "Menu de cliente" << endl;
        cout << "1. Mostrar libros" << endl;
        cout << "2. Prestar libro" << endl;
        cout << "3. Devolver libro" << endl;
        cout << "4. Salir" << endl;

        cin >> opcion;
        switch (opcion) {
            case 1:
                mostrarLibrosDesdeArchivoCSV("Books_Gender.csv");
                break;
            case 2:
                prestarLibro(librosGenero);
                break;
            case 3:
                devolverLibro(librosGenero);
                break;
            case 4:
                cout << "Adiós" << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    }
}

void menuEmpleado() {
    int opcion = 0;
    while (opcion != 5) {
        cout << "Menu de empleado" << endl;
        cout << "1. Mostrar libros" << endl;
        cout << "2. Cargar libros" << endl;
        cout << "3. Borrar libros" << endl;
        cout << "4. Modificar libros" << endl;
        cout << "5. Salir" << endl;

        cin >> opcion;
        switch (opcion) {
            case 1:
                mostrarLibros(librosGenero);
                break;
            case 2:
                cargarLibros(librosGenero);
                break;
            case 3:
                borrarLibro(librosGenero);
                break;
            case 4:
                modificarLibro(librosGenero);
                break;
            case 5:
                cout << "Adiós" << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    }
}

void menuAdministrador(map<string, pair<string, Rol>>& usuariosContraseñas) {
    int opcion = 0;
    while (opcion != 7) {
        cout << "Menu de administrador" << endl;
        cout << "1. Registrar usuarios" << endl;
        cout << "2. Borrar usuarios" << endl;
        cout << "3. Cargar libros" << endl;
        cout << "4. Mostrar libros" << endl;
        cout << "5. agregar libros" << endl;
        cout << "6. Borrar libros" << endl;
        cout << "7. Historial de préstamos" << endl;
        cout << "8. Salir" << endl;

        cin >> opcion;
        switch (opcion) {
            case 1:
                registrarUsuario(usuariosContraseñas);
                break;
            case 2:
                borrarUsuario(usuariosContraseñas);
                break;
            case 3:
                cargarLibros(librosGenero);
                break;
            case 4:
                mostrarLibros(librosGenero);
                break;
            case 5:
                agregarLibro(librosGenero);
                break;
            case 6:
                borrarLibro(librosGenero);
                break;
            case 7:
                mostrarPrestamos();
                break;
            case 8:
                cout << "Adiós" << endl;
                break;
            default:
                cout << "Opción no válida" << endl;
                break;
        }
    }
}

void accionesSegunRol(const Rol& rol, map<string, pair<string, Rol>>& usuariosContraseñas) {
    switch (rol) {
        case Rol::ADMINISTRADOR:
            menuAdministrador(usuariosContraseñas);
            break;
        case Rol::EMPLEADO:
            menuEmpleado();
            break;
        case Rol::CLIENTE:
            menuCliente();
            break;
    }
}

int main() {
    try {
        map<string, pair<string, Rol>> usuariosContraseñas = cargarUsuariosContraseñas(ARCHIVO_USUARIOS_CONTRASEÑAS);
        map<string, string> librosGenero = cargarLibrosGenero(ARCHIVO_LIBROS_GENERO);

        string username, password;

        cout << "BIENVENIDO AL SISTEMA DE BIBLIOTECA" << endl;
        cout << endl;

        mostrarMenu();
        

        int opcion = 0;
        cin >> opcion;

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
                    accionesSegunRol(usuariosContraseñas[username].second, usuariosContraseñas);
                }
                break;
            case 3:
                cout << "Gracias por usar el sistema de biblioteca. ¡Hasta pronto!" << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
        }
    } catch (const exception& e) {
        logError(e.what());
        cout << e.what() << endl;
    }

    return 0;
}
