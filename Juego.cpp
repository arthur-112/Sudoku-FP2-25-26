#include "Juego.h"

Juego::Juego:tablero(int dimension) {     //Se accede al atributo tablero y se le envia la dimension, que en realidad va a parar a la constructora de la propia clase tablero
	vacias = dimension * dimension;         //Esta es la totalidad de casillas vacias cuando se inicia el programa
}
void Juego::colocar_valor_inicial(Posicion const& p, int e) {
	tablero.colocar_valor_inicial(p, e);                 //Delega la tarea en la misma funcion de tablero
	vacias--;                                       //Reduce la cantidad de casillas vacias
}
bool Juego::asignar_valor(Posicion const& p, int e) {
	if (esta_libre(p)) {
		tablero.asignar_valor(p, e);
		vacias--;
		return true;
	}
	return false;
}
bool Juego::borrar_valor(Posicion const)

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
