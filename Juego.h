#pragma once

#include "Tablero.h"
using Posibles = bool[MAX_DIM + 1];

class Juego {

private:

	Tablero tablero;
	int vacias;

	struct Bloqueos { // casillas sin valores posibles
		int cont = 0;
		Posicion info[MAX_DIM * MAX_DIM];
	};

	// Guarda las posiciones bloqueadas
	Bloqueos bloqueadas;

	bool esta_bloqueada(Posicion posicion) const;
	void insertar_bloqueada(Posicion posicion);

	// Tipo oculto
	struct Valor {
		bool posible;
		int num_casillas_culpables; // > 0 si posible == false; 0 e.o.c.
	};

	// Representa los valores posibles en una determinada posición
	Valor valores[MAX_DIM][MAX_DIM][MAX_DIM + 1];

	void propagar_a_casillas_afectadas(Posicion posicion, int valor, bool poniendo);
	void afectar(Posicion posicion, int valor, bool poniendo);

	void procesar_bloqueos(Posicion posicion, bool poniendo);
	void eliminar_bloqueada(Posicion posicion);

public:
	Juego(int dimension = 0);

	void colocar_valor_inicial(Posicion const& p, int e);

	bool asignar_valor(Posicion const& p, int e);
	bool borrar_valor(Posicion const& p);
	void auto_completar();
	void reiniciar();
	int valores_posibles(Posicion p, Posibles posibles) const;

	bool terminado() const;
	bool bloqueado() const;
	int num_bloqueadas() const;
	Posicion casilla_bloqueada(int i) const;

	// Delegan en Tablero
	bool posicion_valida(Posicion const& p) const;
	bool valor_valido(int v) const;
	int dimension() const;
	int valor(Posicion const& p) const;
	bool es_inicial(Posicion const& p) const;
	bool esta_libre(Posicion const& p) const;
	bool esta_ocupada(Posicion const& p) const;
};