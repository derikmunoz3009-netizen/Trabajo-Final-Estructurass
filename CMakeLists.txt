cmake_minimum_required(VERSION 3.10)
project(Detective_Case)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente
set(SOURCES
        main.cpp
        Nodo.cpp
        Ciudad.cpp
        Posicion.cpp
        Pista.cpp
        Testigo.cpp
        Sospechoso.cpp
        HashSospechosos.cpp
        ABBPuntajes.cpp
        FaseAcusacion.cpp
        GestorPistasTestigos.cpp
)

# Crear el ejecutable principal
add_executable(Detective_Case ${SOURCES})

# Incluir directorios
target_include_directories(Detective_Case PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})