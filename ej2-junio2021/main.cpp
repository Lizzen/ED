// NOMBRE Y APELLIDOS: David Ferreras Díaz
// USUARIO DEL JUEZ:


#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/*
Determinar justificadamente la complejidad del algoritmo:
	La complejidad de la función es O(n) donde n es el número de nodos que presenta el árbol ya que para saber la cantidad de nodos correctivos hay que mirar todos una vez.
*/
int num_correctivos_aux(const Arbin<int>& a, int& sum_nodos, int& num_nodos) {
	if (a.esVacio()) {
		return 0;
	}
	else if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {
		sum_nodos += a.raiz();
		num_nodos += 1;
		return 0;
	}
	else {
		int valor_der = 0, valor_izq = 0, num_izq = 0, num_der = 0;
		int der = num_correctivos_aux(a.hijoDer(), valor_der, num_der);
		int izq = num_correctivos_aux(a.hijoIz(), valor_izq, num_izq);

		sum_nodos = valor_der + valor_izq + a.raiz();
		num_nodos = num_der + num_izq + 1;

		if (!(a.hijoDer().esVacio()) && (valor_der - num_izq) == a.raiz()) {
			return 1 + izq + der;
		}
		else { return izq + der; }
	}
}

int num_correctivos(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int sum_nodos = 0, num_nodos = 0;
	return num_correctivos_aux(a, sum_nodos, num_nodos);
}




Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		cout << num_correctivos(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
