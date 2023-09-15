#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Función que define la función f(x) = e^(-x) - x
double f(double x) {
        // return exp(-x)-x;
        //return -0.874 * pow(x, 2) + 1.750 * x + 2.627;
         return -23.330+79.350*x-88.090*x*x+41.600*x*x*x-8.6800 *x*x*x*x+0.658 *x*x*x*x*x;
         //return log(x)-5;
        // return (1-0.6*x)/x;
}

double der(double x) {
    // return -exp(-x)-1;
    //return -1.748*x+1.75;
     return 3.29*x*x*x*x-34.72*x*x*x+124.8 *x*x-176.18*x+79.35;
    // return log(x)-5;
    //return (1-0.6*x)/x;
}

double g(double x) {
    // return exp(-x);
    return x-(f(x)/der(x));
     //return x-f(x)/der(x);
     //return exp(5);
     return 1/0.6;
}

// Función que recorre la función en intervalos y devuelve los límites donde el producto de los extremos es menor que cero
void analPorInt(double inicio, double fin, double tamIntervalo, vector<double> &resultados) {
    double intervaloInicio = inicio;
    double intervaloFin = inicio + tamIntervalo;
    while (intervaloFin <= fin) {
        double multiplicacionExtremos = f(intervaloInicio) * f(intervaloFin);
        if (multiplicacionExtremos < 0) {
            resultados.push_back(intervaloInicio);
            resultados.push_back(intervaloFin);
        }
        intervaloInicio = intervaloFin;
        intervaloFin += tamIntervalo;
    }
}

// Función que implementa el método de punto fijo
double puntoFijo(double aproximacion, double porcentajeError) {
    double x = aproximacion;
    double nuevoX;
    double error = 100.0; // Inicializar el error con un valor grande

    int iteraciones = 0;

    while (error > porcentajeError) {
        nuevoX = g(x);
        error = fabs((nuevoX - x) / nuevoX) * 100.0;
        x = nuevoX;
        iteraciones++;
        cout << " iter: " << iteraciones << " x: " << x << " nuevo X: " << nuevoX << " error: " << error << endl;
    }

    cout << "El metodo convergio despuos de " << iteraciones << " iteraciones." << endl;
    return nuevoX;
}



int main() {
    double x,y,a,b;
    vector<double> resultados, raices;

    analPorInt(-10,200,0.1,resultados);
    cout <<"tamano " << resultados.size()<< endl;
    for (size_t i = 0; i < resultados.size(); i+=2) {
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(puntoFijo( resultados[i], 0.00001)); // intento con lim inf
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(puntoFijo( resultados[i+1], 0.00001)); // intento con lim sup
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
