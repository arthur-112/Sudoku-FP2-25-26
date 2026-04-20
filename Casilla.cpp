#include "Casilla.h"

Casilla::Casilla(int v, bool i) {
	valor = v;
	esInicial = i;
}

bool Casilla::es_inicial() const {
	return esInicial;
}

bool Casilla::esta_ocupada() const {
	return valor != 0;
}

bool Casilla::esta_libre() const {
	return valor == 0;
}

int Casilla::tiene_valor() const {
	return valor;
}

void Casilla::poner_valor(int v) {
	valor = v;
}

void Casilla::borrar_valor() {
	valor = 0;
}