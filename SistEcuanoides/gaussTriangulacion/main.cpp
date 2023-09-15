#include <iostream>
#include <vector>

using namespace std;

// Función para triangular la matriz
void triangularMatriz(vector<vector<double>>& matriz, int n) {
    for (int i = 0; i < n; i++) {
        if (matriz[i][i] == 0) {
            cout << "No se puede triangular la matriz debido a un elemento diagonal igual a cero." << endl;
            return;
        }

        // Eliminar elementos debajo de la diagonal
        for (int j = i + 1; j < n; j++) {
            double factor = matriz[j][i] / matriz[i][i];
            for (int k = i; k <= n; k++) {
                matriz[j][k] -= factor * matriz[i][k];
            }
        }
    }
}

// Función para resolver el sistema de ecuaciones usando retro-sustitución
vector<double> retroSustitucion(vector<vector<double>>& matriz, int n) {
    vector<double> solucion(n);

    for (int i = n - 1; i >= 0; i--) {
        solucion[i] = matriz[i][n];
        for (int j = i + 1; j < n; j++) {
            solucion[i] -= matriz[i][j] * solucion[j];
        }
        solucion[i] /= matriz[i][i];
    }

    return solucion;
}

int main() {
    int n = 3; // Tamaño de la matriz 3x3

    // Inicializar la matriz de coeficientes con los valores proporcionados
  /*
    vector<vector<double>> matriz = {
            {3.0, -0.1, -0.2, 7.85},
            {0.1, 7.0, -0.3, 19.30},
            {0.3, -0.2, 10.0, 71.40}
    };
*/
/*
    vector<vector<double>> matriz = {
            {10, -3, 6, 24.50},
            {1, 8, -2, -9},
            {-2, 4, -9,-50}
    };
*/
/*
    vector<vector<double>> matriz = {
            {1, 7, -3, -51},
            {4, -4, 9, 61},
            {12, -1, 3, 8}
    };
*/
/*
    vector<vector<double>> matriz = {
            {-6, 0, 12, 60},
            {4, -1, -1, -2},
            {6, 8, 0, 44}
    };
*/

    vector<vector<double>> matriz = {
            {5, 4, 0, 25},
            {4, -3, 7, 3},
            {12, 0, 3, 36}
    };

    cout << "Matriz inicial:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz[i][j] << "\t"; // Formateamos la salida con precisión decimal
        }
        cout << endl;
    }
    cout << endl;

    triangularMatriz(matriz, n);

    cout << "Matriz triangular superior:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz[i][j] << "\t"; // Formateamos la salida con precisión decimal
        }
        cout << endl;
    }

    cout << "post retro-sustitucion --------------------------------------------- " << endl;

    vector<double> solucion = retroSustitucion(matriz, n);

    cout << "Solucion:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X" << i + 1 << " = " << solucion[i] << endl;
    }

    return 0;
}
