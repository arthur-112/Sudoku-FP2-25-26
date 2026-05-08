#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

#include "io.h"
#include "colores.h"
#include "juego.h"

using namespace std;

/* Constantes para pintar el estado del juego */
char const HORIZONTAL = char(196);
char const UPPER_LEFT = char(218);
char const UPPER_CROSS = char(194);
char const UPPER_RIGHT = char(191);
char const VERTICAL = char(179);
char const MID_LEFT = char(195);
char const MID_CROSS = char(197);
char const MID_RIGHT = char(180);
char const LOWER_LEFT = char(192);
char const LOWER_CROSS = char(193);
char const LOWER_RIGHT = char(217);
char const SQUARE = char(219);
char const EMPTY = char(250);

int const DEFAULT_COLOR = -1;
int const TAM_CELDA = 3; // Celdas de 3 x 3
string const MARGEN = "   ";

// Cabecera de columnas
void static mostrar_columnas(int dimRegion) {
	cout << MARGEN << MARGEN;

	for (int j = 0; j < dimRegion; j++) {
		for (int i = 1; i <= dimRegion; i++)
			cout << ' ' << dimRegion * j + i << ' ';
		cout << ' ';
	}

	cout << '\n';
}

// Líneas horizontales de las regiones de la cuadrícula
void static mostrar_linea(char esqIzda, char cruce, char esqDer, int dimRegion) {
	cout << MARGEN << "  " << esqIzda;

	for (int i = 1; i < dimRegion; i++)
		cout << string(dimRegion * TAM_CELDA, HORIZONTAL) << cruce;

	cout << string(dimRegion * TAM_CELDA, HORIZONTAL) << esqDer << '\n';
}

// Contenido de las casillas de una región de una fila
void static mostrar_region_fila(Juego const& juego, int f, int c, int dimRegion) {
	for (int k = 0; k < dimRegion; k++) {
		Posicion p = { f, c + k }; // válida por construcción

		int v = juego.valor(p);

		if (v != 0) {
			if (juego.es_inicial(p))
				cout << ORANGE << ' ' << v << ' ' << RESET;
			else
				cout << ' ' << v << ' ';
		}
		else
			cout << ' ' << EMPTY << ' ';
	}
}

// Contenido de una fila de casillas
void static mostrar_fila(Juego const& juego, int fila, int dimRegion) {
	// margen inicial + nº de fila
	cout << MARGEN << fila + 1 << ' ';

	int columna = 0;

	for (int k = 0; k < dimRegion; k++) {
		cout << VERTICAL;
		mostrar_region_fila(juego, fila, columna, dimRegion);
		columna += dimRegion;
	}

	cout << VERTICAL << '\n';
}

void mostrar_juego(Juego const& juego) {
	cout << RESET;

	int dim = juego.dimension();
	int dimRegion = (int)sqrt(dim);

	// borde superior
	mostrar_columnas(dimRegion);
	mostrar_linea(UPPER_LEFT, UPPER_CROSS, UPPER_RIGHT, dimRegion);

	// Primera fila
	mostrar_fila(juego, 0, dimRegion);

	for (int f = 1; f < dim; f++) {
		// separación entre bloques de filas
		if (f % dimRegion == 0)
			mostrar_linea(MID_LEFT, MID_CROSS, MID_RIGHT, dimRegion);

		mostrar_fila(juego, f, dimRegion);
	}

	mostrar_linea(LOWER_LEFT, LOWER_CROSS, LOWER_RIGHT, dimRegion);
}

void mostrar_cabecera() {
	cout << '\n' << BLUE;
	cout << MARGEN << "*************\n";
	cout << MARGEN << "* Mi Sudoku *\n";
	cout << MARGEN << "*************\n";
	cout << RESET;
}

void mostrar_resultado(Juego const& juego) {
	cout << '\n' << RED;
	cout << MARGEN;

	if (juego.terminado())
		cout << "ENHORABUENA --- Sudoku RESUELTO";
	else
		cout << "Abandonaste el juego";

	cout << RESET;
	cout << "\n\n";
}

