#include <iostream>
#include "Juego.h"
#include "memoryleaks.h"
#include "io.h"

using namespace std;

void jugar(Juego& juego) {
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
		10
	} while (!juego.terminado() && eleccion.accion != SALIR);
	mostrar_resultado(juego);
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	mostrar_cabecera();
	ListaSudokus lista_partidas, lista_sudokus; // listas ordenadas de sudokus
	cargar_lista_partidas(lista_partidas);
	cargar_lista_sudokus(lista_sudokus);
	TipoPartida tipo = NINGUNA;
	Juego juego;
	do {
		tipo = partida(); // el usuario elige abandonar, continuar o nueva
		int s = 0;
		if (tipo != ABANDONAR) {
			switch (tipo) {
			case NUEVA:
				s = elige_sudoku(lista_sudokus); // elige un sudoku nuevo
				juego = lista_sudokus[s]; // asignación
				break;
			case ANTIGUA:
				if (lista_partidas.num_elems() == 0) {
					mostrar_error("No dispones de partidas empezadas!Elige un sudoku nuevo");
					tipo = NUEVA; // cambia tipo
					s = elige_sudoku(lista_sudokus);
					juego = lista_sudokus[s];
				}
				else {
					s = elige_sudoku(lista_partidas); // elige partida comenzada
					juego = lista_partidas[s]; // continúa partida
				}
				break;
			default:
				break;
			}
			mostrar_juego(juego);
			jugar(juego); // esencialmente el main de la versión 1
				if (juego.numero_vacias() > 0) {
					lista_partidas.insertar(juego);
					cout << "Partida guardada en la lista de pendientes." << endl;
				}
				else {
					cout << "¡Felicidades! Has completado el Sudoku." << endl;
				}
		}
	} while (tipo != ABANDONAR);
	guardar_lista_partidas(lista_partidas);
	return 0;
}