#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Definici�n de la estructura del libro
struct Libro {
    string titulo;
    string autor;
    string genero;
    string ISBN;

    // M�todo para serializar un libro y escribirlo en un archivo
    void serializar(ofstream& archivo) const {
        archivo << titulo << endl;
        archivo << autor << endl;
        archivo << genero << endl;
        archivo << ISBN << endl;
    }

    // M�todo para deserializar un libro ley�ndolo desde un archivo
    void deserializar(ifstream& archivo) {
        getline(archivo, titulo);
        getline(archivo, autor);
        getline(archivo, genero);
        getline(archivo, ISBN);
    }
};

// Nodo para el �rbol binario de b�squeda
struct NodoArbol {
    Libro libro;
    NodoArbol* izq;
    NodoArbol* der;

    // Constructor
    NodoArbol(Libro lib) : libro(lib), izq(nullptr), der(nullptr) {}
};

// Clase para el �rbol binario de b�squeda
class ArbolBinario {
private:
    NodoArbol* raiz;
    ofstream archivoSalida; // Mantener el archivo abierto para escribir

    // Funci�n privada para insertar un libro en el �rbol
    NodoArbol* insertar(NodoArbol* nodo, Libro libro) {
        if (nodo == nullptr) {
            return new NodoArbol(libro);
        }
        if (libro.titulo < nodo->libro.titulo) {
            nodo->izq = insertar(nodo->izq, libro);
        } else {
            nodo->der = insertar(nodo->der, libro);
        }
        return nodo;
    }

    // Funci�n privada para buscar un libro por t�tulo
    NodoArbol* buscarPorTitulo(NodoArbol* nodo, string titulo) {
        if (nodo == nullptr || nodo->libro.titulo == titulo) {
            return nodo;
        }
        if (titulo < nodo->libro.titulo) {
            return buscarPorTitulo(nodo->izq, titulo);
        }
        return buscarPorTitulo(nodo->der, titulo);
    }

    // Funci�n privada para buscar un libro por autor
    NodoArbol* buscarPorAutor(NodoArbol* nodo, string autor) {
        if (nodo == nullptr || nodo->libro.autor == autor) {
            return nodo;
        }
        if (autor < nodo->libro.autor) {
            return buscarPorAutor(nodo->izq, autor);
        }
        return buscarPorAutor(nodo->der, autor);
    }

    // Funci�n privada para buscar un libro por g�nero
    NodoArbol* buscarPorGenero(NodoArbol* nodo, string genero) {
        if (nodo == nullptr || nodo->libro.genero == genero) {
            return nodo;
        }
        if (genero < nodo->libro.genero) {
            return buscarPorGenero(nodo->izq, genero);
        }
        return buscarPorGenero(nodo->der, genero);
    }

    // Funci�n privada para buscar un libro por ISBN
    NodoArbol* buscarPorISBN(NodoArbol* nodo, string ISBN) {
        if (nodo == nullptr || nodo->libro.ISBN == ISBN) {
            return nodo;
        }
        if (ISBN < nodo->libro.ISBN) {
            return buscarPorISBN(nodo->izq, ISBN);
        }
        return buscarPorISBN(nodo->der, ISBN);
    }

public:
    // Constructor
    ArbolBinario() : raiz(nullptr) {
        // Abrir el archivo para escribir
        archivoSalida.open("libros.txt", ios::app);
        if (!archivoSalida.is_open()) {
            cerr << "Error al abrir el archivo." << endl;
        }
    }

    // Destructor
    ~ArbolBinario() {
        // Cerrar el archivo al destruir el objeto
        archivoSalida.close();
    }

    // M�todo p�blico para insertar un libro en el �rbol
    void insertarLibro(Libro libro) {
        raiz = insertar(raiz, libro);

        // Serializar el libro y guardarlo en el archivo
        if (archivoSalida.is_open()) {
            libro.serializar(archivoSalida);
        } else {
            cerr << "Error al escribir en el archivo." << endl;
        }
    }

    // M�todo p�blico para buscar un libro por t�tulo
    NodoArbol* buscarLibroPorTitulo(string titulo) {
        return buscarPorTitulo(raiz, titulo);
    }

    // M�todo p�blico para buscar un libro por autor
    NodoArbol* buscarLibroPorAutor(string autor) {
        return buscarPorAutor(raiz, autor);
    }

    // M�todo p�blico para buscar un libro por g�nero
    NodoArbol* buscarLibroPorGenero(string genero) {
        return buscarPorGenero(raiz, genero);
    }

    // M�todo p�blico para buscar un libro por ISBN
    NodoArbol* buscarLibroPorISBN(string ISBN) {
        return buscarPorISBN(raiz, ISBN);
    }
};

