#include "../Controlador/Controller.h"

int main() {
    Controller controller;
    controller.mostrarLibros();
    controller.modificarLibro("LibroEjemplo", "NuevoGenero");
    controller.mostrarLibros();
    return 0;
}