#include <iostream>
using namespace std;

/* Código para resolver el problema de 
    BSEARCH1 - Binary search 04-07-24 
    Implementación de árbol binario de 
    búsqueda rojo-negro con almacenamiento
    de la posición de la aparción de la clave*/

struct Nodo{
    Nodo *padre;      // almacena al padre
    long long key;    // almacena la clave
    Nodo *left;       // alamcena el hijo izquierdo 
    Nodo *right;      // almacena el hijo derecho
    int color;        // definí el color rojo como 1 y negro como 0
    int poss;         // almacena la posición en la que es alamacenado como si fuera un arreglo

    Nodo(){
        padre = nullptr;
        key = 0;
        left = nullptr;
        right = nullptr;
        color = 1;    // color rojo por defecto
    }

};

struct Tree{
    Nodo *root;     // apundador a la raiz    
    Nodo *nil;      // centinela

    Tree(){
        nil = new Nodo;
        /* el centinela tiene colo negro para cumplir con la 
            propiedad de que todas las hojas son negras */
        nil -> color = 0;
        root = nil; // inicialmente la raiz apunta a nill 

    }
    void left_rotation( Nodo *x ){
        /* Realiza una rotación a izquierda de un nodo x.
            Toma como parametro un apuntador al nodo.
            La salida es 'void' pues modifica el arbol*/
        Nodo  *right_son; 
        right_son = x -> right;

        if ( right_son != nil ){ 
            /* La rotación a izquierda es válida si el hijo 
               derecho del nodo a mover es distinto de nill.     
               Se le asignan a derecha los hijos a izquierda
               del hijo izquierdo del hijo derecho del nodo.*/
            x -> right = right_son -> left;     
            if ( right_son -> left != nil ){    
                right_son -> left -> padre = x;
            }
            right_son -> padre = x -> padre;
            if ( x -> padre == nil ){
                /*Si el nodo no tiene padre entonces se trata de
                  la raiz, el nodo a derecha será la nueva raiz*/
                root = right_son;
            }
            else if ( x == x -> padre -> left ){
                x -> padre -> left = right_son;
            }
            else{
                x -> padre -> right = right_son;
            }
            x -> padre = right_son;
            right_son -> left = x;
        }
    }
    void right_rotation( Nodo *x ){
        /* Realiza una rotación a derecha de un nodo x.
            Toma como parametro un apuntador al nodo.
            La salida es 'void' pues modifica el arbol*/
        Nodo *left_son;
        left_son = x -> left;

        if ( left_son != nil ){
            /* La rotación a derecha es válida si el hijo 
               izquierdo del nodo a mover es distinto de nill.     
               Se le asignan a izquierda los hijos a derecha
               del hijo derecho del hijo izquierdo del nodo.*/
            x -> left = left_son -> right;
            if ( left_son -> right != nil ){
                left_son -> right -> padre = x;
            }
            left_son -> padre = x -> padre;
            if ( x -> padre == nil ){
                /*Si el nodo no tiene padre entonces se trata de
                  la raiz, el nodo a derecha será la nueva raiz*/
                root = left_son;
            }
            else if( x == x -> padre -> left ){
                x -> padre -> left = left_son;
            }
            else{
                x -> padre -> right = left_son;
            }
            x -> padre = left_son;
            left_son -> right = x;
        }

    }