// Clase para el sistema de inicio de sesi�n
class SistemaLogin {
private:
    unordered_map<string, string> usuarios; // Almacenamiento de usuarios y contrase�as
    bool sesionIniciada;

public:
    // Constructor
    SistemaLogin() : sesionIniciada(false) {
        // Inicializaci�n de usuarios (puedes a�adir m�s si deseas)
        usuarios["admin"] = "admin";
        usuarios["kalid"] = "abc123";
    }

    // M�todo para verificar las credenciales del usuario
    bool verificarCredenciales(string usuario, string contrasena) {
        if (usuarios.find(usuario) != usuarios.end() && usuarios[usuario] == contrasena) {
            sesionIniciada = true;
            return true;
        }
        return false;
    }

    // M�todo para verificar si se ha iniciado sesi�n
    bool sesionActiva() {
        return sesionIniciada;
    }
};

int main() {
    // Inicializaci�n del �rbol binario
    ArbolBinario arbolLibros;

    // Inicializaci�n del sistema de inicio de sesi�n
    SistemaLogin sistemaLogin;

    // Cargar libros desde el archivo al iniciar el programa
    ifstream archivoEntrada("libros.txt");
    if (archivoEntrada.is_open()) {
        while (!archivoEntrada.eof()) {
            Libro libro;
            libro.deserializar(archivoEntrada);
            if (!libro.titulo.empty()) {
                arbolLibros.insertarLibro(libro);
            }
        }
        archivoEntrada.close(); // Cerrar el archivo despu�s de leerlo
    } else {
        cerr << "No se encontr� el archivo de libros." << endl;
    }

    string opcionStr;
    int opcion;
    string usuario, contrasena;

    do {
        cout << "###########################################################################" << endl;
        cout << "# ____      ____  ____  ____   ___      ___   _____      ______    _____  #" << endl;
        cout << "#|_  _|    |_  _||_   ||   _|.'   `.  .'   `.|_   _|   .' ____ \\  / ___ `.#" << endl;
        cout << "#  \\ \\  /\\  / /    | |__| | /  .-.  \\/  .-.  \\ | |     | (___ \\_||_/___) |#" << endl;
        cout << "#   \\ \\/  \\/ /     |  __  | | |   | || |   | | | |   _  _.____`.   /  __.'#" << endl;
        cout << "#    \\  /\\  /     _| |  | |_\\  `-'  /\\  `-'  /_| |__/ || \\____) |  |_|    #" << endl;
        cout << "#     \\/  \\/     |____||____|`.___.'  `.___.'|________| \\______.'  (_)    #" << endl;
        cout << "###########################################################################" << endl;
        cout << "" << endl;
        cout << "1. Iniciar sesion (ADMIN)" << endl;
        cout << "2. Buscar libro por titulo" << endl;
        cout << "3. Buscar libro por autor" << endl;
        cout << "4. Buscar libro por genero" << endl;
        cout << "5. Buscar libro por ISBN" << endl;
        cout << "6. Agregar libro" << endl;
        cout << "7. Salir" << endl;
        cout << "============ v. 1.0.3 ============" << endl;
        cout << "Ingrese su opcion: ";
        getline(cin, opcionStr);

        // Convertir la entrada a min�sculas para manejar entradas mixtas (may�sculas/min�sculas)
        transform(opcionStr.begin(), opcionStr.end(), opcionStr.begin(), ::tolower);

        if (opcionStr == "1" || opcionStr == "iniciar sesion") {
            opcion = 1;
        } else if (opcionStr == "2" || opcionStr == "buscar libro por titulo") {
            opcion = 2;
        } else if (opcionStr == "3" || opcionStr == "buscar libro por autor") {
            opcion = 3;
        } else if (opcionStr == "4" || opcionStr == "buscar libro por genero") {
            opcion = 4;
        } else if (opcionStr == "5" || opcionStr == "buscar libro por isbn") {
            opcion = 5;
        } else if (opcionStr == "6" || opcionStr == "agregar libro") {
            opcion = 6;
        } else if (opcionStr == "7" || opcionStr == "salir") {
            opcion = 7;
        } else {
            opcion = 0; // Opci�n inv�lida
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese su usuario: ";
                getline(cin, usuario);
                cout << "Ingrese su contrasena: ";
                getline(cin, contrasena);
                if (sistemaLogin.verificarCredenciales(usuario, contrasena)) {
                    cout << "Inicio de sesi�n exitoso. Ahora puedes buscar y agregar libros." << endl;
                } else {
                    cout << "Credenciales incorrectas. Intente de nuevo." << endl;
                }
                break;
            case 2:
                if (sistemaLogin.sesionActiva()) {
                    string titulo;
                    cout << "Ingrese el titulo del libro a buscar: ";
                    getline(cin, titulo);
                    NodoArbol* libroEncontrado = arbolLibros.buscarLibroPorTitulo(titulo);
                    if (libroEncontrado != nullptr) {
                        cout << "Libro encontrado:" << endl;
                        cout << "T�tulo: " << libroEncontrado->libro.titulo << endl;
                        cout << "Autor: " << libroEncontrado->libro.autor << endl;
                        cout << "G�nero: " << libroEncontrado->libro.genero << endl;
                        cout << "ISBN: " << libroEncontrado->libro.ISBN << endl;
                    } else {
                        cout << "Libro no encontrado." << endl;
                    }
                } else {
                    cout << "Debe iniciar sesi�n para buscar un libro." << endl;
                }
                break;
            case 3:
                if (sistemaLogin.sesionActiva()) {
                    string autor;
                    cout << "Ingrese el autor del libro a buscar: ";
                    getline(cin, autor);
                    NodoArbol* libroEncontrado = arbolLibros.buscarLibroPorAutor(autor);
                    if (libroEncontrado != nullptr) {
                        cout << "Libro encontrado:" << endl;
                        cout << "T�tulo: " << libroEncontrado->libro.titulo << endl;
                        cout << "Autor: " << libroEncontrado->libro.autor << endl;
                        cout << "G�nero: " << libroEncontrado->libro.genero << endl;
                        cout << "ISBN: " << libroEncontrado->libro.ISBN << endl;
                    } else {
                        cout << "Libro no encontrado." << endl;
                    }
                } else {
                    cout << "Debe iniciar sesi�n para buscar un libro." << endl;
                }
                break;
            case 4:
                if (sistemaLogin.sesionActiva()) {
                    string genero;
                    cout << "Ingrese el genero del libro a buscar: ";
                    getline(cin, genero);
                    NodoArbol* libroEncontrado = arbolLibros.buscarLibroPorGenero(genero);
                    if (libroEncontrado != nullptr) {
                        cout << "Libro encontrado:" << endl;
                        cout << "T�tulo: " << libroEncontrado->libro.titulo << endl;
                        cout << "Autor: " << libroEncontrado->libro.autor << endl;
                        cout << "G�nero: " << libroEncontrado->libro.genero << endl;
                        cout << "ISBN: " << libroEncontrado->libro.ISBN << endl;
                    } else {
                        cout << "Libro no encontrado." << endl;
                    }
                } else {
                    cout << "Debe iniciar sesi�n para buscar un libro." << endl;
                }
                break;
            case 5:
                if (sistemaLogin.sesionActiva()) {
                    string ISBN;
                    cout << "Ingrese el ISBN del libro a buscar: ";
                    getline(cin, ISBN);
                    NodoArbol* libroEncontrado = arbolLibros.buscarLibroPorISBN(ISBN);
                    if (libroEncontrado != nullptr) {
                        cout << "Libro encontrado:" << endl;
                        cout << "T�tulo: " << libroEncontrado->libro.titulo << endl;
                        cout << "Autor: " << libroEncontrado->libro.autor << endl;
                        cout << "G�nero: " << libroEncontrado->libro.genero << endl;
                        cout << "ISBN: " << libroEncontrado->libro.ISBN << endl;
                    } else {
                        cout << "Libro no encontrado." << endl;
                    }
                } else {
                    cout << "Debe iniciar sesi�n para buscar un libro." << endl;
                }
                break;
            case 6:
                if (sistemaLogin.sesionActiva()) {
                    // Aqu� puedes implementar la l�gica para agregar un libro
                    Libro nuevoLibro;
                    cout << "Ingrese el titulo del libro: ";
                    getline(cin, nuevoLibro.titulo);
                    cout << "Ingrese el autor del libro: ";
                    getline(cin, nuevoLibro.autor);
                    cout << "Ingrese el genero del libro: ";
                    getline(cin, nuevoLibro.genero);
                    cout << "Ingrese el ISBN del libro: ";
                    getline(cin, nuevoLibro.ISBN);
                    arbolLibros.insertarLibro(nuevoLibro);
                    cout << "Libro agregado exitosamente." << endl;
                } else {
                    cout << "Debe iniciar sesi�n para agregar un libro." << endl;
                }
                break;
            case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, ingrese una opci�n valida." << endl;
        }
    } while (opcion != 7);

    cout << "Presione Enter para salir...";
    cin.get(); // Espera a que el usuario presione Enter antes de salir

    return 0;
}

