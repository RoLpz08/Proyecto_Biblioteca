En este programa se define una estructura llamada Usuario que contiene tres atributos: nombre, contraseña y tipo. 
Se implementan dos funciones, una para leer los datos de usuarios desde un archivo CSV y otra para verificar el inicio de sesión de un usuario. 
La función leerUsuarios lee los datos de usuarios desde un archivo CSV llamado "datos_usuarios.csv" y los guarda en un arreglo de estructuras Usuario. 
La función iniciarSesion recibe como parámetros el arreglo de usuarios, el número de usuarios, el nombre y la contraseña ingresados por el usuario al intentar iniciar sesión. 
En la función principal (main) se crea un arreglo de usuarios y se llama a la función leerUsuarios para cargar los datos desde el archivo. 
Luego, se solicita al usuario que ingrese su nombre y contraseña, y se llama a la función iniciarSesion para verificar si los datos son válidos. 
Si el inicio de sesión es exitoso, se muestra un mensaje de éxito.

Tambien se realizó un sistema de gestión de libros que permite al usuario agregar, mostrar, modificar y eliminar libros de una lista almacenada en un archivo CSV llamado "libros.csv".
El programa comienza mostrando un menú con las opciones de agregar libro, mostrar libros, modificar libro, eliminar libro y salir. 
Dependiendo de la opción seleccionada, se ejecuta la función correspondiente.
La función agregarLibro permite ingresar el nombre y género de un nuevo libro, que luego se registra en el archivo "libros.csv".
La función mostrarLibros lee el archivo "libros.csv" y muestra en pantalla los libros registrados, mostrando su ID, nombre, género y si está alquilado o no.
La función modificarLibro permite ingresar el ID de un libro, modificar su nombre y género, y actualiza la información en el archivo "libros.csv".
La función eliminarLibro permite ingresar el ID de un libro, lo elimina de la lista y actualiza el archivo "libros.csv".
El programa sigue ejecutándose y mostrando el menú hasta que el usuario selecciona la opción de salir (0).
