// NOMBRE Y APELLIDOS INTEGRANTE 1: David Ferreras Díaz
// NOMBRE Y APELLIDOS INTEGRANTE 2: David Díaz Gregorio
// USUARIO DEL JUEZ: B17


#include <iostream>
#include <string>
#include "Arbin.h"
using namespace std;



/** INDICA AQUÍ JUSTIFICADAMENTE LA COMPLEJIDAD DEL ALGORITMO
	
	La complejidad del algoritmo es O(n) donde n es el número de nodos que contiene el árbol ya que se recorren todos los nodos del árbol una sola vez 
	para ver si son o no impar-colgantes.
	**/

int numImparColgantes_aux(Arbin<int> a, int suma_ancestros, int& suma_descendientes) {
	if (a.esVacio()) {
		return 0;
	}
	else {

		int anc = suma_ancestros,  desc_izq = 0, desc_der = 0;

		if (a.raiz() % 2 != 0) {
			anc += a.raiz();
			suma_descendientes += a.raiz();
		}
		
		int der = numImparColgantes_aux(a.hijoDer(), anc, desc_der);
		int izq = numImparColgantes_aux(a.hijoIz(), anc, desc_izq);

		suma_descendientes += desc_der + desc_izq;

		if ((desc_der + desc_izq) > suma_ancestros) {
			return der + izq + 1;
		}
		else {
			return der + izq;
		}
	}
}

int numImparColgantes(Arbin<int> a) {
	// IMPLEMENTA AQUÍ EL SUBPROGRAMA
	int sum_descendientes = 0;
	return numImparColgantes_aux(a, 0, sum_descendientes);
}



/*
Formato de la entrada
=====================
El formato de cada caso es como sigue:
- Cada línea contiene la descripción de un árbol
- Para describir los árboles se sigue el siguiente convenio:
* Los árboles vacíos se escriben como #
* Los árboles simples se escriben como [c], con c el contenido del nodo.
* Los árboles compuestos se escriben como (IcD), donde:  (i) I es el hijo izquierdo; (ii) c es el contenido de la raíz; (iii) D es el hijo derecho.


Formato de la salida
====================
Para cada caso el programa imprime el número de nodos impar-colgantes.


Ejemplo de entrada
==================
#
[11]
([3]1[5])
(([7]8([9]6#))5(#13([15]3[6])))


Salida asociada
===============
0
0
1
4


*/

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



void ejecuta_caso() {
	Arbin<int> a = lee_arbol(cin);
	cout << numImparColgantes(a);
	cout << endl;
}


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		ejecuta_caso();
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}