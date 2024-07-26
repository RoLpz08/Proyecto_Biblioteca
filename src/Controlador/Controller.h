#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "View.h"

class Controller {
private:
    Model model;
    View view;

public:
    Controller();
    void mostrarLibros();
    void modificarLibro(const string& nombreLibro, const string& nuevoGenero);
};

#endif // CONTROLLER_H