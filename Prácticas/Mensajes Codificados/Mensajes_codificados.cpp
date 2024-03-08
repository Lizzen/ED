/*
NOMBRE Y APELLIDOS PRIMER INTEGRANTE DEL GRUPO: David Díaz Gregorio
NOMBRE Y APELLIDOS SEGUNDO INTEGRANTE DEL GRUPO: David Ferreras Díaz
USUARIO DEL JUEZ DOMJUDGE: B17
 */
#include <iostream>
using namespace std;
#include <string>

#include "lista.h"
// INCLUIR EL RESTO DE TADS QUE SE CONSIDEREN OPORTUNOS

//Función que devuelve true si el char es una vocal. 
bool esVocal(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}


// Reemplaza cada secuencia de caracteres no vocales consecutivos 
// por su inversa. 'mensaje' se deberá modificar con el resultado
// de realizar dicho proceso. 
void codifica(Lista<char>& mensaje) {
    Lista<char> secNoVocal;							/*Lista de secuencia de consonantes*/
    Lista<char>::Iterator it = mensaje.begin();		/*Iterador de la lista mensaje*/
    Lista<char>::Iterator elem = it;				/*Iterador auxiliar*/

    while (it != mensaje.end()) {
        bool cVocal = esVocal(it.elem());			/*Devuelve true si el char es una vocal*/
		
		//Si no es una vocal, introducimos el elemento en la lista de consonantes (secNoVocal)
        if (!cVocal) {
            elem = it;
            it.next();
            secNoVocal.pon_final(elem.elem());
            mensaje.eliminar(elem);
        }
		//Si es una vocal, insertamos las consonantes que haya en la lista de consonantes, de tal forma que se introducen a la inversa
        else {
            if (!secNoVocal.esVacia()) {
                while (!secNoVocal.esVacia()) {
                    mensaje.insertar(secNoVocal.ultimo(), it);
                    secNoVocal.quita_final();
                }
            }
            it.next();
        }
    }
	
	//Verifica que se hayan invertido todas las consonantes
    if (!secNoVocal.esVacia()) {
        while (!secNoVocal.esVacia()) {
            mensaje.insertar(secNoVocal.ultimo(), it);
            secNoVocal.quita_final();
        }
    }
}

 
// Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	Lista<char>::ConstIterator it = l.cbegin();
	while (it != l.cend()) {
		cout << it.elem();
		it.next();
	}
	cout << endl;
}


  // Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for(unsigned int i=0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);  
}

int main() {
	string linea;
	while(getline(cin,linea)) {
	   Lista<char> mensaje;
	   construyeMensaje(linea,mensaje);
       codifica(mensaje);
	   imprime(mensaje);
	}
	return 0;
}	
