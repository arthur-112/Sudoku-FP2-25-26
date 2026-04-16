#pragma once
#include "Tablero.h"

class Juego {
private:

	Tablero tablero;
	int vacias;

	struct Bloqueos {                                          // casillas sin valores posibles
		int cont = 0;
		Posicion info[MAX_DIM * MAX_DIM];
	};

	Bloqueos bloqueadas;                                        // Guarda las posiciones bloqueadas

	bool esta_bloqueada(Posicion posicion) const;
	void insertar_bloqueada(Posicion posicion);


	struct Valor {                                                     // Tipo oculto
		bool posible;
		int num_casillas_culpables; // > 0 si posible == false; 0 e.o.c.
	};

	Valor valores[MAX_DIM][MAX_DIM][MAX_DIM + 1];                // Representa los valores posibles en una determinada posición

	void propagar_a_casillas_afectadas(Posicion posicion, int valor, Posibles poniendo);
	void afectar(Posicion posicion, int valor, Posibles poniendo);

	void procesar_bloqueos(Posicion posicion, Posibles poniendo);
	void eliminar_bloqueada(Posicion posicion);

public:
	Juego(int dimension = 0);

	void colocar_valor_inicial(Posicion const& p, int e);

	bool asignar_valor(Posicion const& p, int e);
	bool borrar_valor(Posicion const& p);
	void auto_completar();
	void reiniciar();
	int valores_posibles(Posicion p, Valor valores) const;

	bool terminado() const;
	bool bloqueado() const;
	int num_bloqueadas() const;
	Posicion casilla_bloqueada(int i) const;

	// Delegan en Tablero
	bool posicion_valida(Posicion const& p) const;
	bool valor_valido(int v) const;
	int dimension() const;
	int valor(Posicion const& p) const;
	bool es_inicial(Posicion const& p) const;
	bool esta_libre(Posicion const& p) const;
	bool esta_ocupada(Posicion const& p) const;
};