// Pide pos hasta que obtiene una válida (implementación recursiva)
// Por eso necesita el juego como parámetro (para comprobar que es válida)
Posicion static leer_posicion(Juego const& juego, bool libre) {
	Posicion pos;

	cout << MARGEN << "Selecciona una CASILLA (fila y columna): ";
	cin >> pos.f >> pos.c;
	cout << "\n";

	// Conversión a representación interna estándar
	pos.f--;
	pos.c--;

	if (!juego.posicion_valida(pos)) {
		mostrar_error("Casilla inexistente.");

		return leer_posicion(juego, libre);
	}
	else if (juego.es_inicial(pos)) {
		mostrar_error("Casilla no modificable.");

		return leer_posicion(juego, libre);
	}
	else if ((libre && !juego.esta_libre(pos)) || (!libre && juego.esta_libre(pos))) {
		
		if (libre)
			mostrar_error("La accion seleccionada requiere una casilla libre.");
		else
			mostrar_error("La accion seleccionada requiere una casilla ocupada.");

		return leer_posicion(juego, libre);
	}
	else
		return pos;
}

int static leer_valor(Juego const& juego) {
	int v;

	cout << MARGEN << "Indica un valor: ";
	cin >> v;
	cout << "\n";

	if (!juego.valor_valido(v)) {
		mostrar_error("Valor invalido.");

		return leer_valor(juego);
	}
	else 
		return v;
}

// El jugador elige acción (y casilla sobre la que aplicarla, si procede)
Eleccion elegir(Juego const& juego) {
	Eleccion act;

	while (act.accion == INDETERMINADA) {
		cout << "\n"
			<< MARGEN << "Selecciona una accion:\n\n";
		cout << MARGEN << "1 - PONER NUMERO\n";
		cout << MARGEN << "2 - BORRAR NUMERO\n";
		cout << MARGEN << "3 - POSIBLES VALORES ?\n";
		cout << MARGEN << "4 - AUTO-COMPLETAR TRIVIALES\n";
		cout << MARGEN << "5 - REINICIAR\n";
		cout << MARGEN << "6 - SALIR\n\n";
		cout << MARGEN << "Accion: ";

		int eleccion;
		cin >> eleccion;
		cout << "\n";

		switch (eleccion) {
		case 1:
			act.accion = ASIGNAR;
			act.casilla = leer_posicion(juego, true);
			act.valor = leer_valor(juego);
			break;
		case 2:
			act.accion = QUITAR;
			act.casilla = leer_posicion(juego, false);
			break;
		case 3:
			act.accion = POSIBLES;
			act.casilla = leer_posicion(juego, true);
			break;
		case 4:
			act.accion = AUTO;
			break;
		case 5:
			act.accion = REINICIAR;
			break;
		case 6:
			act.accion = SALIR;
			break;
		default:
			mostrar_error("Eleccion invalida.");
			break;
		}
	}

	return act;
}

// Carga de juego desde un flujo de entrada
istream& operator>>(istream& flujoEntrada, Juego& juego)  {
	int dimension;
	flujoEntrada >> dimension;

	juego = Juego(dimension);

	int elemento;

	for (int f = 0; f < dimension; f++)
		for (int c = 0; c < dimension; c++) {
			flujoEntrada >> elemento;

			if (elemento != 0)
				juego.colocar_valor_inicial({ f, c }, elemento);
		}

	return flujoEntrada;
}

// Solicita un nombre de archivo hasta que logra abrirlo
Juego cargar_juego() {
	Juego juego;

	string nombreArchivo;
	bool abierto = false;

	while (!abierto) {
		cout << "\n" << MARGEN << "Nombre del archivo desde el que cargar el juego: ";
		cin >> nombreArchivo;
		cout << "\n";

		ifstream archivo;
		archivo.open(nombreArchivo.c_str());

		if (archivo.is_open()) {
			// asumo formato correcto de los ficheros 
			// (si no, habría que hacer una función booleana que asegurara que la carga ha ido bien)
			archivo >> juego;
			archivo.close();
			abierto = true;
		}
		else
			mostrar_error("Archivo no encontrado.");
	}

	return juego;
}

void mostrar_valores_posibles(Juego const& juego, Posibles posible, int n) {
	cout << RED << MARGEN << "Los posibles valores son: ";

	if (n == 0)
		cout << "Ninguno!";
	else {
		int dim = juego.dimension();
		int i = 1;

		while (i <= dim && !posible[i])
			++i;

		cout << "{ " << i;
		++i;

		while (i <= dim) {
			if (posible[i])
				cout << ", " << i;
			++i;
		}
	}

	cout << " }\n\n" << RESET;
}

void mostrar_error(string const& mensaje) {
	cout << MARGEN << GREEN << mensaje << "\n\n" << RESET;
}

void mostrar_bloqueadas(Juego const& juego) {
	assert(juego.bloqueado());

	cout << "\n";
	mostrar_error("Sudoku BLOQUEADO: las casillas bloqueadas son:");

	int n = juego.num_bloqueadas();

	for (int i = 0; i < n; i++) {
		Posicion p = juego.casilla_bloqueada(i);
		cout << MARGEN << "(" << p.f + 1 << ", " << p.c + 1 << ")\n";
	}
}

