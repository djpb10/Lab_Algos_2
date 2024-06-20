#include <iostream>
using namespace std;

/* Código para resolver el problema 
    QUEUEEZ - Easy Queue 19-06-24*/


// Objeto que será un elemento en la lista enlazada simple
struct Element{
    long int  key;
    Element *next;

    Element (){
        key = 0;
        next = nullptr;
    }

};

// Representación de una cola con lista enlazada simple
struct Cola{
    Element *head;
    Element *tail;

    Cola(){
        head = nullptr;
        tail = nullptr;
    }

    void encolar( long int x ){
        Element *new_element;
        new_element = new Element;
        
        new_element -> key = x;
        if ( head == nullptr ){
            head = new_element;
            tail = new_element;
        }
        else{
            tail -> next = new_element;
            tail = new_element;
        }

    }
    void desencolar( void ){
        if ( head != nullptr ){
            Element *old_element;
            old_element = head;
            head = head -> next;
            delete old_element;  // si se utiliza esta instrucción en el codigo
                                // en el peor caso suma O(n) a nuestra ejecución
        }
    }
    void imprimir_head( void ){
        if ( head == nullptr ){
            cout << "Empty!"<< "\n";
        }
        else{
            cout << head -> key << "\n";
        }
    }
};

int main(){
    // comandos para que el código se ejecute más rápido
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, operador;
    long int entrada;

    Cola lista;
    cin >> t;
    for ( int i = 0; i < t; i++){
        cin >> operador;
        if ( operador == 1 ){
            cin >> entrada;
            lista.encolar( entrada );
        }
        else if ( operador == 2 ){
            lista.desencolar();
        }
        else{
            lista.imprimir_head();
        }

    }
    
    return 0;
}
