#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

// Prototipos
void insertion_sort( vector<int> &arreglo, int n);
void separacion( vector<int> &arreglo, vector<int> &part1, vector<int> &part2);
void merge( vector<int> &arreglo, vector<int> &part1, vector<int> part2);
void merge_sort( vector<int> &arreglo, int n);
bool comprobar( vector<int> &arreglo, int distance, int C);

int main(void){
    /* Almacena cada puesto donde es posible colocar una vaca y ordena este vector
        de forma ascendente. Luego, aplica el concepto de busqueda binaria para
        iterar sobre el vector de modo que usa el mismo número de cada puesto para
        comprobar si efectivamente es posible asignar las vacas con esa distancia
        que finalmente prueba ser la mayor de las menores posibles (el infimo de ellas) */
    int tests;
    int C;
    int N;
    int sol;
    vector<int> puestos;

    cin >> tests;
    for (int i = 0; i < tests; i++){
        puestos.clear();
        cin >> N >> C;
        int temp;
        for (int j = 0; j < N; j++){
            cin >> temp;
            puestos.push_back(temp);
        }
        
        // Acomoda los elementos de forma ascendente
        merge_sort( puestos, N);
        int der = puestos[N-1], izq = puestos[0];
        int k ;

        // Aplica Busqueda binaria para encontrar la minima distancia mas larga
        while ( izq <= der){
            k = (der + izq) / 2;
            if ( comprobar( puestos, k, C)) izq = k +1;
            else der = k -1;
        }
        sol = izq -1; // Por alguna razon no se si es el lenguaje en la pagina si pongo k no agarra
        cout << sol << endl;
    }
    return 0;
}


bool comprobar( vector<int> &arreglo, int distance, int C){
    /* Funcion que comprueba si con la distancia se pueden colocar las 
    vacas en las posiciones que hay disponibles en el arreglo*/
    
    int cows = 1;
    int anterior = arreglo[0];
    for ( int i = 1; i < arreglo.size(); i++){
        if (( arreglo[i] - anterior) >= distance){
            cows++;
            anterior = arreglo[i];
        }
    }
    if (cows >= C) return true;
    else return false;
}


/* Funciones que componen a merge-sort para sortear los elemenetos*/
void merge_sort( vector<int> &arreglo, int n){
    /* Si el vector es lo suficientemente pequeño lo ordena con el procedimiento
        "selection_sort".
        En caso contrario, separa el vector original en dos mitades no necesariamente iguales 
        para luego volver a llamarse a sí mismo. Finalmente llama al procedimiento
        "merge" que las vuelve a unir de forma ordenada en el vector original*/
    vector<int> part1, part2;

    if ( arreglo.size() <= 2) insertion_sort(arreglo, arreglo.size());
    else{
        separacion( arreglo, part1, part2);
        merge_sort(part1, part1.size());
        merge_sort(part2, part2.size());
        merge( arreglo, part1, part2);
    }     
}

void merge( vector<int> &arreglo, vector<int> &part1, vector<int> part2){
    /* Recibe el vector y sus dos mitades que se supone están ordenadas.
        Itera sobre ambas asignando los elementos en orden en el vector original*/
    int i = 0, j = 0;
    int centinela = pow(10,9);
    part1.push_back(centinela);
    part2.push_back(centinela);
    for (int k = 0; k < arreglo.size(); k++){
        if ( part1[i] < part2[j]){
            arreglo[k] = part1[i];
            i++;
        }
        else{
            arreglo[k] = part2[j];
            j++;
        }

    }

}
void separacion( vector<int> &arreglo, vector<int> &part1, vector<int> &part2){
    /* Asigna los elementos del vector en dos nuevos vectores que poseen respectivamente la 
        mitad de sus elementos*/
    int mitad = arreglo.size() / 2;

    for (int i = 0; i < mitad ; i++){
        part1.push_back(arreglo[i]);
    }
    for (int i = mitad; i < arreglo.size(); i++){
        part2.push_back(arreglo[i]);
    }

}

void insertion_sort( vector<int> &arreglo, int n){
    // En realidad se debería llamar selection_sort pero se me pasó cambiarlo antes de mandarlo
    int temp;
    for ( int i = 0; i < n; i++){
        for ( int j = i+1; j < n; j++){
            if ( arreglo[j] < arreglo[i]){
                temp = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = temp;
            }
        }
    }
}
