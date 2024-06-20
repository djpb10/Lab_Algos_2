#include <iostream>
using namespace std;

/* Código para resolver el problema 
    STACKEZ - Easy Stack 19-06-24*/

// Objeto que será un elemento en la lista enlazada simple
struct Element{
    Element *prev;
    long int  key;

    Element (){
        prev = nullptr;
        key = 0;
    }

};

// Representación de una pila con lista enlazada simple
struct Pila{
    Element *tail;

    Pila(){
        tail = nullptr;
    }

    void apilar( long int x ){
        Element *new_element;
        new_element = new Element;
        
        new_element -> key = x;
        if ( tail == nullptr ){
            tail = new_element;
        }
        else{
            new_element -> prev = tail;
            tail = new_element;
        }

    }
    void desapilar( void ){
        if ( tail != nullptr ){
            Element *old_element;
            old_element = tail;
            tail = tail -> prev;
            delete old_element;  // si se utiliza esta instrucción en el codigo
                                // en el peor caso suma O(n) a nuestra ejecución
        }
    }
    void imprimir_tail( void ){
        if ( tail == nullptr ){
            cout << "Empty!"<< "\n";
        }
        else{
            cout << tail -> key << "\n";
        }
    }
};

int main(){
    // comandos para que el código se ejecute más rápido
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, operador;
    long int entrada;
    Pila lista;
    cin >> t;
    for ( int i = 0; i < t; i++){
        cin >> operador;
        if ( operador == 1 ){
            cin >> entrada;
            lista.apilar( entrada );
        }
        else if ( operador == 2 ){
            lista.desapilar();
        }
        else{
            lista.imprimir_tail();
        }

    }
    
    return 0;
}