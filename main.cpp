#include <iostream>
#include "Juego.h"
#include "io.h"

using namespace std;

int main() {
	mostrar_cabecera();
	Juego juego = cargar_juego();
	mostrar_juego(juego);
	Eleccion eleccion;
	do {
		eleccion = elegir(juego);
		if (eleccion.accion != SALIR) {
			switch (eleccion.accion) {
			case ASIGNAR:
				if (!juego.asignar_valor(eleccion.casilla, eleccion.valor))
					muestra_error("No es posible realizar esa asignacion!");
				break;
			case QUITAR:
				if (!juego.borrar_valor(eleccion.casilla))
					muestra_error("No es posible ese borrado!");
				break;
			case POSIBLES:
				if (juego.esta_libre(eleccion.casilla)) {
					Posibles posibles;
					int n = juego.valores_posibles(eleccion.casilla, posibles);
					mostrar_valores_posibles(juego, posibles, n);
				}
				else
					muestra_error("Esa casilla ya tiene un valor asignado!");
				break;
			case AUTO:
				juego.auto_completar();
				break;
			case REINICIAR:
				juego.reiniciar();
				break;
			default:
				break;
			}
			mostrar_juego(juego);
			if (juego.bloqueado())
				mostrar_bloqueadas(juego);
		}
	} while (!juego.terminado() && eleccion.accion != SALIR);
	mostrar_resultado(juego);

}