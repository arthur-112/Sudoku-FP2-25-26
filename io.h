/*
    Módulo que centraliza todo lo que tiene que ver con la entrada / salida
    - Apertura de fichero, lectura o escritura
    - Escribir todo lo que tiene que ver con el juego (todos los cout van aquí)
    - Leer todo lo que tiene que ver con el juego (todos los cin van aquí)
    - En particular, aquí se implementa TODA la interacción con el usuario / jugador

    En la interfaz solo aparece lo que se usa desde el módulo principal main
    (el único que se comunica con este módulo, pidiéndole cosas relacionados con la E/S)
*/

#pragma once

#include "juego.h"

// Decisión del jugador
enum Accion { INDETERMINADA, ASIGNAR, QUITAR, POSIBLES, AUTO, REINICIAR, SALIR };

struct Eleccion {
    Accion accion = INDETERMINADA; // sin acción válida elegida aún
    Posicion casilla;
    int valor = 0; // solo se cambia cuando se elige poner un valor en una casilla
};

void mostrar_cabecera();
void mostrar_juego(Juego const& juego);
void mostrar_resultado(Juego const& juego);

void mostrar_valores_posibles(Juego const& juego, Posibles posible, int n);
void mostrar_bloqueadas(Juego const& juego);

Eleccion elegir(Juego const& juego);

Juego cargar_juego();

void mostrar_error(std::string const& mensaje);