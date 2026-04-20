#pragma once

#include "Casilla.h"

const int MAX_DIM = 9;
struct Posicion {
	int f = -1;
	int c = -1;
};

class Tablero {
private:

	int dim;
	Casilla tab[MAX_DIM][MAX_DIM];


public:

	Tablero(int d = MAX_DIM);

	void colocar_valor_inicial(Posicion posicion, int valor);
	void asignar_valor(Posicion posicion, int valor);
	void borrar_valor(Posicion posicion);

	int dimension() const;
	bool posicion_valida(Posicion posicion) const;
	bool valor_valido(int v) const;
	int valor(Posicion posicion) const;
	bool es_inicial(Posicion posicion) const;
	bool esta_libre(Posicion posicion) const;

	void set_dimension(int d);

	//funciones auxiliares que se necesitan
	int casillas_vacias() const;
};