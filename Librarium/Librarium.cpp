#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

using namespace std;

// Definición de la estructura del libro
struct Libro {
    string titulo;
    string autor;
    string genero;
    string ISBN;
    // Constructor
    Libro(string tit, string aut, string gen, string isbn) : titulo(tit), autor(aut), genero(gen), ISBN(isbn) {}
};

// Nodo para el árbol binario de búsqueda
struct NodoArbol {
    Libro libro;
    NodoArbol* izq;
    NodoArbol* der;
    // Constructor
    NodoArbol(Libro lib) : libro(lib), izq(nullptr), der(nullptr) {}
};

// Clase para el árbol binario de búsqueda
class ArbolBinario {
private:
    NodoArbol* raiz;

    // Función privada para insertar un libro en el árbol
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

    // Función privada para buscar un libro por título
    NodoArbol* buscarPorTitulo(NodoArbol* nodo, string titulo) {
        if (nodo == nullptr || nodo->libro.titulo == titulo) {
            return nodo;
        }
        if (titulo < nodo->libro.titulo) {
            return buscarPorTitulo(nodo->izq, titulo);
        }
        return buscarPorTitulo(nodo->der, titulo);
    }

    // Función privada para buscar un libro por autor
    NodoArbol* buscarPorAutor(NodoArbol* nodo, string autor) {
        if (nodo == nullptr || nodo->libro.autor == autor) {
            return nodo;
        }
        NodoArbol* encontradoIzq = buscarPorAutor(nodo->izq, autor);
        NodoArbol* encontradoDer = buscarPorAutor(nodo->der, autor);
        return (encontradoIzq != nullptr) ? encontradoIzq : encontradoDer;
    }

    // Función privada para buscar un libro por género
    NodoArbol* buscarPorGenero(NodoArbol* nodo, string genero) {
        if (nodo == nullptr || nodo->libro.genero == genero) {
            return nodo;
        }
        NodoArbol* encontradoIzq = buscarPorGenero(nodo->izq, genero);
        NodoArbol* encontradoDer = buscarPorGenero(nodo->der, genero);
        return (encontradoIzq != nullptr) ? encontradoIzq : encontradoDer;
    }

    // Función privada para buscar un libro por ISBN
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
    ArbolBinario() : raiz(nullptr) {}

    // Método público para insertar un libro en el árbol
    void insertarLibro(Libro libro) {
        raiz = insertar(raiz, libro);
    }

    // Método público para buscar un libro por título
    NodoArbol* buscarLibroPorTitulo(string titulo) {
        return buscarPorTitulo(raiz, titulo);
    }

    // Método público para buscar un libro por autor
    NodoArbol* buscarLibroPorAutor(string autor) {
        return buscarPorAutor(raiz, autor);
    }

    // Método público para buscar un libro por género
    NodoArbol* buscarLibroPorGenero(string genero) {
        return buscarPorGenero(raiz, genero);
    }

    // Método público para buscar un libro por ISBN
    NodoArbol* buscarLibroPorISBN(string ISBN) {
        return buscarPorISBN(raiz, ISBN);
    }
};

// Clase para el sistema de inicio de sesión
class SistemaLogin {
private:
    unordered_map<string, string> usuarios; // Almacenamiento de usuarios y contraseñas
    bool sesionIniciada;

public:
    // Constructor
    SistemaLogin() : sesionIniciada(false) {
        // Inicialización de usuarios (puedes añadir más si deseas)
        usuarios["admin"] = "admin";
        usuarios["kalid"] = "abc123";
    }

    // Método para verificar las credenciales del usuario
    bool verificarCredenciales(string usuario, string contrasena) {
        if (usuarios.find(usuario) != usuarios.end() && usuarios[usuario] == contrasena) {
            sesionIniciada = true;
            return true;
        }
        return false;
    }

    // Método para verificar si se ha iniciado sesión
    bool sesionActiva() {
        return sesionIniciada;
    }
};

