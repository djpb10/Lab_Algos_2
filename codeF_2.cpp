#include <iostream>
#include <vector>
using namespace std;

void ordenar( vector<int> &lista, int size);

int main(void){

    int tests;
    int n;
    int respuesta;
    vector<int> lista;

    cin >> tests;
    for (int i = 0; i < tests; i++){
        cin >> n;
        lista.clear();
        int temp;
        for (int j = 0; j < n; j++){
            cin >> temp;
            lista.push_back(temp);
        }
        ordenar( lista, n);
        respuesta = 0;
        while ( n >= 2){
            respuesta += (lista[n -1] - lista[n -2]);
            n -= 1;
        }
        cout << respuesta << endl;
    }

    return 0;
}

void ordenar( vector<int> &lista, int size){
    int temp;
    for ( int i = 0; i < size; i++){
        for (int j = i + 1; j < size; j++){
            if ( lista[j] < lista[i]){
                temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
}