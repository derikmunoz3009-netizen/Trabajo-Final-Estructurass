#ifndef SOSPECHOSO_H   // Si este archivo no ha sido incluido antes...
#define SOSPECHOSO_H   // ...marcalo como incluido (evita duplicados)

#include <string>      // Para usar el tipo string (texto)
#include <vector>      // Para usar vector (lista dinámica)

using namespace std;   // Para no escribir std:: antes de string, vector, etc.

// ============================================================
// CLASE Sospechoso
// Representa a cada sospechoso del caso con su nombre y atributos
// ============================================================
class Sospechoso {

private:
    // --- Atributos privados (solo accesibles desde dentro de la clase) ---
    string nombre;                   // Nombre del sospechoso (ej: "Carlos")
    vector<string> atributos;        // Lista de todos sus atributos (ej: "alto", "zurdo", "cabello rojo")
    vector<string> atributosRevelados; // Lista de atributos que el jugador ya descubrió
    bool esCulpable;                 // true si este sospechoso es el culpable real

public:
    // --- Constructor: se llama cuando creas un Sospechoso ---
    Sospechoso(string nombre, vector<string> atributos);

    // --- Getters: métodos para leer los datos privados ---
    string getNombre();                       // Devuelve el nombre
    vector<string> getAtributos();            // Devuelve todos los atributos
    vector<string> getAtributosRevelados();   // Devuelve los atributos ya revelados al jugador
    bool getEsCulpable();                     // Devuelve si es culpable

    // --- Setters: métodos para modificar datos ---
    void setEsCulpable(bool valor);           // Marca o desmarca como culpable

    // --- Métodos de lógica ---
    void revelarSiguienteAtributo();          // Revela al jugador el siguiente atributo oculto
    void mostrarInfo();                       // Imprime nombre y atributos revelados en pantalla
};

#endif // Fin del bloque de protección