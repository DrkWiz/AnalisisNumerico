#include <iostream>
#include <vector>

using namespace std;

void SumatoriaXporY(double equis,double ye, double &resultado){
resultado += equis * ye;
}

void SumatoriaEquis(double equis, double &resultado){
resultado += equis;
}

void SumatoriaYe(double ye, double &resultado){
    resultado += ye;
}

void SumatoriaEquisCuadrados(double equis, double &resultado){
    resultado += equis * equis;
}

double Promedio(vector<double> &datos){
    double resultado = 0;
    for (double num: datos) { resultado += num; }
    return resultado/datos.size();
}

double pendiente(vector<double> &equis, vector<double> &ye){
    double n = equis.size();
    double sXY =0;
    double sX=0,sY = 0, sXsY=0;
    double sX2 = 0;

    for (int i=0; i < n ; i++){
        SumatoriaXporY(equis[i],ye[i],sXY);
        SumatoriaEquis(equis[i],sX);
        SumatoriaYe(ye[i],sY);
        SumatoriaEquisCuadrados(equis[i],sX2);
    }
    sXsY=sX*sY;

    return ((n*sXY-sXsY)/(n*sX2-sX*sX));
}

int main(){
    vector<double> equis = {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
    vector<double> ye =    {0.50,2.50,2.0,4.0,3.50,6.0,5.50};

    double a1 = pendiente(equis,ye);
    double a0 = Promedio(ye) - a1 * Promedio(equis);

    cout << "la ecuacion y = a1 x + a0 es: "<< a1 << " * x + " << a0 << endl;

}
