cmake_minimum_required(VERSION 3.10)
project(TP3 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(TP5
        file.c
        file.h
        filePrioritesMin.c
        filePrioritesMin.h
        graphe.c
        graphe.h
        liste.c
        liste.h
        ListeAdj.c
        ListeAdj.h
        main.c
        main.c genetique.c genetique.h)
