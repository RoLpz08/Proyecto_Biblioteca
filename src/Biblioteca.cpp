#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;


map<string, tuple<string, bool, string>> librosPrestados;
const string ARCHIVO_USUARIOS_CONTRASEÑAS = "Users_Password_Rol.csv";
const string ARCHIVO_LIBROS_GENERO = "Books_Gender.csv";
map<string, string> librosGenero;

enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };


map<string, string> cargarLibrosGenero(const string& archivo) {
    map<string, string> librosGenero;
    ifstream file(archivo);
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            istringstream ss(linea);
            string libro, genero;
            getline(ss, libro, ',');
            getline(ss, genero);
            librosGenero[libro] = genero;
        }
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << archivo << endl;
    }
    return librosGenero;
}
map<string, pair<string, Rol>> cargarUsuariosContraseñas(const string& archivo) {
    map<string, pair<string, Rol>> usuariosContraseñas;
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
    } else {
        cout << "Error al abrir el archivo " << archivo << endl;
    }
    return usuariosContraseñas;
}
void registrarUsuario(map<string, pair<string, Rol>>& usuariosContraseñas) {
    string username, password, rol_str;
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

    if (file.is_open()) {
        file << username << "," << password << "," << rol_str << endl;
        file.close(); // Cerrar el archivo después de completar el registro del usuario
        cout << "Usuario registrado exitosamente" << endl;
    } else {
        cout << "Error al abrir el archivo " << ARCHIVO_USUARIOS_CONTRASEÑAS << " para escritura" << endl;
    }

    Rol rol;
    if (rol_str == "Admin") {
        rol = Rol::ADMINISTRADOR;
    } else if (rol_str == "Employee") {
        rol = Rol::EMPLEADO;
    } else {
        rol = Rol::CLIENTE;
    }
    usuariosContraseñas[username] = make_pair(password, rol);
}
bool iniciarSesion(const map<string, pair<string, Rol>>& usuariosContraseñas, const string& username, const string& password) {
    auto it = usuariosContraseñas.find(username);
    if (it != usuariosContraseñas.end() && it->second.first == password) {
        cout << "Inicio de sesión exitoso" << endl;
        cout << "Bienvenido " << (it->second.second == Rol::ADMINISTRADOR ? "Administrador" : (it->second.second == Rol::EMPLEADO ? "Empleado" : "Cliente")) << " " << username << "!" << endl;
        return true;
    } else {
        cout << "Usuario o contraseña incorrectos" << endl;
        return false;
    }
}
void borrarUsuario(map<string, pair<string, Rol>>& usuariosContraseñas) {
    string username;
    cout << "Ingrese el nombre de usuario a borrar: ";
    cin >> username;
    if (usuariosContraseñas.erase(username)) {
        cout << "Usuario borrado exitosamente" << endl;
    } else {
        cout << "Usuario no encontrado" << endl;
    }
}
void mostrarPrestamos() {
    ifstream file("Rent_Books.csv");
    
    if (file.is_open()) {
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
            
            cout << "Nombre: " << nombre << ", Genero: " << genero 
                 << ", Estado: " << estado << ", Usuario: " << usuario << endl;
        }
        if (line == "") {
            cout << "No hay libros prestados" << endl;
        }
        file.close();
    } else {
        // Si el archivo no existe, lo creamos
        ofstream file("Rent_Books.csv");
        if (file.is_open()) {
            cout << "No existia el archivo de prestamos" << endl;
            cout << "Archivo Rent_Books.csv creado exitosamente" << endl;
            file.close();
        } else {
            cout << "Error al crear el archivo Rent_Books.csv" << endl;
        }
    }
}
void mostrarLibros(const map<string, string>& librosGenero) {
    for (const auto& libro : librosGenero) {
        cout << "Libro: " << libro.first << ", Genero: " << libro.second << endl;
    }
}

