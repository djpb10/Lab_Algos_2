#include <iostream>
using namespace std;

int main(){
    short int x;
    while (true){
        cin >> x;
        if (x == 42){
            break;
        }
        cout << x << endl;
    }
    return 0;
}
