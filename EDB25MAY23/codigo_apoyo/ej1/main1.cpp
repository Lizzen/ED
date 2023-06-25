// NO MODIFIQUES NADA DE LO QUE APARECE EN ESTE FICHERO

#include <iostream>
#include <string>
#include "pila.h"

using namespace std;


bool ejecuta_caso() {
    int n;
    cin >> n;
    if (n == -1) return false;
    else {
        Pila<int> p;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            p.apila(v);
        }
        Pila<int> resto =  p.hanoificar();
        p.imprime();
        cout << "#";
        resto.imprime();
        cout << endl;
      }
      return true;
  }


int main() {
    while (ejecuta_caso());
    return 0;
}