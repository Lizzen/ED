/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;


/*
* COMPLEJIDAD: Determina justificadamente la complejidad de este algoritmo.
*	Tiene una complejidad O(n) porque se recorren todos los nodos del árbol una vez.
*/
bool es_peculiar_aux(const Arbin<int>& a, int& minimo, int& maximo, int& pares, int& impares) {
	// A IMPLEMENTAR

	if (a.esVacio()) {
		return true;
	}
	else if (a.hijoDer().esVacio() && a.hijoIz().esVacio()){
		minimo = a.raiz();
		maximo = a.raiz();
		if (a.raiz() % 2 == 0) {
			pares +=  1;
		}
		else
		{
			impares += 1;
		}
		return true; 
	}

	int min_der = minimo, max_der = 0, pares_der = 0, impares_der = 0,
		min_iz = minimo, max_iz = 0, pares_iz = 0, impares_iz = 0;

	bool der = es_peculiar_aux(a.hijoDer(), min_der, max_der, pares_der, impares_der);
	bool iz = es_peculiar_aux(a.hijoIz(), min_iz, max_iz, pares_iz, impares_iz);	

	if (der && iz && ((a.hijoDer().esVacio() && a.raiz() < min_iz) || (a.hijoIz().esVacio() && a.raiz() > max_der) || (pares_der - impares_iz == a.raiz()))) {
		if (min_iz > min_der) {
			minimo = min(min_der, a.raiz());
		}
		else {
			minimo = min(min_iz, a.raiz());
		}

		if (max_iz > max_der) {
			maximo = max(min_iz, a.raiz());
		}
		else {
			maximo = max(min_der, a.raiz());
		}

		if (a.raiz() % 2 == 0) {
			pares += pares_der + pares_iz + 1;
			impares += impares_der + impares_iz;
		}
		else
		{
			pares += pares_der + pares_iz;
			impares += 1 + impares_der + impares_iz;
		}
		return true;
	}

	return false;
}

bool es_peculiar(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int minimo = 10000, maximo = 0, pares = 0, impares = 0;
	return es_peculiar_aux(a, minimo, maximo, pares, impares);
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

void muestra_solucion(bool rebuscado) {
  if (rebuscado) {
	 cout << "SI" << endl; 
  }	
  else {
	 cout << "NO" << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		muestra_solucion(es_peculiar(a));
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}