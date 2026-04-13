#include "Casilla.h"

Casilla::Casilla(int v, bool i) {
	valor = v;
	inicial = i;
}
bool Casilla::es_inicial() const {
	return inicial;
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
	if(!es_inicial()) valor = v;
}
void Casilla::borrar_valor() {
	if (!es_inicial()) valor = 0;
}
