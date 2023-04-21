// NOMBRE Y APELLIDOS DEL PRIMER INTEGRANTE: David Ferreras Díaz
// NOMBRE Y APELLIDOS DEL SEGUNDO INTEGRANTE:
// Nº DE GRUPO:
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

 
/**
  FUNCION A IMPLEMENTAR.
  Aparte de esta función, puedes implementar todas las funciones auxiliares que
  consideres oportuno. 
  Debes describir y justificar aquí la complejidad de la implementación realizada:
  
  

*/
int num_a_salvo(const Arbin<char>& a);

void num_a_salvo_aux(const Arbin<char>& a, int& asalvo, int monstruos, int& caballeros) {
	if (!a.esVacio()) {
		if (a.raiz() == 'D') {
			caballeros = 0;
			num_a_salvo_aux(a.hijoIz(), asalvo, monstruos, caballeros);
			num_a_salvo_aux(a.hijoDer(), asalvo, monstruos, caballeros);
			if (monstruos <= caballeros) {
				++asalvo;
			}
		}
		else {
			if (a.raiz() == 'M') {
				++monstruos;
			}
			else if (a.raiz() == 'C') {
				++caballeros;
			}
			num_a_salvo_aux(a.hijoIz(), asalvo, monstruos, caballeros);
			num_a_salvo_aux(a.hijoDer(), asalvo, monstruos, caballeros);
		}
	}
}

int num_a_salvo(const Arbin<char>& a) {
	/*** A IMPLEMENTAR ***/
	int asalvo = 0, caballeros = 0;
	num_a_salvo_aux(a, asalvo, 0, caballeros);
	return asalvo;
}

Arbin<char> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<char>();
	case '[': {
		char raiz;
		in >> raiz;
  		in >> c;
		return Arbin<char>(raiz);
	}
	case '(': {
		Arbin<char> iz = lee_arbol(in);
		char raiz;
		in >> raiz;
		Arbin<char> dr = lee_arbol(in);
		in >> c;
		return Arbin<char>(iz, raiz, dr);
	}
	default: return Arbin<char>();
	}
}


void escribe_arbol(Arbin<char> a) {
	if (a.esVacio()) cout << "#";
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio()) cout << "[" << a.raiz() << "]";
	else {
		cout << "("; 
		escribe_arbol(a.hijoIz()); 
		cout << a.raiz(); 
		escribe_arbol(a.hijoDer());
		cout << ")";
	}
}


int main() {
	Arbin<char> arbol;
	while (cin.peek() != EOF)  {
		Arbin<char> mapa = lee_arbol(cin);
		cout << "num_a_salvo ";
		escribe_arbol(mapa);
		cout << " => ";
		cout << num_a_salvo(mapa);
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
