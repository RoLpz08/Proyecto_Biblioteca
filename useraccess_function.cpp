
bool iniciarSesion(Usuario usuarios[], int numUsuarios, std::string nombre, std::string contrasena) { 

        for (int i = 0; i < numUsuarios; i++) { 
		    if (usuarios[i].nombre == nombre && usuarios[i].contrasena == contrasena) { 
			    std::cout << "Inicio de sesion exitoso" << std::endl; 
				return true; 
				
			} 
		}

 
    std::cout << "Nombre de usuario o contrasena incorrectos" << std::endl;
    return false;
}
