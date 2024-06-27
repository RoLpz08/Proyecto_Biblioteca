
void eliminarLibro(int id) {
    std::ifstream inFile("libros.csv");
    std::ofstream outFile("temp.csv");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cout << "Error al abrir los archivos.\n";
        return;
    }

    std::string line;
    bool encontrado = false;

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string currentId;
        std::getline(ss, currentId, ',');

        if (std::stoi(currentId) == id) {
            encontrado = true;
            std::cout << "Libro eliminado correctamente.\n";
        } else {
            outFile << line << '\n';
        }
    }

    inFile.close();
    outFile.close();

    remove("libros.csv");
    rename("temp.csv", "libros.csv");

    if (!encontrado) {
        std::cout << "ID de libro no encontrado.\n";
    }
}