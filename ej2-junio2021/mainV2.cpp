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
int num_correctivos_aux(const Arbin<int>& a, int &sum_val, int &num_nodos) {
	// A IMPLEMENTAR
	if (a.esVacio()) {
		return 0;
	}
	
	int iz_sumVal = 0, der_sumVal = 0, iz_nodos = 0, der_nodos = 0;
	
	int der = num_correctivos_aux(a.hijoDer(), der_sumVal, der_nodos);
	int iz = num_correctivos_aux(a.hijoIz(), iz_sumVal, iz_nodos);

	sum_val = der_sumVal + iz_sumVal + a.raiz();
	num_nodos = der_nodos + iz_nodos + 1;
	if (!a.hijoDer().esVacio() && a.raiz() == (der_sumVal - iz_nodos)) {
		return der + iz + 1;
	}

	return der + iz;
}

int num_correctivos(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int sum_val = 0, num_nodos = 0;
	return num_correctivos_aux(a, sum_val, num_nodos);
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
