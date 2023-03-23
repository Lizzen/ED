// INDICA AQU� LOS DATOS DEL GRUPO: B20 (alvgom20@ucm.es y dferre07@ucm.es)
// NOMBRE Y APELLIDOS DEL PRIMER INTEGRANTE: �lvaro G�mez Tejedor 
// NOMBRE Y APELLIDOS DEL SEGUNDO INTEGRANTE: David Ferreras D�az
// N� DE GRUPO: 20


#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

/**
  COMPLEJIDAD: Explica aqu� justificadamente cu�l es la complejidad de
			   esta funci�n
			   ***A COMPLETAR***
			   La complejidad de la funci�n es O(n) donde n es el n�mero de nodos en el �rbol debido a que cada nodo
			   se tiene que visitar una vez y se busca si es una hoja profunda.
*/

/*Fuenci�n que, dada una profundidad, busca y devuelve las hojas m�s profundas que k*/
unsigned int numero_hojas_mas_profundas_que_aux(const Arbin<int>& a, unsigned int k, unsigned int profundidad) {
	if (a.esVacio()) {
		return 0;
	}
	else if (a.hijoIz().esVacio() && a.hijoDer().esVacio() && profundidad >= k) {
		return 1;
	}
	else {
		return (numero_hojas_mas_profundas_que_aux(a.hijoIz(), k, profundidad + 1) + numero_hojas_mas_profundas_que_aux(a.hijoDer(), k, profundidad + 1));
	}
}

/*Llama desde la profundidad de la ra�z a la funci�n que busca las hojas profundas y devuelve el n�mero de hojas profundas*/
unsigned int numero_hojas_mas_profundas_que(const Arbin<int>& a, unsigned int k) {
	// A IMPLEMENTAR
	return numero_hojas_mas_profundas_que_aux(a, k, 0);
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



/**
La entrada al programa consiste de l�neas formadas por:
(1) Un �rbol de enteros
(2) El valor de k
Los �rboles se codifican de acuerdo con las siguientes reglas:
(1) El �rbol vac�o se codifica como #
(2) Los �rboles simples se codifican como [v], con
	v el valor del nodo
(3) Los �rboles complejos se codifican como (IvD),
	con I la codificaci�n del hijo izquierdo,
	v el valor de la ra�z, y D la codificaci�n
	del hijo derecho.
Para cada l�nea leida, escribe en la salida est�ndar
el n�mero de hojas que est�n a profundidad mayor que k


Ejemplo de entrada:

([2]1([4]3[5])) 0
([2]1([4]3[5])) 1
([2]1([4]3[5])) 2
([2]1([4]3[5])) 3
([2]1([4]3[5])) 4
([2]1([4]3[5])) 100

Salida asociada:

3
3
2
0
0
0

*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a, k) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
