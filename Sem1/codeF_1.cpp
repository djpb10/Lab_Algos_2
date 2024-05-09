#include <iostream>
#include <vector>
using namespace std;

/* Codigo del problema A - Card Exchange 
    de code forces 8-05-24 */

void ordenar( vector<int> &lista, int size);

int main(){

    int temp;
    int test;
    int k;
    int n;
    vector<int> cards;

    cin >> test;
    for (int i = 0; i < test; i++){

        cin >> n;
        cin >> k;
        temp = 0;
        cards.clear();

        for (int j = 0; j < n; j++){
            cin >> temp;
            cards.push_back(temp);
        }
        
        int op = 1;
        int count;
        int poss;
        int size;
        while ( cards.size() >= k && op == 1){
            op = 0; // Evita que entre en bucle infinito
            ordenar(cards, cards.size());
            count = 0;
            size = cards.size();
            poss = -1;
            // Busca la posición de la carta que cumple k repeticiones
            for ( int i = 0; i < size; i++){
                count = 0;
                for (int j = i; j < size; j++){
                    if ( cards[j] == cards[i]){
                        count++;
                    }
                    else break;
                }
                if ( count >= k){
                    op = 1;
                    poss = i;
                }
            }
            // Procede a eliminar el intervalo donde se encuentran las k cartas
            // Agrega k-1 cartas iguales a la primera
            if ( poss != -1){
                cards.erase(cards.begin() + poss, cards.begin() + poss + k);
                for ( int i = 0; i < k-1; i++){
                    cards.push_back(cards[0]);
                }
            }    
        }
    cout << cards.size() << endl;
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
