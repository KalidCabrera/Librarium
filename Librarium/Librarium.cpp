#include <iostream>
#include <list>
#include <string>

// Clase para representar un libro
class Libro {
public:
    std::string titulo;
    std::string autor;

    // Constructor para crear un libro
    Libro(const std::string& t, const std::string& a)
        : titulo(t), autor(a) {}
};

// Clase para gestionar el catálogo de libros
class Catalogo {
private:
    std::list<Libro> libros;

public:
    // Método para agregar un libro al catálogo
    void agregarLibro(const std::string& titulo, const std::string& autor) {
        libros.emplace_back(titulo, autor);
        std::cout << "Libro agregado exitosamente.\n";
    }

    // Método para buscar libros por título o autor
    bool buscarLibro(const std::string& query) const {
        bool encontrado = false;

        for (const auto& libro : libros) {
            if (libro.titulo == query || libro.autor == query) {
                std::cout << "Título: " << libro.titulo << ", Autor: " << libro.autor << std::endl;
                encontrado = true;
            }
        }

        return encontrado;
    }
};

int main() {
    Catalogo catalogo;
    bool continuarPrograma = true;

    while (continuarPrograma) {
        // Mostrar opciones al usuario
        std::cout << "\nMenu:\n";
        std::cout << "1. Agregar un libro\n";
        std::cout << "2. Buscar un libro\n";
        std::cout << "3. Salir\n";
        std::cout << "Elige una opcion (1-3): ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(); // Ignorar el resto de la línea de entrada

        if (opcion == 1) {
            // Agregar un libro
            std::string titulo, autor;
            std::cout << "Ingrese el título del libro: ";
            std::getline(std::cin, titulo);
            std::cout << "Ingrese el autor del libro: ";
            std::getline(std::cin, autor);
            catalogo.agregarLibro(titulo, autor);

        } else if (opcion == 2) {
            // Buscar un libro
            std::string query;
            std::cout << "Ingrese el título o autor del libro que desea buscar: ";
            std::getline(std::cin, query);

            bool encontrado = catalogo.buscarLibro(query);

            if (!encontrado) {
                std::cout << "No se encontró ningún libro con el título o autor: " << query << std::endl;

                // Preguntar si el usuario quiere agregar un libro
                std::cout << "¿Desea agregar un libro? (s/n): ";
                std::string respuesta;
                std::getline(std::cin, respuesta);

                if (respuesta == "s" || respuesta == "S") {
                    std::string nuevoTitulo, nuevoAutor;
                    std::cout << "Ingrese el título del libro: ";
                    std::getline(std::cin, nuevoTitulo);
                    std::cout << "Ingrese el autor del libro: ";
                    std::getline(std::cin, nuevoAutor);
                    catalogo.agregarLibro(nuevoTitulo, nuevoAutor);
                }
            }

        } else if (opcion == 3) {
            // Salir del programa
            continuarPrograma = false;
        } else {
            std::cout << "Opción inválida, por favor intente de nuevo.\n";
        }
    }

    std::cout << "Programa terminado. Gracias por usar el catálogo de libros.\n";

    return 0;
}