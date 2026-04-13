#include "Juego.h"

Juego::Juego(int dimension) {
	tablero.set_dimension(dimension);
}

void Juego::colocar_valor_inicial(Posicion const& p, int e) {
	tablero.colocar_valor_inicial(p, e);
}

bool Juego::asignar_valor(Posicion const& p, int e) {
	bool ok = false;
	if (tablero.posicion_valida(p)) {
		tablero.asignar_valor(p, e);
		ok = true;
	}
	return ok;
}

bool Juego::borrar_valor(Posicion const& p) {
	tablero.borrar_valor(p);
	return true;







}

bool Juego::terminado() const {
	bool ok = false;

	if (vacias == 0) {
		ok = true;
	}

	return ok;
}

bool Juego::bloqueado() const {
	bool ok = false;

	if (num_bloqueadas() > 0) {
		ok = true;
	}

	return ok;
}

int Juego::num_bloqueadas() const {
	return bloqueadas.cont;
}

Posicion Juego::casilla_bloqueada(int i) const {
	return bloqueadas.info[i];
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
	return !tablero.esta_libre(p);
}

