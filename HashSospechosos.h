#ifndef HASHSOSPECHOSOS_H   // Protección contra inclusión doble
#define HASHSOSPECHOSOS_H

#include "Sospechoso.h"   // Necesitamos la clase Sospechoso
#include <vector>          // Para usar vector como estructura base del hash
#include <string>          // Para usar string

using namespace std;

// ============================================================
// CLASE HashSospechosos
// Tabla Hash que guarda 8 sospechosos
// Permite buscar un sospechoso por nombre en O(1) promedio
// ============================================================
class HashSospechosos {

private:
    // Tamaño de la tabla hash (número de "cajones" o buckets)
    static const int TAMANO = 17;   // Primo cercano a 8, mejora distribución del hash

    // La tabla es un vector de vectores (encadenamiento para colisiones)
    // Cada posición puede tener varios sospechosos si hay colisión
    vector<vector<Sospechoso>> tabla;

    // Índice del culpable (posición en la tabla original de 8)
    int indiceCulpable;

    // Función hash: convierte un nombre en un índice de la tabla
    int funcionHash(string nombre);

public:
    // Constructor: inicializa la tabla vacía
    HashSospechosos();

    // Inicializa los 8 sospechosos con datos predefinidos al azar
    void inicializarSospechosos();

    // Inserta un sospechoso en la tabla
    void insertar(Sospechoso s);

    // Busca un sospechoso por nombre y devuelve puntero a él (nullptr si no existe)
    Sospechoso* buscar(string nombre);

    // Muestra todos los sospechosos con sus atributos revelados
    void mostrarTodos();

    // Muestra solo los nombres (para la fase de acusación)
    void mostrarNombres();

    // Revela un atributo del culpable (se llama al recoger una pista o interrogar testigo)
    void revelarAtributoCulpable();

    // Devuelve el nombre del culpable (para verificar la acusación)
    string getNombreCulpable();

    // Devuelve todos los sospechosos en una lista plana (para iterarlos fácilmente)
    vector<Sospechoso*> obtenerTodos();
};

#endif