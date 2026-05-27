# Proyecto: El Caso del Detective
### Estructuras de Datos — Mayo 2026

---

## Descripción general
Es un juego de investigación criminal donde somos un detective que debe moverse por el mapa e ir recolectando pistas ocultas, interrogar testigos y acusar al sospechoso correcto.

---

## Estructura de los archivos

```
proyecto/
├── main.cpp
├── Pista.h / Pista.cpp ✓
├── Sospechoso.h / Sospechoso.cpp ✓
├── Detective.h / Detective.cpp ✓
├── Ubicacion.h / Ubicacion.cpp ✓
├── Pila.h / Pila.cpp ✓
├── Cola.h / Cola.cpp ✓
├── TablaHash.h / TablaHash.cpp ✓
├── ABB.h / ABB.cpp ✓
├── Mapa.h / Mapa.cpp ✓
├── Juego.h / Juego.cpp ✓
└── README.md ✓
```

---

## Estructuras de datos utilizadas
| Estructura | Archivo | En que lo usamos                                                                 |
|---|---|----------------------------------------------------------------------------------|
| Lista múltiplemente enlazada | `Mapa` | El tablero de la ciudad (cada celda conectada arriba, abajo, izquierda, derecha) |
| Pila | `Pila` | Las pistas recogidas por el detective (LIFO)                                     |
| Cola | `Cola` | Declaraciones de testigos por procesar (FIFO)                                    |
| Tabla Hash | `TablaHash` | Los 8 sospechosos del caso con búsqueda por nombre                               |
| ABB | `ABB` | Historial de puntajes de detectives, ordenado de menor a mayor                   |

---

## Orden de implementación
Fuimos creando las clases de manera de adentro hacia afuera, primero las más simples y luego las que van a depender de ellas.

1. `Pista` → la más simple y q no depende de nadie
2. `Sospechoso` → datos del sospechoso y sus atributos
3. `Detective` → datos del jugador
4. `Ubicacion` → una celda del mapa
5. `Pila` → para apilar las pistas recogidas
6. `Cola` → para las declaraciones de testigos
7. `TablaHash` → para gestionar los sospechosos
8. `ABB` → para el historial de puntajes
9. `Mapa` → lo más complejo mk une todo el tablero
10. `Juego` → la lógica principal que une todas las clases (lo mas largo)
11. `main` → punto de entrada, solo arranca el juego