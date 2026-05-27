#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H

#include <string>
#include <vector>
using namespace std;

class Sospechoso {
private:
    string nombre;
    vector<string> atributos;
    vector<bool> atributosRevelados;
    bool esCulpable;

public:
    Sospechoso();
    Sospechoso(string nombre, vector<string> atributos);

    string getNombre() const;
    bool getEsCulpable() const;
    void marcarCulpable();

    void revelarSiguienteAtributo();
    void mostrar() const;
    void mostrarTodo() const;
};

#endif
