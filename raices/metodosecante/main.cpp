#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


double func(double x) ;
void analPorInt(double inicio, double fin, double tamIntervalo, vector<double> &resultados);
double Secante(double LimInf, double LimSup,double tolerancia);

int main(){

    double x,y,a,b;
    vector<double> resultados, raices;

    analPorInt(-10,200,0.1,resultados);
    cout <<"tamano " << resultados.size()<< endl;
    for (size_t i = 0; i < resultados.size(); i+=2) {
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(Secante( resultados[i],resultados[i+1], 0.00001));
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



// Función que define la función f(x) = e^(-x) - x
double func(double x) {
    //return exp(-x)-x;
    //return -0.874 * pow(x, 2) + 1.750 * x + 2.627;
    //return -23.330+79.350*x-88.090*x*x+41.600*x*x*x-8.6800 *x*x*x*x+0.658 *x*x*x*x*x;
    //return log(x)-5;
    return (1-0.6*x)/x;
}

// Función que recorre la función en intervalos y devuelve los límites donde el
// producto de los extremos es menor que cero
void analPorInt(double inicio, double fin, double tamIntervalo, vector<double> &resultados) {
    double intervaloInicio = inicio;
    double intervaloFin = inicio + tamIntervalo;
    while (intervaloFin <= fin) {
        double multiplicacionExtremos = func(intervaloInicio) * func(intervaloFin);
        if (multiplicacionExtremos < 0) {
            resultados.push_back(intervaloInicio);
            resultados.push_back(intervaloFin);
        }
        intervaloInicio = intervaloFin;
        intervaloFin += tamIntervalo;
    }
}

double Secante(double LimInf, double LimSup,double tolerancia){

    double fxI,fxS,xsig,errorCalc=1;
    int iteraciones=0;

    cout << "Iteracion: " << iteraciones << " LimInf: " << LimInf << " FX: " << func(LimInf) << " Error: " << errorCalc << endl;
    cout << "Iteracion: " << iteraciones << " LimSup: " << LimSup << " FX: " << func(LimSup) << " Error: " << errorCalc << endl;

    while(errorCalc > tolerancia){
        fxI=func(LimInf);
        fxS=func(LimSup);

        xsig= LimSup - ((fxS*(LimInf-LimSup))/(fxI-fxS));

        errorCalc = fabs(xsig - LimSup);

        LimInf=LimSup;
        LimSup=xsig;

        iteraciones++;

        cout<< "iteraciones: " << iteraciones << " LimSup: " << LimSup <<" FX" << func(LimSup) << " Error: " << errorCalc<< endl;
    }
return LimSup;
}