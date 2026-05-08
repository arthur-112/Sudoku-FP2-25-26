#pragma once
#include "juego.h"
int const MAX_INICIAL = 1;
class ListaSudokus {
private:
	int contador;
	int capacidad;
	Juego** sudokus;

	// Búsqueda binaria recursiva para encontrar la posición de inserción
	int buscar(Juego const& juego, int a, int b) const;
	void desplazar_derecha(int pos);
	void desplazar_izquierda(int pos);
	void duplicar();
public:
	ListaSudokus();                  //constructora
	~ListaSudokus();                  // destructora
	bool vacia() const;                //true si no hay elementos guardados
	int num_elems() const;                      //numero de elementos guardados
	Juego const& operator[](int i) const;          
	Juego& operator[](int i);
	void insertar(Juego const& juego);
	void eliminar(int i);
};