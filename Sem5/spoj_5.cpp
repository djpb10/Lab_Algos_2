#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

/* Codigo para resolver el problema 
    RK Sorting 31-05-24 */

class tripleta{
    public:
        unsigned long valor;
        int repet;
        int poss;
};


// codigo tuplaa ordenar un vector
int comprobar( vector<int> &v, int x, int poss);
void max_heapify( vector<tripleta> &A, int poss, int n);
void build_max_heap( vector<tripleta> &A, int n);
void heapsort( vector<tripleta> &A, int n);

int main(void){
    /* Luego de almacenados los números el programa itera sobre el vector para determinar el numero de apariciones.
        Almacena el número como primera coordenada en un vector de tripletas, pero solo en su primera aprición;
        la segunda coordenada será el número de veces que este se encuentra en vector inicial
        y finalmente la tercera coordenada será su primera aparición cuando son introducidos. Luego, itera sobre las 
        segundas coordenadas de las tripletas de este nuevo vector para determinar cual tiene más repeticiones, una vez
        determina cual tiene mayor lo coloca al inicio del vector o antes del menor inmediato; en el caso de ser iguales
        itera sobre la tercera coordenada para cumplir con el orden de aparición de los elementos.
        Finalmente, imprime las primeras coordenadas tantas veces como la segunda coordenada indique 
        en el mismo orden en que se encuentran. */
    
    int count;
    int num;
    unsigned long c;
    vector<int> secuencia;
    vector<tripleta> tuplas;
    tripleta tupla;
    
    cin >> num;
    cin >> c;

    secuencia.resize(num);

    for (int i = 0; i < num; i++){
        cin >> secuencia[i];
    }
    for ( int i = 0; i < num; i++){

        if (comprobar( secuencia, secuencia[i], i) == 0){
            /* Verifica que no haya tomado ya el número
                Si no está cuenta las repeticiones y crea el 
                par ordenado, la primera coordenada con el número
                y la segunda con el número de repeticiones */
            tupla.valor = secuencia[i];
            tupla.poss = i;
            count = 0;
            for ( int j = i; j < num; j++){
                if ( secuencia[j] == secuencia[i]){
                    count++;
                }
            }
            tupla.repet = count;
            tuplas.push_back(tupla);
        }
    }
    /* Reordena la lista de "tripletas" de acuerdo con el número de repeticiones
        de cada número, mayor número de repeticiones lo coloca al principio
        de la lista con "heapsort"; luego, para misma cantidad de repeticiones reorganiza 
        la lista para que el elemento que fue inicializado primero aparezca primero */
    heapsort( tuplas, tuplas.size());

    for ( int i = 0 ; i < tuplas.size(); i++){
        for (int j = i +1; j < tuplas.size(); j++){
            if ( tuplas[i].repet == tuplas[j].repet && tuplas[i].poss > tuplas[j].poss){
                swap( tuplas[i], tuplas[j]);
            }
        }
        
    }
  
    for (int i = 0; i < tuplas.size(); i++){
        for (int j = 0; j < tuplas[i].repet; j++){
            cout << tuplas[i].valor << " ";
        }
    }
    return 0;
}

int comprobar( vector<int> &v, int x, int poss){
    for (int i = 0; i < poss; i++){
        if (v[i] == x) return 1;
    }
    return 0;
}

void heapsort( vector<tripleta> &A, int n){
    build_max_heap( A, n);
    for (int i = 0; i < n; i++){
        swap(A[0], A[n-1-i]);
        max_heapify( A, 0, n-1-i);
    }

}
void build_max_heap( vector<tripleta> &A, int n){
    int count = n/2;
    while ( count >= 0){
        max_heapify(A, count, n);
        count--;
    }
}

void max_heapify( vector<tripleta> &A, int poss, int n){
    int izq = poss*2;
    int der = poss*2 + 1;
    int smallest = poss;
    
    if ( izq < n && A[izq].repet < A[smallest].repet ) smallest = izq;
    if ( der < n && A[der].repet < A[smallest].repet ) smallest = der;

    if ( smallest != poss ){
        swap(A[poss], A[smallest]);
        max_heapify( A, smallest, n);
    }

}



