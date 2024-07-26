#include "Model.h"

void logError(const string& errorMessage) {
    cerr << errorMessage << endl;
}

map<string, string> Model::cargarLibros(const string& archivo) {
    map<string, string> libros;
    try {
        ifstream file(archivo);
        if (!file.is_open()) throw runtime_error("No se pudo abrir el archivo " + archivo);

        string linea;
        while (getline(file, linea)) {
            istringstream ss(linea);
            string nombre, genero;
            getline(ss, nombre, ',');
            getline(ss, genero, ',');
            libros[nombre] = genero;
        }
        file.close();
    } catch (const exception& e) {
        logError(e.what());
    }
    return libros;
}

void Model::guardarLibros(const string& archivo, const map<string, string>& libros) {
    try {
        ofstream file(archivo);
        if (!file.is_open()) throw runtime_error("No se pudo abrir el archivo " + archivo);

        for (const auto& [nombre, genero] : libros) {
            file << nombre << "," << genero << endl;
        }
        file.close();
        cout << "Libros guardados en " << archivo << endl;
    } catch (const exception& e) {
        logError(e.what());
    }
}

void Model::modificarLibro(const string& nombreLibro, const string& nuevoGenero) {
    try {
        if (librosGenero.find(nombreLibro) != librosGenero.end()) {
            librosGenero[nombreLibro] = nuevoGenero;
            guardarLibros(ARCHIVO_LIBROS_GENERO, librosGenero);
            cout << "Libro modificado exitosamente" << endl;
        } else {
            throw runtime_error("Libro no encontrado");
        }
    } catch (const exception& e) {
        logError(e.what());
    }
}

void Model::guardarPrestados() {
    try {
        ofstream file("Rent_Books.csv");
        if (!file.is_open()) throw runtime_error("Error al abrir el archivo Rent_Books.csv");

        file << "Nombre,Genero,Prestado,Usuario" << endl;
        for (const auto& libro : librosPrestados) {
            file << libro.first << "," << get<0>(libro.second) << "," << (get<1>(libro.second) ? "Prestado" : "Disponible") << "," << get<2>(libro.second) << endl;
        }
        file.close();
        cout << "Libros prestados guardados en Rent_Books.csv" << endl;
    } catch (const exception& e) {
        logError(e.what());
    }
}