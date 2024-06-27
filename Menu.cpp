int main() {
    int opcion;
    
    do {
        std::cout << "\nMenu:\n1. Agregar libro\n2. Mostrar libros\n3. Modificar libro\n4. Eliminar libro\n0. Salir\n";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                agregarLibro();
                break;
            case 2:
                mostrarLibros();
                break;
            case 3:
                int idModificar;
                std::cout << "Ingrese el ID del libro a modificar: ";
                std::cin >> idModificar;
                modificarLibro(idModificar);
                break;
            case 4:
                int idEliminar;
                std::cout << "Ingrese el ID del libro a eliminar: ";
                std::cin >> idEliminar;
                eliminarLibro(idEliminar);
                break;
            case 0:
                break;
            default:
                std::cout << "Opcion invalida. Por favor, seleccione una opcion valida.\n";
        }
        
    } while (opcion != 0);
    
    
    return 0;
}