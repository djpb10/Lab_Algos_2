#include <iostream>
#include <math.h>
#include <vector>
#include <utility>
using namespace std;


//Prototipos
void selection_sort( vector<pair<long long, int>> &arreglo, int n);
void separacion( vector<pair<long long, int>> &arreglo, vector<pair<long long, int>> &part1, vector<pair<long long, int>> &part2);
void merge( vector<pair<long long, int>> &arreglo, vector<pair<long long, int>> &part1, vector<pair<long long, int>> part2);
void merge_sort( vector<pair<long long, int>> &arreglo, int n);


int main(){
    int n, tests;
    long long score;
    vector<pair<long long, int>> poss;
    vector<int> ans;

    cin >> tests;
    for ( int test = 0; test < tests; test++){
        score = 0;
        cin >> n;
        poss.resize(n);
        ans.resize(n);

        for( int elemento = 0; elemento < n; elemento++){
            cin >> poss[elemento].first;
            poss[elemento].second = elemento;
        }
        
        merge_sort(poss, n);
        
        int k = 0;
        long long temp;
        for ( int i = 0; i < n; i++){
            /* Lo que se encuentra comentado más abajo del "if" era la primera versión del código que había escrito, 
                diferente al que vimos en clase; no pude usar esa forma porque el código era muy lento,
                pensaba que era merge_sort pero era cuestión de ese condicional (lo envíe como 8 veces).
                En verdad no veo muy bien porque mejora el tiempo de ejecución y bueno lo pongo por 
                acá para consultarte para salir de dudas*/
            if ( i == k){
                score += poss[i].first;
                k++;
            }
            //score += poss[i].first;
            //temp = score;
            //k = i + 1;
            while ( k < n && score >= poss[k].first){
                score += poss[k].first;
                k ++;
            }
            ans[poss[i].second] = k-1;

        }
        for( int j = 0; j < n; j++){
            cout << ans[j] << " ";
        }
        cout << endl;

    }
    
    return 0;
}

// Versión de merge_sort
void merge_sort( vector<pair<long long, int>> &arreglo, int n){
    /* Si el vector es lo suficientemente pequeño lo ordena con el procedimiento
        "selection_sort".
        En caso contrario, separa el vector original en dos mitades no necesariamente iguales 
        para luego volver a llamarse a sí mismo. Finalmente llama al procedimiento
        "merge" que las vuelve a unir de forma ordenada en el vector original*/
    vector<pair<long long, int>> part1, part2;

    if ( arreglo.size() <= 4) selection_sort(arreglo, arreglo.size());
    else{
        separacion( arreglo, part1, part2);
        merge_sort(part1, part1.size());
        merge_sort(part2, part2.size());
        merge( arreglo, part1, part2);
    }     
}

void merge( vector<pair<long long, int>> &arreglo, vector<pair<long long, int>> &part1, vector<pair<long long, int>> part2){
    /* Recibe el vector y sus dos mitades que se supone están ordenadas.
        Itera sobre ambas asignando los elementos en orden en el vector original*/
    int i = 0, j = 0;
    pair<long long, int> centinela;

    centinela.first = pow(10,10);
    centinela.second = pow(10,8);

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
void separacion( vector<pair<long long, int>> &arreglo, vector<pair<long long, int>> &part1, vector<pair<long long, int>> &part2){
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

void selection_sort( vector<pair<long long, int>> &arreglo, int n){
    pair<long long , int > temp;
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