// Para la versión 2

TipoPartida partida() {
	TipoPartida tipo = NINGUNA;

	while (tipo == NINGUNA) {
		cout << "\n"
			<< MARGEN << "Elige si quieres empezar un nuevo sudoku (N), continuar un sudoku (C) o abandonar (A):\n\n";
		cout << MARGEN << "Eleccion: ";

		char eleccion;
		cin >> eleccion;
		cout << '\n';

		eleccion = toupper(eleccion);

		switch (eleccion) {
		case 'N':
			tipo = NUEVA;
			break;
		case 'C':
			tipo = ANTIGUA;
			break;
		case 'A':
			tipo = ABANDONAR;
			break;
		default:
			mostrar_error("Eleccion invalida.");
			break;
		}
	}

	return tipo;
}

Juego static cargar_juego(string const& nombreArchivo) {
	Juego juego;

	ifstream archivo;
	archivo.open(nombreArchivo.c_str());

	if (archivo.is_open()) {
		// asumo formato correcto de los ficheros 
		archivo >> juego;
		archivo.close();
	}
	else
		mostrar_error("Archivo no encontrado.");
	
	return juego;
}

void cargar_lista_partidas(ListaSudokus& lista) {
	ifstream archivo;
	archivo.open("lista_partidas.txt");

	if (archivo.is_open()) {
		int num_partidas;
		archivo >> num_partidas;

		for (int i = 0; i < num_partidas; i++) {
			Juego juego;
			archivo >> juego;

			int f, c, valor;
			archivo >> f;

			while (f != -1) {
				archivo >> c >> valor;
				juego.asignar_valor({ f, c }, valor);
				archivo >> f;
			}

			lista.insertar(juego);
		}

		archivo.close();
	}
	else
		mostrar_error("Lista de partidas no encontrada.");
}

void cargar_lista_sudokus(ListaSudokus& lista) {
	ifstream archivo;
	archivo.open("lista_sudokus.txt");

	if (archivo.is_open()) {
		int num_sudokus;
		archivo >> num_sudokus;

		string dummy;
		getline(archivo, dummy); // leer el resto de la línea (contenido irrelevante)

		for (int i = 0; i < num_sudokus; i++) {
			string nombre;
			getline(archivo, nombre);
			
			// Asumo que existen todos los ficheros listados
			Juego juego = cargar_juego(nombre);

			lista.insertar(juego);
		}

		archivo.close();
	}
	else
		mostrar_error("Lista de sudokus no encontrada.");
}

void static mostrar_lista(ListaSudokus const& lista) {
	int num_elems = lista.num_elems();

	for (int i = 0; i < num_elems; i++) {
		Juego sudoku = lista[i];
		cout << RED << MARGEN << i + 1 << " - Sudoku con " << sudoku.numero_vacias() << " casillas vacias" << RESET << '\n';

		int valores[MAX_DIM + 1];
		sudoku.numero_casillas_posibles(valores);

		for (int i = 1; i <= MAX_DIM; i++)
			cout << MARGEN << MARGEN << MARGEN << "+ casillas con " << i << " valores posibles: " << valores[i] << '\n';

		cout << '\n';
	}
}

int elige_sudoku(ListaSudokus const& lista) {
	int num_elems = lista.num_elems();
	int op;

	do {
		mostrar_lista(lista);
		cout << MARGEN << "Elige un numero de sudoku: ";
		cin >> op;
		cout << "\n\n";

	} while (op < 1 || op > num_elems);

	return op - 1;
}

void static guardar_partida(ofstream& archivo, Juego const& juego) {
	int dim = juego.dimension();

	archivo << dim << '\n';

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			Posicion p = { i, j };

			if (juego.es_inicial(p)) 
				archivo << juego.valor(p) << ' ';
			else 
				archivo << "0 ";
		}
		archivo << '\n';
	}

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			Posicion p = { i, j };

			if (juego.esta_ocupada(p))
				archivo << i << ' ' << j << ' ' << juego.valor(p) << '\n';
		}
	}

	archivo << "-1\n";
}

void static guardar_lista_partidas(ListaSudokus const& lista) {
	ofstream archivo;
	archivo.open("lista_partidas.txt");

	if (archivo.is_open()) {
		int n = lista.num_elems();
		archivo << n << '\n';

		for (int i = 0; i < n; i++) 
			guardar_partida(archivo, lista[i]);

		archivo.close();
	}
	else
		mostrar_error("Lista de partidas no encontrada.");
}

