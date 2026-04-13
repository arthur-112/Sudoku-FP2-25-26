#pragma once
#include "Tablero.h"

class Juego {
private:
	Tablero tablero;
	int vacias;
public:

	Juego(int dimension = 0);

	void colocar_valor_inicial(Posicion const& p, int e);
	bool asignar_valor(Posicion const& p, int e);
	bool borrar_valor(Posicion const& p);
	void reiniciar();
	bool terminado() const;

	bool posicion_valida(Posicion const& p) const; 
	bool valor_valido(int v) const;
	int dimension() const;
	int valor(Posicion const& p) const;
	bool es_inicial(Posicion const& p) const;
	bool esta_libre(Posicion const& p) const;
	bool esta_ocupada(Posicion const& p) const;
};