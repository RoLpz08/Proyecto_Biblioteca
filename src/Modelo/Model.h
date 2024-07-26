#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <tuple>
#include <stdexcept>

using namespace std;

enum class Rol { ADMINISTRADOR, EMPLEADO, CLIENTE };

class Model {
public:
    map<string, tuple<string, bool, string>> librosPrestados;
    map<string, string> librosGenero;
    const string ARCHIVO_LIBROS_GENERO = "C:\\Users\\Ronal\\Desktop\\Documents\\bin\\Books_Gender.csv";

    map<string, string> cargarLibros(const string& archivo);
    void guardarLibros(const string& archivo, const map<string, string>& libros);
    void modificarLibro(const string& nombreLibro, const string& nuevoGenero);
    void guardarPrestados();
};

#endif // MODEL_H