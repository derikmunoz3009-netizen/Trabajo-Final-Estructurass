#include "ABBPuntajes.h"   // Incluye el header de esta clase
#include <iostream>        // Para cout (imprimir en pantalla)

using namespace std;

// ============================================================
// CONSTRUCTOR
// Crea un árbol vacío (la raíz apunta a nullptr)
// ============================================================
ABBPuntajes::ABBPuntajes() {
    raiz = nullptr;   // Árbol vacío al inicio
}

// ============================================================
// DESTRUCTOR
// Libera toda la memoria cuando el objeto es destruido
// ============================================================
ABBPuntajes::~ABBPuntajes() {
    liberarMemoria(raiz);   // Llama al metodo recursivo desde la raíz
}

// ============================================================
// liberarMemoria (privado, recursivo)
// Recorre el árbol y elimina cada nodo para liberar memoria
// ============================================================
void ABBPuntajes::liberarMemoria(NodoABB* nodo) {
    if (nodo == nullptr) return;           // Caso base: si el nodo es vacío, no hace nada
    liberarMemoria(nodo->izquierda);       // Libera el subárbol izquierdo primero
    liberarMemoria(nodo->derecha);         // Libera el subárbol derecho
    delete nodo;                           // Elimina el nodo actual
}

// ============================================================
// insertarRec (privado, recursivo)
// Inserta un detective en el árbol según su PUNTAJE
// Si el detective ya existe, conserva el MENOR puntaje (mejor resultado)
// ============================================================
NodoABB* ABBPuntajes::insertarRec(NodoABB* nodo, string nombre, int puntaje) {

    // Caso base: llegamos a un lugar vacío, creamos el nuevo nodo aquí
    if (nodo == nullptr) {
        return new NodoABB(nombre, puntaje);   // Crea y devuelve el nodo nuevo
    }

    // Si el detective ya existe en el árbol (mismo nombre)
    if (nodo->nombreDetective == nombre) {
        // Solo actualiza si el nuevo puntaje es MENOR (mejor)
        if (puntaje < nodo->puntaje) {
            nodo->puntaje = puntaje;   // Actualiza con el mejor puntaje
            cout << "📊 Puntaje actualizado para " << nombre << ": " << puntaje << endl;
        } else {
            // El puntaje anterior era mejor, no se cambia
            cout << "📊 Se conserva el puntaje anterior de " << nombre << ": " << nodo->puntaje << endl;
        }
        return nodo;   // Devuelve el nodo sin más cambios
    }

    // Si el puntaje nuevo es MENOR al del nodo actual → va al subárbol IZQUIERDO
    if (puntaje < nodo->puntaje) {
        nodo->izquierda = insertarRec(nodo->izquierda, nombre, puntaje);
    }
    // Si el puntaje nuevo es MAYOR o igual → va al subárbol DERECHO
    else {
        nodo->derecha = insertarRec(nodo->derecha, nombre, puntaje);
    }

    return nodo;   // Devuelve el nodo actual (sin cambios en este nivel)
}

// ============================================================
// insertarPuntaje (público)
// Punto de entrada para insertar desde fuera de la clase
// ============================================================
void ABBPuntajes::insertarPuntaje(string nombre, int puntaje) {
    // Llama a la función recursiva empezando desde la raíz
    raiz = insertarRec(raiz, nombre, puntaje);
    cout << "✅ Puntaje de " << nombre << " guardado: " << puntaje << " movimientos." << endl;
}

// ============================================================
// buscarNombreRec (privado, recursivo)
// Busca un detective por nombre (recorre todo el árbol)
// Nota: el árbol está ordenado por puntaje, no por nombre,
// por eso toca revisar ambos lados en cada nodo
// ============================================================
NodoABB* ABBPuntajes::buscarNombreRec(NodoABB* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;   // Caso base: llegamos a un vacío, no encontró

    // Si este nodo tiene el nombre buscado
    if (nodo->nombreDetective == nombre) {
        return nodo;   // Encontró el nodo, lo devuelve
    }

    // Busca en el subárbol izquierdo
    NodoABB* encontrado = buscarNombreRec(nodo->izquierda, nombre);

    // Si lo encontró en el izquierdo, lo devuelve
    if (encontrado != nullptr) return encontrado;

    // Si no, busca en el subárbol derecho y devuelve el resultado
    return buscarNombreRec(nodo->derecha, nombre);
}

// ============================================================
// buscarDetective (público)
// Busca si un detective ya jugó y muestra su mejor puntaje
// ============================================================
void ABBPuntajes::buscarDetective(string nombre) {
    NodoABB* resultado = buscarNombreRec(raiz, nombre);   // Llama a la búsqueda recursiva

    if (resultado != nullptr) {
        // Si encontró el detective, muestra su mejor puntaje
        cout << "🕵️  " << nombre << " ya jugó antes. Su mejor puntaje: "
             << resultado->puntaje << " movimientos." << endl;
    } else {
        // Si no existe en el árbol
        cout << "ℹ️  " << nombre << " no tiene puntaje registrado. ¡Es su primera partida!" << endl;
    }
}

// ============================================================
// mostrarOrdenadoRec (privado, recursivo)
// Recorrido InOrden: izquierda → nodo → derecha
// Esto imprime los nodos de MENOR a MAYOR puntaje automáticamente
// porque el árbol está ordenado por puntaje
// ============================================================
void ABBPuntajes::mostrarOrdenadoRec(NodoABB* nodo) {
    if (nodo == nullptr) return;   // Caso base: nodo vacío, no hace nada

    mostrarOrdenadoRec(nodo->izquierda);   // Primero visita el lado izquierdo (menores)

    // Imprime el detective actual con formato de ranking
    cout << "  🏅 " << nodo->nombreDetective
         << " — " << nodo->puntaje << " movimientos" << endl;

    mostrarOrdenadoRec(nodo->derecha);    // Después visita el lado derecho (mayores)
}

// ============================================================
// mostrarRanking (público)
// Muestra todos los detectives ordenados de menor a mayor puntaje
// ============================================================
void ABBPuntajes::mostrarRanking() {
    cout << "\n╔══════════════════════════════════════╗" << endl;
    cout << "║     RANKING HISTÓRICO DE DETECTIVES  ║" << endl;
    cout << "║   (menor puntaje = mejor desempeño)  ║" << endl;
    cout << "╚══════════════════════════════════════╝" << endl;

    if (raiz == nullptr) {
        // Si el árbol está vacío, no hay puntajes registrados aún
        cout << "  (Aún no hay partidas registradas)" << endl;
    } else {
        mostrarOrdenadoRec(raiz);   // Llama al recorrido InOrden desde la raíz
    }
    cout << endl;
}