#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

// Función para realizar la eliminación gaussiana paso a paso
void eliminacionGaussianaPasoAPaso(vector<vector<double>>& matriz, int n) {
    for (int i = 0; i < n; i++) {
        // Pivoteo parcial: encontrar la fila con el valor máximo en la columna actual
        int filaMax = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(matriz[j][i]) > abs(matriz[filaMax][i])) {
                filaMax = j;
            }
        }

        // Intercambiar filas si es necesario
        if (filaMax != i) {
            swap(matriz[i], matriz[filaMax]);
        }

        // Mostrar la matriz en esta iteración
        cout << "Iteración " << i + 1 << ":" << endl;
        for (int k = 0; k < n; k++) {
            for (int j = 0; j <= n; j++) {
                cout << matriz[k][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;

        // Hacer que el elemento diagonal sea igual a 1
        double divisor = matriz[i][i];
        for (int j = i; j <= n; j++) {
            matriz[i][j] /= divisor;
        }

        // Eliminar otras filas
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = matriz[j][i];
                for (int k = i; k <= n; k++) {
                    matriz[j][k] -= factor * matriz[i][k];
                }
            }
        }
    }
}


int main() {
    int n = 3; // Tamaño de la matriz 3x3

    // Inicializar la matriz de coeficientes con los valores proporcionados
    vector<vector<double>> matriz1 = {
            {3.0, -0.1, -0.2, 7.85},
            {0.1, 7.0, -0.3, 19.30},
            {0.3, -0.2, -10.0, 71.40}
    };

    vector<vector<double>> matriz2 = {
            {3.0, -0.1, -0.2, 7.85},
            {0.1, 7.0, -0.3, 19.30},
            {0.3, -0.2, -10.0, 71.40}
    };

    cout << "Matriz inicial:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz1[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    eliminacionGaussianaPasoAPaso(matriz1, n);

    cout << "Matriz reducida:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << matriz1[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "Matriz reducida Solucion:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << matriz1[i][n] << endl;
    }
    cout << endl;



    return 0;
}
