#include "Sospechoso.h"   // Incluye el header con la definición de la clase
#include <iostream>       // Para usar cout (imprimir en pantalla)

using namespace std;      // Para no escribir std:: en cada línea

// ============================================================
// CONSTRUCTOR
// Se ejecuta cuando haces: Sospechoso s("Carlos", atributos);
// ============================================================
Sospechoso::Sospechoso(string nombre, vector<string> atributos) {
    this->nombre = nombre;         // Guarda el nombre recibido
    this->atributos = atributos;   // Guarda la lista de atributos recibida
    this->esCulpable = false;      // Por defecto no es culpable (se asigna después al azar)
    // atributosRevelados empieza vacío automáticamente (vector vacío)
}

// ============================================================
// GETTERS - Métodos para leer datos privados
// ============================================================

string Sospechoso::getNombre() {
    return nombre;   // Devuelve el nombre del sospechoso
}

vector<string> Sospechoso::getAtributos() {
    return atributos;   // Devuelve todos los atributos (incluidos los no revelados)
}

vector<string> Sospechoso::getAtributosRevelados() {
    return atributosRevelados;   // Devuelve solo los atributos que el jugador ya vio
}

bool Sospechoso::getEsCulpable() {
    return esCulpable;   // Devuelve true si es el culpable, false si no
}

// ============================================================
// SETTER - Metodo para asignar si es culpable
// ============================================================

void Sospechoso::setEsCulpable(bool valor) {
    esCulpable = valor;   // Cambia el valor de esCulpable (true o false)
}

// ============================================================
// revelarSiguienteAtributo
// Toma el siguiente atributo no revelado y lo pasa a "revelados"
// Se llama cada vez que el detective recoge una pista
// ============================================================
void Sospechoso::revelarSiguienteAtributo() {
    // Cuenta cuántos atributos ya fueron revelados
    int yaRevelados = atributosRevelados.size();

    // Verifica que todavía queden atributos por revelar
    if (yaRevelados < (int)atributos.size()) {
        // Toma el siguiente atributo (el que sigue según el índice)
        string nuevoAtributo = atributos[yaRevelados];

        // Lo agrega a la lista de revelados
        atributosRevelados.push_back(nuevoAtributo);

        // Muestra un mensaje al jugador
        cout << "🔍 Nuevo dato del culpable revelado: " << nuevoAtributo << endl;
    }
    // Si ya se revelaron todos los atributos, no hace nada
}

// ============================================================
// mostrarInfo
// Imprime el nombre y los atributos ya revelados del sospechoso
// Se usa cuando el jugador presiona "S"
// ============================================================
void Sospechoso::mostrarInfo() {
    cout << " " << nombre << " | atributos confirmados: ";   // Imprime el nombre

    // Verifica si ya se reveló algún atributo
    if (atributosRevelados.empty()) {
        cout << "-";   // Si no hay revelados, muestra un guión
    } else {
        // Recorre cada atributo revelado e imprime uno por uno
        for (int i = 0; i < (int)atributosRevelados.size(); i++) {
            cout << atributosRevelados[i];           // Imprime el atributo
            if (i < (int)atributosRevelados.size() - 1) {
                cout << ", ";   // Pone coma entre atributos, menos en el último
            }
        }
    }
    cout << endl;   // Salto de línea al final
}