#ifndef PISTA_H
#define PISTA_H

#include <string>
using namespace std;

//Lista de nombres para usar los datos mas breve, el compilador los convierte en números, pa eso esta el enum
enum TipoPista { HUELLA, COARTADA, TESTIMONIO, PRUEBA_FORENSE };

class Pista {
private:
    TipoPista tipo;  //se guarda que tipo de pista es en la variable "tipo" xd
    bool recogida;   // pa ver si la pista ya fue recogida

public:
    Pista();                // pista vacia
    Pista(TipoPista tipo);  // aquí se recibe el tipo de pista que queremos crear y es el que usamos de verdad en el juego

    TipoPista getTipo() const; //metodo que nos retorna el enum del tipo, para saber que tipo de pista va a utilizar
    bool isRecogida() const;   //ver si la pista ya fue usada
    void recoger();             //cambia recogida de false a true

    string getTipoString() const; //esots dos nos devuelven el nombre completo de los datos
    string getSimbolo() const;    //solo devuelven la letra inicial de cada dato para cuando lo mostramos en la terminal
};

#endif
