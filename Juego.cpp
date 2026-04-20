#include "Juego.h"

Juego::Juego(int dimension) {
	tablero.set_dimension(dimension);
	vacias = tablero.casillas_vacias();
	for (int i = 0; i < dimension() * dimension(); i++) {
		bloqueadas.info[i].f = 0;
		bloqueadas.info[i].c = 0;
	}
	bloqueadas.cont = 0;
	for (int i = 0; i < dimension(); i++) {
		for (int j = 0; j < dimension(); j++) {
			for (int k = 1; k < dimension() + 1; k++) {
				valores[i][j][k].posible = true;
				valores[i][j][k].num_casillas_culpables = 0;
			}
		}
	}
}

void Juego::colocar_valor_inicial(Posicion const& p, int e) {
	tablero.colocar_valor_inicial(p, e);
}

bool Juego::asignar_valor(Posicion const& p, int e) {
	bool ok = false;
	if (tablero.posicion_valida(p) && tablero.esta_libre(p) && valor_valido(e) && valores[p.f][p.c][e].posible) {
		ok = true;
		tablero.asignar_valor(p, e);
		propagar_a_casillas_afectadas(p, e, true); //true para saber que se ha borrado un valor en las funciones de afectar,propagar_a_casillas_afectadas, etc
		vacias--;
	}
	return ok;
}

bool Juego::borrar_valor(Posicion const& p) {
	bool ok = false;
	if (tablero.posicion_valida(p) && !tablero.esta_libre(p) && !tablero.es_inicial(p)) {
		ok = true;
		int val = valor(p);
		tablero.borrar_valor(p);
		procesar_bloqueos(p, false); //false para saber que se ha borrado un valor en las funciones de afectar,propagar_a_casillas_afectadas, etc
		propagar_a_casillas_afectadas(p, val, false);
		vacias++;
	}
	return ok;
}

void Juego::auto_completar() {
	Posibles posibles;
	for (int i = 0; i < dimension(); i++) {
		for (int j = 0; j < dimension(); j++) {
			Posicion pos = { i, j };
			if (esta_libre(pos) && valores_posibles(pos,posibles)==1) {
				for (int k = 0; k < dimension() + 1; i++) {
					if (posibles[k] == true) {
						asignar_valor(pos, k);
					}
				} 
			}
		}
	}

}

void Juego::reiniciar() {
	Posicion pos;
	for (int i = 0; i < dimension(); i++) {
		for (int j = 0; j < dimension(); j++) {
			pos.f = i;
			pos.c = j;
			if (!es_inicial(pos)) {
				tablero.asignar_valor(pos, 0);
			}
		}
	}
}

int Juego::valores_posibles(Posicion p, Posibles posibles) const {
	int contador = 0;

	for (int i = 1; i < dimension() + 1; i++) {
		if (valores[p.f][p.c][i].posible == true) {
			contador++;
			posibles[i] = true;
		}
		else {
			posibles[i] = false;
		}
	}
	return contador;
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

bool Juego::esta_bloqueada(Posicion posicion) const {
	bool ok = false;

	for (int i = 0; i < bloqueadas.cont; i++) {
		if (bloqueadas.info[i].f == posicion.f && bloqueadas.info[i].c == posicion.c) {
			ok = true;
		}
	}

	return ok;
}

void Juego::insertar_bloqueada(Posicion posicion) {
	if (bloqueadas.cont != dimension() * dimension()){
		bloqueadas.info[bloqueadas.cont] = posicion;
		bloqueadas.cont++;
	}
}

void Juego::propagar_a_casillas_afectadas(Posicion posicion, int valor, bool poniendo) {
	Posicion nueva_pos;

	for (int i = 0; i < dimension(); i++) {
		if (posicion.c == i) {

		}
		else {
			nueva_pos.f = posicion.f;
			nueva_pos.c = i;
			afectar(nueva_pos, valor, poniendo);
			procesar_bloqueos(nueva_pos, poniendo);
		}
	}

	for (int j = 0; j < dimension(); j++) {
		if (posicion.f == j) {

		}
		else {
			nueva_pos.f = j;
			nueva_pos.c = posicion.c;
			afectar(nueva_pos, valor, poniendo);
			procesar_bloqueos(nueva_pos, poniendo);
		}
	}

	int dimReg = sqrt(dimension());
	int inicio_fila = (posicion.f / dimReg) * dimReg;
	int inicio_col = (posicion.c / dimReg) * dimReg;

	for (int i = inicio_fila; i < inicio_fila + dimReg; i++) {
		for (int j = inicio_col; j < inicio_col + dimReg; j++) {
			if (posicion.f == i || posicion.c == j) {

			}
			else {
				nueva_pos.f = i;
				nueva_pos.c = j;
				afectar(nueva_pos, valor, poniendo);
				procesar_bloqueos(nueva_pos, poniendo);
			}
		}
	}
}

void Juego::afectar(Posicion posicion, int valor, bool poniendo) {
	if (poniendo == true) {
		valores[posicion.f][posicion.c][valor].posible = false;
		valores[posicion.f][posicion.c][valor].num_casillas_culpables++;
	}
	else {
		valores[posicion.f][posicion.c][valor].num_casillas_culpables--;
		if (valores[posicion.f][posicion.c][valor].num_casillas_culpables == 0) {
			valores[posicion.f][posicion.c][valor].posible = true;
		}
	}
}

void Juego::procesar_bloqueos(Posicion posicion, bool poniendo) {
	if (esta_libre(posicion)) {
		Posibles posibles;

		if (poniendo == true && valores_posibles(posicion, posibles) == 0 && !esta_bloqueada(posicion)) {
			insertar_bloqueada(posicion);
		}
		if (poniendo == false && valores_posibles(posicion, posibles) != 0 && esta_bloqueada(posicion)) {
			eliminar_bloqueada(posicion);
		}
	}
}

void Juego::eliminar_bloqueada(Posicion posicion) {
	int indice = -1;

	for (int i = 0; i < bloqueadas.cont; i++) {
		if (bloqueadas.info[i].f == posicion.f && bloqueadas.info[i].c == posicion.c) {
			indice = i;
		}
	}

	bloqueadas.info[indice].f = 0;
	bloqueadas.info[indice].c = 0;
	for (int j = indice; j < bloqueadas.cont - 1; j++) {
		bloqueadas.info[j] = bloqueadas.info[j + 1];
	}
	bloqueadas.cont--;
}