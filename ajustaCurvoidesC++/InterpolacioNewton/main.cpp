#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// decimos que diferencia dividida es f[X i+1;X i] = (f(X[i+1])-f(X[i]))/X[i+1]-X[i]

// hacer la tabla | X  | Y  |          |             |                |
//                | x0 | y0 | f[X1,x0] | f[x2,X1,x0] | f[x3,x2,X1,x0] |
//                | x1 | y1 | f[X1,x0] | f[x2,X1,x0] |
//                | x2 | y2 | f[X1,x0] |
//                | x3 | y3 |




//definimos las funciones y clases

class NewtonInterpolation {
private:
    int CantDeDatosX; // Número de puntos de interpolación
    std::vector<double> x; // Valores de x
    std::vector<double> y; // Valores de y
    std::vector<std::vector<double>> diferencias_divididas; // Diferencias divididas
    std::vector<double> coeficientes; // Coeficientes del polinomio
public:
    // Constructor que toma los puntos (x, y) de interpolación
    NewtonInterpolation(const std::vector<double>& x_values, const std::vector<double>& y_values) {
        if (x_values.size() != y_values.size()) { //si hay mas datos de x que de y, tirara error
            throw std::invalid_argument("Los vectores x_values e y_values deben tener la misma longitud");
        }

        CantDeDatosX = x_values.size();
        x = x_values;
        y = y_values;
        coeficientes = std::vector<double>(CantDeDatosX); //seteo cantidad de coeficientes del polinomio dependiendo
        // de la caintidad de datos de X

        // Paso 1: Calcular las diferencias divididas de orden cero
        for (int i = 0; i < CantDeDatosX; i++) {
            diferencias_divididas.push_back(std::vector<double>(CantDeDatosX));
            diferencias_divididas[i][0] = y[i];
        }

        // Paso 2: Calcular las diferencias divididas de orden superior
        for (int j = 1; j < CantDeDatosX; j++) {
            for (int i = 0; i < CantDeDatosX - j; i++) {
                diferencias_divididas[i][j] = (diferencias_divididas[i + 1][j - 1] - diferencias_divididas[i][j - 1]) / (x[i + j] - x[i]); //formula de diferecias divididas
            }
        }

        // Paso 3: Los coeficientes del polinomio son las diferencias divididas de orden cero
        for (int i = 0; i < CantDeDatosX; i++) {
            coeficientes[i] = diferencias_divididas[0][i];
        }
    }

    // Función para obtener la expresión del polinomio de Newton
    std::string obtenerExpresion() const {
        std::string expresion = std::to_string(coeficientes[0]);

        // Paso 4: Construir la expresión del polinomio de Newton
        for (int i = 1; i < CantDeDatosX; i++) {
            expresion += " + " + std::to_string(coeficientes[i]);

            for (int j = 0; j < i; j++) {
                expresion += "*(x - " + std::to_string(x[j]) + ")";
            }
        }

        return expresion;
    }

    // Función para imprimir la tabla de diferencias divididas
    void imprimirTablaDiferenciasDivididas() const {
        std::cout << "Tabla de Diferencias Divididas:" << std::endl;
        std::cout << std::setw(5) << "X" << " | " << std::setw(5) << "Y" << " | ";
        for (int i = 1; i <= CantDeDatosX; i++) {
            std::cout << std::setw(15) << "f[X" + std::to_string(i) + "]";
        }
        std::cout << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        for (int i = 0; i < CantDeDatosX; i++) {
            std::cout << std::setw(5) << x[i] << " | " << std::setw(5) << y[i] << " | ";
            for (int j = 0; j < CantDeDatosX - i; j++) {
                std::cout << std::setw(15) << diferencias_divididas[i][j];
            }
            std::cout << std::endl;
        }
    }

    std::string obtenerExpresionSimplificada() const {
        std::string expresion = std::to_string(coeficientes[0]);

        for (int i = 1; i < CantDeDatosX; i++) {
            if (coeficientes[i] != 0) {
                expresion += " + " + std::to_string(coeficientes[i]);

                for (int j = 0; j < i; j++) {
                    expresion += "*(x";
                    for (int k = 0; k <= j; k++) {
                        expresion += " - " + std::to_string(x[k]);
                    }
                    expresion += ")";
                }
            }
        }

        return expresion;
    }

};

int main() {
    // Definir los puntos de interpolación (X, Y)

    //std::vector<double> x_values = {0.0, 1.0, 2.0, 3.0};
    //std::vector<double> y_values = {1.0, 2.7182, 7.3891, 20.0855};

    //std::vector<double> x_values = { 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    //std::vector<double> y_values = {1.0, 2.1190, 2.9100, 3.9450, 5.7200, 8.6950};

    //std::vector<double> x_values = {1.0, 2.0, 3.0, 5.0, 6.0};
    //std::vector<double> y_values = {4.75, 4.0, 5.25, 19.75, 36.0};

    std::vector<double> x_values = {0, 10, 20, 30, 40, 50, 60};
    std::vector<double> y_values = {50000, 35000, 31000, 20000, 19000, 12000, 11000};


    // Crear un objeto de interpolación de Newton
    NewtonInterpolation interpolacion(x_values, y_values);

    // Imprimir la tabla de diferencias divididas
    interpolacion.imprimirTablaDiferenciasDivididas();

    // Obtener la expresión del polinomio de Newton
    std::string expresion = interpolacion.obtenerExpresion();

    // Imprimir la expresión del polinomio de Newton
    std::cout << "El polinomio de Newton es: y = " << expresion << std::endl;


}

