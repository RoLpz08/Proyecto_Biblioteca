
numUsuarios = 0;
while (getline(archivo, linea)) {
    std::string nombre, contrasena, tipo;
    size_t coma1 = linea.find(",");
    size_t coma2 = linea.find(",", coma1 + 1);

    nombre = linea.substr(0, coma1);
    contrasena = linea.substr(coma1 + 1, coma2 - coma1 - 1);
    tipo = linea.substr(coma2 + 1);

    Usuario usuario;
    usuario.nombre = nombre;
    usuario.contrasena = contrasena;
    usuario.tipo = tipo;

    usuarios[numUsuarios] = usuario;
    numUsuarios++;
}

archivo.close();
}
