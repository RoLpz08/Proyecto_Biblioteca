
void mostrarLibros() {
    std::ifstream file("libros.csv");
    
    if (file.is_open()) {
        std::string line;
        
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Libro libro;
            std::string id, nombre, genero, alquilado_str;
            
            std::getline(ss, id, ',');
            libro.id = std::stoi(id);
            
            std::getline(ss, libro.nombre, ',');
            std::getline(ss, libro.genero, ',');
            std::getline(ss, alquilado_str, ',');
            libro.alquilado = (alquilado_str == "1");
            
            std::cout << "ID: " << libro.id << ", Nombre: " << libro.nombre << ", Genero: " << libro.genero << ", Alquilado: " << (libro.alquilado ? "Si" : "No") << '\n';
        }
        
        file.close();
    } else {
        std::cout << "Error al abrir el archivo de libros.\n";
    }
}
