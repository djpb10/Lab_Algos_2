#include <iostream>
#include <vector>
using namespace std;
 
vector<vector<uint64_t>> strassen( vector<vector<uint64_t>> &A, vector<vector<uint64_t>> &B, uint32_t n);
 
int main(){
    uint32_t n;
    uint32_t d1, p1, r1, m1, d2, r2, p2, m2;
    // input
    
    cin >> n >> p1 >> d1 >> r1 >> m1 >> p2 >> d2 >> r2 >> m2;
    // arrays
    vector<vector<uint64_t>> A(n , vector<uint64_t> (n)), B(n , vector<uint64_t> (n));
    vector<vector<uint64_t>> C(n , vector<uint64_t> (n));
    vector<uint64_t> V(n);
    
    for ( uint32_t i = 0; i < n; ++i){
        for ( uint32_t j = 0; j < n; ++j) {
            d1 = d1 * p1 + r1;
            d2 = d2 * p2 + r2;
            A[i][j] = d1 >> (32 - m1);
            B[i][j] = d2 >> (32 - m2);
        }
    }
    C = strassen( A, B, n);
 
    for (uint32_t i=0; i<n; ++i){ 
        V[i] = 0;
        for (uint32_t j=0; j<n; ++j){
            V[i] ^= C[i][j];
        }
    }
    for ( uint32_t i = 0; i < n; i++){
        cout << V[i] << " ";
    }
    return 0;
}
 
 
vector<vector<uint64_t>> strassen( vector<vector<uint64_t>> &A, vector<vector<uint64_t>> &B, uint32_t n){
    if ( n == 1) return {{A[0][0]*B[0][0]}};
    else{
    //Se computan las submatrices
        vector<vector<uint64_t>> C(n, vector<uint64_t> (n));
        vector<vector<uint64_t>> A_11(n/2, vector<uint64_t> (n/2)), 
                            A_12(n/2, vector<uint64_t> (n/2)),
                            A_21(n/2, vector<uint64_t> (n/2)),
                            A_22(n/2, vector<uint64_t> (n/2)),
                            B_11(n/2, vector<uint64_t> (n/2)),
                            B_12(n/2, vector<uint64_t> (n/2)),
                            B_21(n/2, vector<uint64_t> (n/2)),
                            B_22(n/2, vector<uint64_t> (n/2));
                            
        vector<vector<uint64_t>> P_1,
                                 P_2,
                                 P_3,
                                 P_4,
                                 P_5,
                                 P_6,
                                 P_7;

        // Multiplicaciones de strassen
        vector<vector<uint64_t>> S1(n/2, vector<uint64_t> (n/2)), S2(n/2, vector<uint64_t> (n/2)), 
        S3(n/2, vector<uint64_t> (n/2)), S4(n/2, vector<uint64_t> (n/2))
        , S5(n/2, vector<uint64_t> (n/2)), S6(n/2, vector<uint64_t> (n/2)), S7(n/2, vector<uint64_t> (n/2)), 
        S8(n/2, vector<uint64_t> (n/2)), S9(n/2, vector<uint64_t> (n/2)), S10(n/2, vector<uint64_t> (n/2));
 
        for ( int i = 0; i < n/2; i++){    
            for ( int j = 0; j < n/2; j++){

                A_11[i][j] = A[i][j];
                B_11[i][j] = B[i][j];

                A_12[i][j] = A[i][j + n/2];
                B_12[i][j] = B[i][j + n/2];

                A_21[i][j] = A[i + n/2][j];
                B_21[i][j] = B[i + n/2][j];

                A_22[i][j] = A[i + n/2][j + n/2];
                B_22[i][j] = B[i + n/2][j + n/2];
            
                S1[i][j] = B[i][j + n/2] - B[i + n/2][j + n/2];
                S2[i][j] = A[i][j] + A[i][j + n/2];
                S3[i][j] = A[i + n/2][j] +  A[i + n/2][j + n/2];
                S4[i][j] = B[i + n/2][j] -  B[i][j];
                S5[i][j] = A[i][j] + A[i + n/2][j + n/2];
                S6[i][j] = B[i][j] + B[i + n/2][j + n/2];
                S7[i][j] = A[i][j + n/2] - A[i + n/2][j + n/2];
                S8[i][j] = B[i + n/2][j] + B[i + n/2][j + n/2];
                S9[i][j] = A[i][j] - A[i + n/2][j];
                S10[i][j] = B[i][j] + B[i][j + n/2];
            }
        }

        P_1 = strassen( A_11, S1, n/2);
        P_2 = strassen( S2, B_22, n/2);
        P_3 = strassen( S3, B_11, n/2);
        P_4 = strassen( A_22, S4, n/2);
        P_5 = strassen( S5, S6, n/2);
        P_6 = strassen( S7, S8, n/2);
        P_7 = strassen( S9, S10, n/2);

        for (int i = 0; i < n/2; i++) {
            for (int j = 0; j < n/2; j++) {
                C[i][j] = P_5[i][j] + P_6[i][j] + (P_4[i][j] - P_2[i][j]);
                C[i][j + n/2 ] = P_1[i][j] + P_2[i][j];
                C[i + n/2][j] = P_3[i][j] + P_4[i][j];
                C[i + n/2][j + n/2 ] = P_5[i][j] + P_1[i][j] - (P_3[i][j] + P_7[i][j]);
            }
        }

        return C;
 
 
    }
 
}
