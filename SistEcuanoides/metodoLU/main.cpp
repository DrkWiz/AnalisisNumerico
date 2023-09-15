#include <iostream>
#include <vector>

using namespace std;

// Función para realizar la descomposición LU
void descomponerconLU(vector<vector<double>>& matrizA, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = matrizA.size();

    for (int i = 0; i < n; i++) {
        // generacion de Matriz U
        for (int k = i; k < n; k++) {
            double suma = 0.0;
            for (int j = 0; j < i; j++) {
                suma += L[i][j] * U[j][k];
            }
            U[i][k] = matrizA[i][k] - suma;
        }

        // generacion de Matriz L
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1.0;
            } else {
                double suma = 0.0;
                for (int j = 0; j < i; j++) {
                    suma += L[k][j] * U[j][i];
                }
                L[k][i] = (matrizA[k][i] - suma) / U[i][i];
            }
        }
    }
}

// Función para resolver el sistema de ecuaciones usando la descomposición LU
vector<double> resolvedorDeLU(vector<vector<double>>& L, vector<vector<double>>& U, vector<double>& b) {
    int n = L.size();
    vector<double> y(n);
    vector<double> x(n);

    // se resuelve Ly = b
    for (int i = 0; i < n; i++) {
        double suma = 0.0;
        for (int j = 0; j < i; j++) {
            suma += L[i][j] * y[j];
        }
        y[i] = b[i] - suma;
    }

    // se resuelve Ux = y
    for (int i = n - 1; i >= 0; i--) {
        double suma = 0.0;
        for (int j = i + 1; j < n; j++) {
            suma += U[i][j] * x[j];
        }
        x[i] = (y[i] - suma) / U[i][i];
    }

    return x;
}

int main() {
/*
    vector<vector<double>> A = {
            {3.0, -0.1, -0.2},
            {0.1, 7.0, -0.3},
            {0.3, -0.2, 10.0}
    };

    vector<double> b = {7.85, 19.30, 71.40};
*/
/*
    vector<vector<double>> A = {
            {10, -3, 6},
            {1, 8, -2},
            {-2, 4, -9}
    };

    vector<double> b = {25.50, -9, -50};
*/
/*
    vector<vector<double>> A = {
            {1, 7, -3},
            {4, -4, 9},
            {12, -1, 3}
    };

    vector<double> b = {-51, 61, 8};
*/
/*
    vector<vector<double>> A = {
            {-6, 0, 12},
            {4, -1, -1},
            {6, 8, 0}
    };

    vector<double> b = {60, -2, 44};

*/
    vector<vector<double>> A = {
            {5, 4, 0},
            {4, -3, 7},
            {12, 0, 3}
    };


    vector<double> b = {25, 3, 36};

    int n = A.size();
    vector<vector<double>> L(n, vector<double>(n, 0.0)); // Inicializar matriz L con ceros
    vector<vector<double>> U(n, vector<double>(n, 0.0)); // Inicializar matriz U con ceros

    descomponerconLU(A, L, U);

    cout << "Matriz L:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << L[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Matriz U:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << "\t";
        }
        cout << endl;
    }

    vector<double> solucion = resolvedorDeLU(L, U, b);

    cout << "Solución:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i + 1 << " = " << solucion[i] << endl;
    }

    return 0;
}
