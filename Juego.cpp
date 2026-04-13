#include "Juego.h"

Juego::Juego(int dimension = 0) {




}

bool Juego::posicion_valida(Posicion const& p) const {
	return tablero.posicion_valida(p);
}

bool Juego::valor_valido(int v) const {
	return tablero.valor_valido(v);
}

int Juego::dimension() const {
	return tablero.dimension();
}

int Juego::valor(Posicion const& p) const {
	return tablero.valor(p);
}

bool Juego::es_inicial(Posicion const& p) const {
	return tablero.es_inicial(p);
}

bool Juego::esta_libre(Posicion const& p) const {
	return tablero.esta_libre(p);
}

bool Juego::esta_ocupada(Posicion const& p) const {
	return tablero.esta_libre(p) == false;
}
