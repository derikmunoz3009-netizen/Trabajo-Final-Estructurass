cmake_minimum_required(VERSION 4.1)
project(Trabajo_Final_Estructurass)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Trabajo_Final_Estructurass
        Sospechoso.cpp
        Sospechoso.h
        HashSospechosos.cpp
        HashSospechosos.h
        ABBPuntajes.cpp
        ABBPuntajes.h
        Faseacusacion.cpp
        Faseacusacion.h)