void mostrarLibrosDesdeArchivoCSV(const string& nombreArchivo) {
    map<string, string> librosGenero;
    ifstream file(nombreArchivo);
    
    if (file.is_open()) {
        string line;
        getline(file, line); // Ignoramos la primera línea que contiene los encabezados
        
        while (getline(file, line)) {
            stringstream ss(line);
            string nombre, genero;
            
            getline(ss, nombre, ',');
            getline(ss, genero, ',');
            
            librosGenero[nombre] = genero;
        }
        
        file.close();
        
        mostrarLibros(librosGenero);
    } else {
        cout << "Error al abrir el archivo " << nombreArchivo << endl;
    }
}
void guardarPrestados() {
    ofstream file("Rent_Books.csv");
    
    if (file.is_open()) {
        file << "Nombre,Genero,Prestado,Usuario" << endl;
        
        for (const auto& libro : librosPrestados) {
            file << libro.first << "," << get<0>(libro.second) << "," 
                 << (get<1>(libro.second) ? "Prestado" : "Disponible") << ","
                 << get<2>(libro.second) << endl;
        }
        
        file.close();
        cout << "Libros prestados guardados en Rent_Books.csv" << endl;
    } else {
        cout << "Error al abrir el archivo Rent_Books.csv" << endl;
    }
}
void cargarLibros(map<string, string>& librosGenero) {
    string libro, genero;
    cout << "Ingrese el nombre del libro: ";
    cin >> libro;
    cout << "Ingrese el genero del libro: ";
    cin >> genero;
    librosGenero[libro] = genero;
}
void borrarLibro(map<string, string>& librosGenero) {
    string libro;
    cout << "Ingrese el nombre del libro a borrar: ";
    cin >> libro;
    if (librosGenero.erase(libro)) {
        cout << "Libro borrado exitosamente" << endl;
    } else {
        cout << "Libro no encontrado" << endl;
    }
}
void modificarLibro(map<string, string>& librosGenero) {
    string libro, genero;
    cout << "Ingrese el nombre del libro a modificar: ";
    cin >> libro;
    if (librosGenero.find(libro) == librosGenero.end()) {
        cout << "Libro no encontrado" << endl;
        return;
        }
    cout << "Ingrese el nuevo genero del libro: ";
    cin >> genero;
    librosGenero[libro] = genero;
}
void prestarLibro(map<string, string>& librosGenero) {
    string libro;
    cout << "Ingrese el nombre del libro: ";
    cin >> libro;
    if (librosGenero.find(libro) == librosGenero.end()) {
        cout << "Libro no encontrado" << endl;
        return;
        }
    cout << "Libro prestado exitosamente" << endl;
    librosGenero[libro] = "Prestado";
}
void devolverLibro(map<string, string>& librosGenero) {
    string libro;
    cout << "Ingrese el nombre del libro: ";
    cin >> libro;
    if (librosGenero.find(libro) == librosGenero.end()) {
        cout << "Libro no encontrado" << endl;
        return;
        }
    cout << "Libro devuelto exitosamente" << endl;
    librosGenero[libro] = "Disponible";
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
    cout << "1. mostrar libros" << endl;
    cout << "2. prestar libro" << endl;
    cout << "3. devolver libro" << endl;
    cout << "4. salir" << endl;

    
    cin >> opcion;
    switch (opcion)
    {
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
        cout << "Adios" << endl;
        break;
    default:
        cout << "Opcion no valida" << endl;
        break;
    }
    }
}
void menuEmpleado() {
    
    cout << "Menu de empleado" << endl;
    cout << "1. mostrar libros" << endl;
    cout << "2. Cargar libros" << endl;
    cout << "3. borrar libros" << endl;
    cout << "4. modificar libros" << endl;
    cout << "5. salir" << endl;

    int opcion = 0;
    switch (opcion)
    {
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
        cout << "Adios" << endl;
        break;
    default:
        cout << "Opcion no valida" << endl;
        break;
    }
}
void menuAdministrador(map<string, pair<string, Rol>>& usuariosContraseñas) {

    int opcion = 0;

    cout << "Menu de administrador" << endl;
    cout << "1. Registrar usuarios" << endl;
    cout << "2. borrar usuarios" << endl;
    cout << "3. mostrar libros" << endl;
    cout << "3. Cargar libros" << endl;
    cout << "4. borrar libros" << endl;
    cout << "5. modificar libros" << endl;
    cout << "6. historial de prestamos" << endl;
    cout << "7. salir" << endl;
 
    cin >> opcion;
     
     switch (opcion)
     {
     case 1:
         registrarUsuario(usuariosContraseñas);
         break;
     case 2:
         borrarUsuario(usuariosContraseñas);
         break;
     case 3:
         mostrarLibros(librosGenero);
         break;
     case 4:
         cargarLibros(librosGenero);
         break;
     case 5:
         borrarLibro(librosGenero);
         break;
     case 6:
         mostrarPrestamos();
         break;
     case 7:
         cout << "Adios" << endl;
         break;
     default:
         cout << "Opcion no valida" << endl;
         break;
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
    map<string, pair<string, Rol>> usuariosContraseñas = cargarUsuariosContraseñas(ARCHIVO_USUARIOS_CONTRASEÑAS);
    map<string, string> librosGenero = cargarLibrosGenero(ARCHIVO_LIBROS_GENERO);

    string username, password; 
    string nombre, genero, estado, usuario; 

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

                return 0; // Detiene la ejecución del programa después de iniciar sesión
            }
            break;
        case 3:
            cout << "Gracias por usar el sistema de biblioteca. ¡Hasta pronto!" << endl;
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
    }

    return 0;
}