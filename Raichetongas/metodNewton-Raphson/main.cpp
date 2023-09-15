#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Función que define la ecuación para la cual deseamos encontrar la raíz
double ecuacion(double x) {
    //return exp(-x)-x;
    //return -0.874 * pow(x, 2) + 1.750 * x + 2.627;
    //return -23.330+79.350*x-88.090*x*x+41.600*x*x*x-8.6800 *x*x*x*x+0.658 *x*x*x*x*x;
    return log(x)-5;
    // return (1-0.6*x)/x;
}

// Derivada de la función ecuación
double derivada(double x) {
    //return -exp(-x) - 1;
    //return -1.748*x+1.75;
    //return 3.29*x*x*x*x-34.72*x*x*x+124.8 *x*x-176.18*x+79.35;
    return 1/x;
    //return -1/(x*x);
}

// Método de Newton-Raphson para encontrar una raíz
double newtonRaphson(double estimacion, double tolerancia) {
    double x = estimacion;
    double error = 1; // Inicializar el error con un valor mayor que la tolerancia

    int iteraciones = 0;

    while (error > tolerancia) {
        double fx = ecuacion(x);
        double dfx = derivada(x);

        double xNuevo = x - fx / dfx;
        error = fabs(xNuevo - x);

        cout << "x: " << x << " f(x): " << fx << " f'(x): " << dfx << " error: " << error << endl;

        x = xNuevo;

        iteraciones++;


    }
    return x;
}

void analPorInt(double inicio, double fin, double tamIntervalo, vector<double> &resultados) {
    double intervaloInicio = inicio;
    double intervaloFin = inicio + tamIntervalo;
    while (intervaloFin <= fin) {
        double multiplicacionExtremos = ecuacion(intervaloInicio) * ecuacion(intervaloFin);
        if (multiplicacionExtremos < 0) {
            resultados.push_back(intervaloInicio);
            resultados.push_back(intervaloFin);
        }
        intervaloInicio = intervaloFin;
        intervaloFin += tamIntervalo;
    }
}

int main() {
    double x,y,a,b;
    vector<double> resultados, raices;

    analPorInt(-10,200,0.1,resultados);
    cout <<"tamano " << resultados.size()<< endl;
    for (size_t i = 0; i < resultados.size(); i+=2) {
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(newtonRaphson( resultados[i], 0.00001)); // intento con lim inf
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(newtonRaphson( resultados[i+1], 0.00001)); // intento con lim sup
    }
    cout << "la raiz/ces es/son: ";
    for(int i =0; i < raices.size(); i+=2){
        cout << raices[i] << " ; ";
    }
    for(int i =1; i < raices.size(); i+=2){
        cout << raices[i] << " ; ";
    }

    return 0;
}
