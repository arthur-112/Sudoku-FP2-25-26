#pragma once

class Casilla {
private:
	bool inicial;
	int valor;
public:

	Casilla(int v = 0, bool i = false);

	bool es_inicial() const;
	bool esta_ocupada() const;
	bool esta_libre() const;
	int tiene_valor() const;

	void poner_valor(int v);
	void borrar_valor();








};

