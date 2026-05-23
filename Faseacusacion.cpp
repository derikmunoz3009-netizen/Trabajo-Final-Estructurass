#include "FaseAcusacion.h"   // Incluye el header de esta clase
#include <iostream>           // Para cout y cin (imprimir y leer input)

using namespace std;

// ============================================================
// ejecutar (estático)
// Toda la lógica de la fase de acusación
// ============================================================
int FaseAcusacion::ejecutar(HashSospechosos& hash, ABBPuntajes& abb,
                             string nombreDetective, int puntajeActual) {

    // Mensaje de inicio de la fase
    cout << "\n╔══════════════════════════════════════════════╗" << endl;
    cout << "║  ¡Has recolectado las 10 pistas!             ║" << endl;
    cout << "║  Es momento de hacer tu acusación...         ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;

    // Muestra la tabla hash completa con todos los atributos revelados
    hash.mostrarTodos();

    // Muestra solo los nombres disponibles para que el usuario elija
    hash.mostrarNombres();

    // Pide al usuario que escriba el nombre del sospechoso a acusar
    cout << "\n¿A quién acusas? > ";
    string acusado;
    cin >> acusado;   // Lee el nombre ingresado por el usuario

    // ============================================================
    // BÚSQUEDA EN LA TABLA HASH - O(1) PROMEDIO
    // Este es el momento que pide el proyecto: mostrar que la
    // búsqueda es O(1) gracias al hash
    // ============================================================
    cout << "\n🔎 Buscando '" << acusado << "' en la Tabla Hash..." << endl;
    Sospechoso* encontrado = hash.buscar(acusado);   // Búsqueda directa por hash

    // Verifica si el nombre existe en la tabla
    if (encontrado == nullptr) {
        // El nombre no existe en la tabla hash
        cout << "❌ Ese nombre no está en la lista de sospechosos." << endl;
        cout << "   El caso se cierra como FRACASADO." << endl;

        // Penaliza el puntaje al doble por acusación inválida
        puntajeActual = puntajeActual * 2;
        cout << "⚠️  Puntaje penalizado al doble: " << puntajeActual << " movimientos." << endl;

    } else if (encontrado->getNombre() == hash.getNombreCulpable()) {
        // ¡La acusación es correcta!
        cout << "\n🎉 ¡CASO RESUELTO! " << acusado << " era el/la culpable." << endl;
        cout << "   Puntaje final: " << puntajeActual << " movimientos." << endl;

    } else {
        // El sospechoso existe pero no es el culpable
        cout << "\n❌ Acusación incorrecta. " << acusado << " es inocente." << endl;
        cout << "   El caso se cierra como FRACASADO." << endl;

        // Penaliza el puntaje al doble
        puntajeActual = puntajeActual * 2;
        cout << "⚠️  Puntaje penalizado al doble: " << puntajeActual << " movimientos." << endl;

        // Revela quién era el culpable real
        cout << "   El culpable real era: " << hash.getNombreCulpable() << endl;
    }

    // ============================================================
    // GUARDAR PUNTAJE EN EL ABB
    // Se guarda siempre (caso resuelto o fracasado)
    // El ABB conservará automáticamente el mejor puntaje si ya jugó antes
    // ============================================================
    cout << "\n💾 Guardando puntaje en el ranking histórico..." << endl;
    abb.insertarPuntaje(nombreDetective, puntajeActual);   // Inserta en el árbol

    // Muestra el ranking actualizado
    abb.mostrarRanking();

    return puntajeActual;   // Devuelve el puntaje final (puede haberse penalizado)
}