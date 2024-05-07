#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// codigo para ordenar un vector
int comprobar( vector<int> &v, int x, int poss);

int main(void){
    
    int count;
    int num;
    long c;
    vector<int> secuencia;
    vector<pair<long,int>> pares;
    pair<int, int> par;
    
    cin >> num;
    cin >> c;

    secuencia.resize(num);

    for (int i = 0; i < num; i++){
        cin >> secuencia[i];
    }
    for ( int i = 0; i < num; i++){

        if (comprobar( secuencia, secuencia[i], i) == 0){
            par.first = secuencia[i];
            count = 0;
            for ( int j = i; j < num; j++){
                if ( secuencia[j] == secuencia[i]){
                    count++;
                }
            }
            par.second = count;
            pares.push_back(par);
        }
    }
    pair<int, int> temp;
    for ( int i = 0; i < pares.size(); i++){
        for (int j = i +1; j < pares.size(); j++){
            if ( pares[j].second > pares[i].second){
                temp = pares[j];
                pares.erase(pares.begin() +j);
                pares.insert(pares.begin() +i, temp);

            }
        }    
    }
    for (int i = 0; i < pares.size(); i++){
        for (int j = 0; j < pares[i].second; j++){
            cout << pares[i].first << " ";
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