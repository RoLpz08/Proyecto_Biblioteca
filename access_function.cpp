#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Nodo para representar un usuario
struct UserNode {
    string username;
    string password;
    string role;
    UserNode* next;

    UserNode(const string& username, const string& password, const string& role)
        : username(username), password(password), role(role), next(nullptr) {}
};

// Clase para representar el sistema
class LibrarySystem {
public:
    UserNode* users;

    // Función para registrar un nuevo usuario
    void registerUser(const string& username, const string& password, const string& role);

    // Función para ingresar el nombre de usuario y contraseña
    void login() {
        string choice;
        cout << "¿Deseas registrarte o iniciar sesión? (R/S): ";
        cin >> choice;
        if (choice == "R" || choice == "r") {
            string username, password, role;
            cout << "Ingresa tu nombre de usuario: ";
            cin >> username;
            cout << "Ingresa tu contraseña: ";
            cin >> password;
            cout << "Ingresa tu rol (admin/user): ";
            cin >> role;
            registerUser(username, password, role);
        } else if (choice == "S" || choice == "s") {
            string username, password;
            cout << "Ingresa tu nombre de usuario: ";
            cin >> username;
            cout << "Ingresa tu contraseña: ";
            cin >> password;
            // Aquí puedes implementar la lógica para autenticar al usuario
        } else {
            cout << "Opción inválida. Por favor ingresa 'R' para registrarse o 'S' para iniciar sesión." << endl;
        }
    }

    // Función para guardar los usuarios en un archivo CSV
    void saveUsersToCSV();
};

void LibrarySystem::registerUser(const string& username, const string& password, const string& role) {
    UserNode* newUser = new UserNode(username, password, role);
    if (users == nullptr) {
        users = newUser;
    } else {
        UserNode* current = users;
        while (current->next != nullptr) {
            current = current->next;
        } 
        current->next = newUser;
    }
    saveUsersToCSV();
}

void LibrarySystem::saveUsersToCSV() {
    ofstream file("users.csv");
    if (file.is_open()) {
        UserNode* current = users;
        while (current != nullptr) {
            file << current->username << "," << current->password << "," << current->role << "\n";
            current = current->next;
        }
        file.close();
    } else {
        cerr << "Error al abrir el archivo users.csv" << endl;
    }
}

int main() {
    LibrarySystem system;
    system.login();
    return 0;
}