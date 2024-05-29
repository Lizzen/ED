// NO MODIFIQUES NADA DE LO QUE APARECE EN ESTE FICHERO

#include <iostream>
#include <string>
#include "lista.h"

using namespace std;

void escribe_lista(Lista<int> l) {
    l.imprime(cout);
    cout << "#";
    l.imprime_invertida(cout);
    cout << "#";
    cout << l.longitud();
    cout << endl;
}

bool lee_lista(Lista<int>& l) {
    int n;
    cin >> n;
    if (n == -1) return false;
    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        l.pon_final(e);
    }
    return true;
}


bool ejecuta_caso() {
        Lista<int> a;
        if (! lee_lista(a)) return false;
        unsigned int pos_inicio;
        cin >> pos_inicio;
        unsigned int n_elems_a_extraer;
        cin >> n_elems_a_extraer;
        Lista<int> b;
        lee_lista(b);
        Lista<int> extracto = a.extrae_e_inserta(pos_inicio, n_elems_a_extraer, b);
        escribe_lista(a);
        escribe_lista(b);
        escribe_lista(extracto);
        return true;
  }


int main() {
    while (ejecuta_caso());
    return 0;
}