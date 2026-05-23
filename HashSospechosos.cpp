#include "HashSospechosos.h"   // Incluye el header de esta clase
#include <iostream>             // Para cout (imprimir)
#include <algorithm>            // Para transform (convertir a minúsculas)
#include <cstdlib>              // Para rand() y srand()
#include <ctime>                // Para time() (semilla aleatoria)

using namespace std;

// ============================================================
// FUNCIÓN HASH
// Convierte el nombre en un número entre 0 y TAMANO-1
// Este número es el "cajón" donde se guarda el sospechoso
// ============================================================
int HashSospechosos::funcionHash(string nombre) {
    int suma = 0;   // Acumulador de valores

    // Recorre cada letra del nombre
    for (int i = 0; i < (int)nombre.size(); i++) {
        // Suma el valor ASCII de cada letra multiplicado por su posición+1
        // Esto distribuye mejor los nombres en la tabla
        suma += (int)nombre[i] * (i + 1);
    }

    // Devuelve el residuo de dividir entre el tamaño (esto da índice válido)
    return suma % TAMANO;
}

// ============================================================
// CONSTRUCTOR
// Crea la tabla con TAMANO posiciones vacías
// ============================================================
HashSospechosos::HashSospechosos() {
    // Redimensiona la tabla para que tenga TAMANO posiciones
    // Cada posición es un vector vacío de sospechosos
    tabla.resize(TAMANO);

    indiceCulpable = -1;   // -1 significa "aún no se ha asignado culpable"

    srand(time(nullptr));   // Inicializa el generador de números aleatorios con la hora actual
}

// ============================================================
// inicializarSospechosos
// Crea 8 sospechosos desde una lista predefinida y elige 1 culpable al azar
// ============================================================
void HashSospechosos::inicializarSospechosos() {

    // Lista de posibles sospechosos con sus atributos
    // Cada entrada es: {nombre, {atributo1, atributo2, atributo3, atributo4, atributo5}}
    vector<pair<string, vector<string>>> candidatos = {
        {"Carlos",   {"zurdo", "alto", "cabello negro", "ojos café", "cicatriz en mejilla"}},
        {"Diana",    {"alta", "cabello rubio", "ojos verdes", "diestra", "lunares en cuello"}},
        {"Eduardo",  {"bajo", "robusto", "calvo", "ojos azules", "tatuaje en brazo"}},
        {"Fernanda", {"alta", "cabello rojo", "ojos miel", "zurda", "pecas en nariz"}},
        {"Gonzalo",  {"delgado", "mediano", "bigote", "ojos negros", "usa gafas"}},
        {"Hilda",    {"alta", "cabello castaño", "ojos grises", "diestra", "voz ronca"}},
        {"Ivan",     {"corpulento", "bajo", "cabello canoso", "cicatriz en mano", "cojea al caminar"}},
        {"Julia",    {"delgada", "alta", "cabello negro", "tatuaje en cuello", "uñas pintadas de negro"}},
        {"Kevin",    {"mediano", "pelirrojo", "pecoso", "ojos verdes", "lleva siempre sombrero"}},
        {"Laura",    {"cabello corto", "baja", "robusta", "ojos azules", "habla muy rápido"}}
    };

    // Mezcla la lista para que cada partida use sospechosos distintos
    // Algoritmo de mezcla Fisher-Yates
    for (int i = candidatos.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);           // Índice aleatorio entre 0 e i
        swap(candidatos[i], candidatos[j]); // Intercambia los elementos
    }

    // Toma solo los primeros 8 candidatos de la lista mezclada
    int culpableIndice = rand() % 8;   // Elige al azar cuál de los 8 será el culpable

    for (int i = 0; i < 8; i++) {
        // Crea el sospechoso con nombre y atributos
        Sospechoso s(candidatos[i].first, candidatos[i].second);

        // Si este es el índice del culpable, lo marca
        if (i == culpableIndice) {
            s.setEsCulpable(true);
        }

        // Lo inserta en la tabla hash
        insertar(s);
    }

    cout << "✅ 8 sospechosos cargados en la Tabla Hash." << endl;
}

