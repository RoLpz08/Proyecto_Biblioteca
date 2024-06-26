#include <iostream>
#include <string>

using namespace std;

// Clase para representar el sistema
class LibrarySystem {
public:
    string username;
    string password;

    // Función para ingresar el nombre de usuario y contraseña
    void login() {
        cout << "Ingresa tu nombre de usuario: ";
        cin >> username;
        cout << "Ingresa tu contraseña: ";
        cin >> password;
    }
};

int main() {
    LibrarySystem system;
    system.login();
    return 0;
}