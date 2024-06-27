
int main() { 

    const int MAX_USUARIOS = 1000; 
    Usuario usuarios[MAX_USUARIOS]; 
    int numUsuarios = 0;

    leerUsuarios(usuarios, numUsuarios);

        std::string nombre, contrasena;
        std::cout << "Nombre de usuario: ";
        std::cin >> nombre;
        std::cout << "Contrasena: ";
        std::cin >> contrasena;

if (iniciarSesion(usuarios, numUsuarios, nombre, contrasena)) {
    
}

return 0;
}