    void correctness( Nodo *z ){

        
        while ( z -> padre -> color == 1 ){
            Nodo *y;
            y = z -> padre -> padre;                    // asignación del abuelo de z

            if ( z -> padre == z -> padre -> padre -> left ){

                //caso 1
                if ( y -> right -> color == 1 ){        // se evalua el tío de z (en rojo)
                    z -> padre -> color = 0;            // padre de z (negro)
                    y -> color = 1;                     // abuelo de z (rojo)
                    y -> right -> color = 0;            // tio de z (negro)
                    z = y;                              // apuntamos al abuelo de z
                }
                //caso 2
                else {
                    if ( z == z -> padre -> right  ){  // se evalua si z es hijo a derecha
                        z = z -> padre;                // apuntamos al padre de z
                        left_rotation( z );            // rotamos a izquierda al padre de z
                    }
                // caso 3
                    z -> padre -> color = 0;                // color (negro)
                    z -> padre -> padre -> color = 1;       // abuelo de (rojo)
                    right_rotation( z -> padre -> padre );  // rotación a derecha del abuelo de z
                }
            }
        
            else{
                //caso 1
                if ( y -> left -> color == 1 ){        // se evalua si el tío de z es rojo
                    z -> padre -> color = 0;           // padre de z (negro)
                    y -> color = 1;                    // abuelo de z (rojo)
                    y -> left -> color = 0;            // tio de z (negro)
                    z = y;                             // apuntamos al abuelo de z
                }
                //caso 2
                else{ 
                    if ( z == z -> padre -> left  ){  // se evalua si z es hijo a izquierda
                        z = z -> padre;               
                        right_rotation( z );          // rotación a derecha del padre de z
                        }
                // caso 3
                    z -> padre -> color = 0;                // padre de z (negro)
                    z -> padre -> padre -> color = 1;       // abuelo de z (rojo)
                    left_rotation( z -> padre -> padre );   // rotamos a izquierda el abuelo de z
                }
            }
        }
        root -> color = 0;      // por si a las moscas siempre a negro
    }

    void insert( long long key , int poss){
        /* Parte desde la raiz realizando comparaciones para verificar
            a que lado del arbol pertenece la calve hasta llegar a una hoja*/
        Nodo *new_element;
        new_element = new Nodo;
        new_element -> padre = nil;     // propiedad de hoja negra
        new_element -> left = nil;      // propiedad de hoja negra
        new_element -> right = nil;     // propiedad de hoja negra

        new_element -> key = key;
        new_element -> poss = poss;     // posición de entrada como si fuera un arreglo

        Nodo *current;
        Nodo *padre;
        current = root;
        padre = nil;

        while ( current != nil ){       // aseguramos que no estamos en una hoja
            padre = current;            // apuntamos al elemento actual para antes de movernos
            if ( key < current -> key ){    // propiedad de lado izquierdo de A. binario de búsqueda
                current = current -> left;
            }
            else{                       // propiedad de lado derecha de A. binario de búsqueda
                current = current -> right;
            }
        }

        if ( padre == nil ){
            root = new_element;
        }
        else if ( key < padre -> key ){
            new_element -> padre = padre;
            padre -> left = new_element;
        }
        else{
            new_element -> padre = padre;
            padre -> right = new_element;
        }
        correctness( new_element );     // luego de insertar preservamos las propiedades

    }

    int search( long long key ){
        /* Parte desde un apuntador de la raiz haciendo comparaciones
            de la misma forma como si de inserción se tratace hasta 
            conseguir el nodo que tiene la clave buscada y retornar 
            el atributo 'poss' en caso contrario retorna -1*/
        int poss = -1;
        Nodo *current;
        current = root;
        while ( current != nil ){
            if ( key == current -> key ){
                poss = current -> poss;
                break;
            }
            else if ( key <= current -> key ){
                current = current -> left;
            }
            else{
                current = current -> right;
            }
        }
        return poss ;
    }

    void inorder( Nodo *x ){
        /* Imprime las claves de los nodos en orden.
            Solo se empleó esta función para verificar
            el correcto almacenamiento de los nodos en 
            arbol.*/
        
        if ( x != nil ){
            inorder( x -> left );
            cout << x -> key << " ";
            inorder( x -> right );
        }
        
    }

};

int main( void ){
    // código para más velocidad
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    Tree arbol;
    int n;
    long long key;
    int consultas;
    cin >> n >> consultas;

    for ( int i = 0; i < n; i ++){
        
        cin >> key;
        // se revisa primero si el elemento se encuentra
        // esto evita que la primera coincidencia sea un 
        // elemento cuya aparición repetida sea posterior
        if ( arbol.search(key) == -1){
            arbol.insert( key, i );
        }    
    }
    
    for ( int i = 0; i < consultas; i++ ){
        cin >> key;
        cout << arbol.search(key) << "\n";
    }

    return 0;
}

