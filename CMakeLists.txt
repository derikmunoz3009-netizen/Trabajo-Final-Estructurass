cmake_minimum_required(VERSION 3.20)

project(Persona2_Pistas_Testigos)

set(CMAKE_CXX_STANDARD 17)

add_executable(Persona2_Pistas_Testigos
        main_demo.cpp
        Posicion.cpp
        Pista.cpp
        Testigo.cpp
        GestorPistasTestigos.cpp
        Ciudad.cpp
        Nodo.cpp
        main.cpp
)