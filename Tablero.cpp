#include "Tablero.h"
#include "Casilla.h"

Tablero::Tablero(int d) {
	dim = d;
}

void Tablero::colocar_valor_inicial(Posicion posicion, int valor) {
	tab[posicion.f][posicion.c].poner_valor(valor);
}

void Tablero::asignar_valor(Posicion posicion, int valor) {
	tab[posicion.f][posicion.c].poner_valor(valor);
}

void Tablero::borrar_valor(Posicion posicion) {
	tab[posicion.f][posicion.c].borrar_valor();
}

int Tablero::dimension() const {
	return dim;
}

bool Tablero::posicion_valida(Posicion posicion) const {
	return posicion.f >= 0 && posicion.f < dim && posicion.c >= 0 && posicion.c < dim;
}

bool Tablero::valor_valido(int v) const {
	return v >= 0 && v <= 9;
}

int Tablero::valor(Posicion posicion) const {
	return tab[posicion.f][posicion.c].tiene_valor();
}

bool Tablero::es_inicial(Posicion posicion) const {
	return tab[posicion.f][posicion.c].es_inicial();
}

bool Tablero::esta_libre(Posicion posicion) const {
	return tab[posicion.f][posicion.c].esta_libre();
}