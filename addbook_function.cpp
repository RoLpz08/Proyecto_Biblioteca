void agregarLibro() {
    Libro nuevoLibro;
    std::ofstream file("libros.csv", std::ios::app);
    
    if (file.is_open()) {
        std::cout << "Ingrese el nombre del libro: ";
        std::cin >> nuevoLibro.nombre;
        std::cout << "Ingrese el genero del libro: ";
        std::cin >> nuevoLibro.genero;
        nuevoLibro.alquilado = false;
        
        file << nuevoLibro.id << ',' << nuevoLibro.nombre << ',' << nuevoLibro.genero << ',' << nuevoLibro.alquilado << '\n';
        
        file.close();
        std::cout << "Libro agregado correctamente.\n";
    } else {
        std::cout << "Error al abrir el archivo de libros.\n";
    }
}