// ============================================================
// insertar
// Agrega un sospechoso a la tabla hash en la posición correcta
// ============================================================
void HashSospechosos::insertar(Sospechoso s) {
    int indice = funcionHash(s.getNombre());   // Calcula el índice con la función hash

    // Agrega el sospechoso al vector de esa posición (por si hay colisión)
    tabla[indice].push_back(s);
}

// ============================================================
// buscar
// Busca un sospechoso por nombre y devuelve un puntero a él
// Complejidad O(1) promedio gracias a la función hash
// ============================================================
Sospechoso* HashSospechosos::buscar(string nombre) {
    int indice = funcionHash(nombre);   // Calcula directamente el índice (O(1))

    // Recorre el vector en esa posición (normalmente solo hay 1 elemento)
    for (int i = 0; i < (int)tabla[indice].size(); i++) {
        // Compara el nombre buscado con el nombre guardado
        if (tabla[indice][i].getNombre() == nombre) {
            return &tabla[indice][i];   // Devuelve puntero al sospechoso encontrado
        }
    }

    return nullptr;   // Si no encontró nada, devuelve nullptr (puntero vacío)
}

// ============================================================
// mostrarTodos
// Imprime todos los sospechosos con sus atributos revelados
// Se usa cuando el jugador presiona "S"
// ============================================================
void HashSospechosos::mostrarTodos() {
    cout << "\n╔══════════════════════════════════════╗" << endl;
    cout << "║     SOSPECHOSOS DEL CASO             ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;

    // Recorre todas las posiciones de la tabla
    for (int i = 0; i < TAMANO; i++) {
        // Recorre todos los sospechosos en esa posición
        for (int j = 0; j < (int)tabla[i].size(); j++) {
            tabla[i][j].mostrarInfo();   // Llama al método de impresión de cada sospechoso
        }
    }
    cout << endl;
}

// ============================================================
// mostrarNombres
// Imprime solo los nombres de los sospechosos en una línea
// Se usa en la fase de acusación
// ============================================================
void HashSospechosos::mostrarNombres() {
    cout << "Sospechosos disponibles: ";

    bool primero = true;   // Flag para no poner coma antes del primer nombre

    // Recorre toda la tabla
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < (int)tabla[i].size(); j++) {
            if (!primero) cout << ", ";           // Coma separadora entre nombres
            cout << tabla[i][j].getNombre();      // Imprime el nombre
            primero = false;                       // Ya pasó el primero
        }
    }
    cout << endl;
}

// ============================================================
// revelarAtributoCulpable
// Llama a revelarSiguienteAtributo() sobre el sospechoso culpable
// Se llama cada vez que el detective recoge una pista o interroga testigo
// ============================================================
void HashSospechosos::revelarAtributoCulpable() {
    // Recorre toda la tabla buscando al culpable
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < (int)tabla[i].size(); j++) {
            if (tabla[i][j].getEsCulpable()) {          // Si este es el culpable...
                tabla[i][j].revelarSiguienteAtributo();  // Revela su siguiente atributo
                return;   // Sale inmediatamente (solo hay un culpable)
            }
        }
    }
}

// ============================================================
// getNombreCulpable
// Devuelve el nombre del culpable para comparar con la acusación
// ============================================================
string HashSospechosos::getNombreCulpable() {
    // Recorre la tabla buscando al culpable
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < (int)tabla[i].size(); j++) {
            if (tabla[i][j].getEsCulpable()) {      // Si encontró al culpable...
                return tabla[i][j].getNombre();      // Devuelve su nombre
            }
        }
    }
    return "";   // No debería llegar aquí, pero por seguridad devuelve vacío
}

// ============================================================
// obtenerTodos
// Devuelve una lista con punteros a todos los sospechosos
// Útil para iterar desde Juego.cpp
// ============================================================
vector<Sospechoso*> HashSospechosos::obtenerTodos() {
    vector<Sospechoso*> lista;   // Lista vacía de punteros

    // Recorre toda la tabla
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < (int)tabla[i].size(); j++) {
            lista.push_back(&tabla[i][j]);   // Agrega el puntero a cada sospechoso
        }
    }

    return lista;   // Devuelve la lista completa
}