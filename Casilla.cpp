#include "Casilla.h"

Casilla::Casilla(int v, bool i) {
	valor = v;
	esInicial = i;
	ocupado = false;
}

bool Casilla::es_inicial() const {
	return esInicial;
}

bool Casilla::esta_ocupada() const {
	return ocupado == true;
}

bool Casilla::esta_libre() const {
	return ocupado == false;
}

int Casilla::tiene_valor() const {
	return valor;
}

void Casilla::poner_valor(int v) {
	valor = v;
	ocupado = true;
}

void Casilla::borrar_valor() {
	valor = 0;
	ocupado = false;
}