int main() {
    // Inicialización del árbol binario
    ArbolBinario arbolLibros;

    // Inicialización del sistema de inicio de sesión
    SistemaLogin sistemaLogin;

    int opcion;
    string usuario, contrasena;

    do {
        cout << "============ LIBRARIUM ============" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Buscar libro por titulo" << endl;
        cout << "3. Buscar libro por autor" << endl;
        cout << "4. Buscar libro por genero" << endl;
        cout << "5. Buscar libro por ISBN" << endl;
        if (sistemaLogin.sesionActiva()) {
            cout << "6. Agregar libro" << endl;
            cout << "7. Cerrar sesion" << endl;
        } else {
            cout << "6. Salir" << endl;
        }
        cout << "============ v. 1.0.4 ============" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        // Limpiar el búfer después de leer el valor de opcion
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Ingrese su usuario: ";
                getline(cin, usuario);
                cout << "Ingrese su contrasena: ";
                getline(cin, contrasena);
                if (sistemaLogin.verificarCredenciales(usuario, contrasena)) {
                    cout << "Inicio de sesión exitoso. Ahora puedes agregar y buscar libros." << endl;
                } else {
                    cout << "Credenciales incorrectas. Intente de nuevo." << endl;
                }
                break;
            case 2:
            {
                string tituloBuscar;
                cout << "Ingrese el título del libro a buscar: ";
                getline(cin, tituloBuscar);
                NodoArbol* resultado = arbolLibros.buscarLibroPorTitulo(tituloBuscar);
                if (resultado != nullptr) {
                    cout << "Libro encontrado:" << endl;
                    cout << "Título: " << resultado->libro.titulo << endl;
                    cout << "Autor: " << resultado->libro.autor << endl;
                    cout << "Género: " << resultado->libro.genero << endl;
                    cout << "ISBN: " << resultado->libro.ISBN << endl;
                } else {
                    cout << "Libro no encontrado." << endl;
                }
                break;
            }
            case 3:
            {
                string autorBuscar;
                cout << "Ingrese el autor del libro a buscar: ";
                getline(cin, autorBuscar);
                NodoArbol* resultado = arbolLibros.buscarLibroPorAutor(autorBuscar);
                if (resultado != nullptr) {
                    cout << "Libro encontrado:" << endl;
                    cout << "Título: " << resultado->libro.titulo << endl;
                    cout << "Autor: " << resultado->libro.autor << endl;
                    cout << "Género: " << resultado->libro.genero << endl;
                    cout << "ISBN: " << resultado->libro.ISBN << endl;
                } else {
                    cout << "Libro no encontrado." << endl;
                }
                break;
            }
            case 4:
            {
                string generoBuscar;
                cout << "Ingrese el género del libro a buscar: ";
                getline(cin, generoBuscar);
                NodoArbol* resultado = arbolLibros.buscarLibroPorGenero(generoBuscar);
                if (resultado != nullptr) {
                    cout << "Libro encontrado:" << endl;
                    cout << "Título: " << resultado->libro.titulo << endl;
                    cout << "Autor: " << resultado->libro.autor << endl;
                    cout << "Género: " << resultado->libro.genero << endl;
                    cout << "ISBN: " << resultado->libro.ISBN << endl;
                } else {
                    cout << "Libro no encontrado." << endl;
                }
                break;
            }
            case 5:
            {
                string ISBNBuscar;
                cout << "Ingrese el ISBN del libro a buscar: ";
                getline(cin, ISBNBuscar);
                NodoArbol* resultado = arbolLibros.buscarLibroPorISBN(ISBNBuscar);
                if (resultado != nullptr) {
                    cout << "Libro encontrado:" << endl;
                    cout << "Título: " << resultado->libro.titulo << endl;
                    cout << "Autor: " << resultado->libro.autor << endl;
                    cout << "Género: " << resultado->libro.genero << endl;
                    cout << "ISBN: " << resultado->libro.ISBN << endl;
                } else {
                    cout << "Libro no encontrado." << endl;
                }
                break;
            }
            case 6:
            {
                if (sistemaLogin.sesionActiva()) {
                    string titulo, autor, genero, ISBN;
                    cout << "Ingrese el título del libro: ";
                    getline(cin, titulo);
                    cout << "Ingrese el autor del libro: ";
                    getline(cin, autor);
                    cout << "Ingrese el género del libro: ";
                    getline(cin, genero);
                    cout << "Ingrese el ISBN del libro: ";
                    getline(cin, ISBN);
                    Libro nuevoLibro(titulo, autor, genero, ISBN);
                    arbolLibros.insertarLibro(nuevoLibro);
                    cout << "Libro agregado exitosamente." << endl;
                } else {
                    cout << "Debe iniciar sesión para acceder a esta opción." << endl;
                }
                break;
            }
            case 7:
                cout << "Cerrando sesion..." << endl;
                sistemaLogin = SistemaLogin(); // Reiniciamos el sistema de login
                break;
            default:
                cout << "Opcion no valida. Por favor, ingrese una opción valida." << endl;
        }
    } while (opcion != 7);

    return 0;
}
