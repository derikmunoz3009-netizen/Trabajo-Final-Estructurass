MODULO PERSONA 2 - PISTAS Y TESTIGOS

Este modulo cumple con la parte de Persona 2 del proyecto:

1. Clase Pista.
2. Clase Testigo.
3. Pila de pistas con stack<Pista>.
4. Cola de testigos con queue<Testigo>.
5. Generacion aleatoria de 10 pistas y 5 testigos.
6. Recoger pista cuando el detective cae en su posicion.
7. Recoger testigo cuando el detective pasa por su posicion.
8. Mostrar pistas con la tecla T.
9. Usar ultima pista con la tecla X.
10. Interrogar testigo con la tecla I.

ARCHIVOS
- Posicion.h / Posicion.cpp
- Pista.h / Pista.cpp
- Testigo.h / Testigo.cpp
- IAccionesCiudad.h
- GestorPistasTestigos.h / GestorPistasTestigos.cpp
- main_demo.cpp

COMO COMPILAR LA DEMO

g++ main_demo.cpp Posicion.cpp Pista.cpp Testigo.cpp GestorPistasTestigos.cpp -o persona2
./persona2

COMO INTEGRARLO CON EL PROYECTO

La Persona 1 debe hacer que su clase Ciudad herede de IAccionesCiudad e implemente:

void taparMapa();
void eliminarCallejonesAleatorios(int cantidad);
void reubicarPistaAleatoriamente(char tipoPista);
void teletransportarDetective();

Cuando el detective se mueva, Juego puede llamar:

gestor.recogerPista(posicionActual);
gestor.recogerTestigo(posicionActual);

Cuando el usuario digite T:

gestor.mostrarPistas();

Cuando el usuario digite X:

gestor.usarUltimaPista(puntaje, ciudad);

Cuando el usuario digite I:

gestor.interrogarTestigo();

NOTA PARA LA SUSTENTACION

La pila funciona con LIFO: la ultima pista recogida es la primera que se puede usar.
La cola funciona con FIFO: el primer testigo encontrado es el primero en ser interrogado.
