#include <iostream>
#include "listaSudokus.h"

void ListaSudokus::duplicar() {
    capacidad = capacidad * 2 + 1;
    Juego** nuevaLista = new Juego * [capacidad];
    for (int i = 0; i < contador; i++) {
        nuevaLista[i] = sudokus[i];
    }
    delete[] sudokus;
    sudokus = nuevaLista;
}
int ListaSudokus::buscar(Juego const& juego, int a, int b) const {
    if (a > b) {
        return a;
    }
    else {
        int mitad = (a + b) / 2;
        if (juego < *sudokus[mitad]) {
            return buscar(juego, a, mitad - 1);
        }
        else if (*sudokus[mitad] < juego) {
            return buscar(juego, mitad + 1, b);
        }
        else {
            return mitad; 
        }
    }
}
void ListaSudokus::desplazar_derecha(int pos) {
    for (int i = contador; i > pos; i--) {
        sudokus[i] = sudokus[i - 1];
    }
}
void ListaSudokus::desplazar_izquierda(int pos) {
    for (int i = pos; i < contador - 1; i++) {
        sudokus[i] = sudokus[i + 1];
    }
    sudokus[contador - 1] = nullptr;
}

ListaSudokus::ListaSudokus() {
    capacidad = 10;
    contador = 0;
    sudokus = new Juego* [capacidad];
}

ListaSudokus::~ListaSudokus() {
    for (int i = 0; i < contador; i++) {
        delete sudokus[i];
    }
    delete[] sudokus;
}
bool ListaSudokus::vacia() const {
    return contador == 0;
}

int ListaSudokus::num_elems() const {
    return contador;
}
Juego const& ListaSudokus::operator[](int i) const {
    return *sudokus[i];
}

Juego& ListaSudokus::operator[](int i) {   // Modificar el juego
    return *sudokus[i];
}
void ListaSudokus::insertar(Juego const& juego) {
    if (contador == capacidad) {
        duplicar();
    }
    int pos = buscar(juego, 0, contador - 1);
    desplazar_derecha(pos);
    sudokus[pos] = new Juego(juego);
    contador++;
}
void ListaSudokus::eliminar(int i) {
    if (i >= 0 && i < contador) {
        delete sudokus[i];
        desplazar_izquierda(i);
        contador--;
    }
}