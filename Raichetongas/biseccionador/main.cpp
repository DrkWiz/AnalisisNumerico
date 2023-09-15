#include <bits/stdc++.h>

using namespace std;

double expo(double num, int x) {
    if (x == 0) {
        return 1.0;
    }

    double res = 1.0;
    for (int i = 0; i < x; i++) {
        res *= num;
    }
    return res;
}

double func(double x){
     return exp(-x)-x;
    // return -0.874 * x * x + 1.750 * x + 2.627
    // return -23.330 + 79.350 * x - 88.090 * pow(x, 2) + 41.600 * pow(x, 3) - 8.6800 * pow(x, 4) + 0.658 * pow(x, 5);
    // return log(x)-5;
    // return (1-0.6*x)/x;
}

void analisis(double inicio, double fin, double paso){
    double y;
    for(int i = inicio ; i<=fin; i+=paso){
        y=func(i);
        cout <<" ("<<i<<";"<<y<<") ";
    }
}


double biseccion(double inicio, double fin,double errorP){
    double errorOb=1,c,Canterior,a=inicio,b=fin;

    while(errorOb>errorP){

        Canterior=c;
        c= (a+b)/2;

        if (func(a)*func(c)<0){
            b=c;
        }else{
            a=c;
        }
        errorOb = fabs(c - Canterior);
        cout << "a: " << a << " b: " << b << " c: " << c << " f(a): " << func(a) << " f(c): " << func(c) << " f(a)f(c): " << func(a)*func(c) << " errorOb: "<<errorOb << endl;
    }
    return c;

}


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




int main(){

    double x,y,a,b;
    vector<double> resultados, raices;

    analPorInt(-10,200,0.4,resultados);
    cout <<"tamano " << resultados.size()<< endl;
    for (size_t i = 0; i < resultados.size(); i+=2) {
        cout << "Intervalo donde la multiplicacion de extremos es negativa: (" << resultados[i] << ";" << resultados[i + 1] << ")" << endl;
        raices.push_back(biseccion( resultados[i],  resultados[i+1], 0.00001));
    }

    cout << "la raiz/ces es/son: ";
    for(int i =0; i < raices.size(); i++){
        cout << raices[i] << " ; ";
    }

    return 0;
}
