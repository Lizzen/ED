/** PONED NOMBRES Y APELLIDOS, AS� COMO N�MERO DE GRUPO
GRUPO: 20
NOMBRE Y APELLIDOS (INTEGRANTE 1): Álvaro Gómez Tejedor
NOMBRE Y APELLIDOS (INTEGRANTE 2): David Ferreras Díaz
*/

#include <iostream>
#include <string>
using namespace std;
#include "cola.h"
#include "pila.h"


void lee_caso(Cola<char>& cola) {
	char ch;
	cin.get(ch);
	while (ch != '\n') {
		if (ch != ' ')
			cola.pon(ch);
		cin.get(ch);
	}
}


bool palindroma(Cola<char> cola) {
	Pila<char> pila;
	int longitud = cola.longitud();
	int i = 0;
	bool palin = true;

	while (i < longitud / 2) {
		pila.apila(cola.primero());
		cola.quita();
		++i;
	}

	if (longitud % 2 != 0) {
		cola.quita();
	}

	while (!cola.esVacia()) {
		if (cola.primero() != pila.cima()) {
			palin = false;
		}
		cola.quita();
		pila.desapila();
	}

	return palin;
}


int main() {
	Cola<char> cola;

	lee_caso(cola);

	Cola<char> colaAux;
	colaAux = cola;
	int longitud = colaAux.longitud();
	for (int i = 1; i <= longitud; i++) {
		cout << colaAux.primero();
		colaAux.quita();
	}
	cout << " = ";
	if (palindroma(cola)) {
		cout << "SI\n";
	}
	else {
		cout << "NO\n";
	}

	return 0;
}