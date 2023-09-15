//
// Created by francisco on 08/09/23.
//

#ifndef GAUSSSEINDELNICO_SISTECU_H
#define GAUSSSEINDELNICO_SISTECU_H

#include "vector"
#include "iostream"

using namespace std;

class sistEcu {
private:
    int filas;
    int columnas;

    vector<double> terminosI;
    vector<vector<double>> matrizCoe;

public:
    sistEcu(int fil = 0, int col = 0);

    void setTerminosI(int size, double array[]);
    void setMatrizCoe(vector<vector <double>> matriz);

    double getTerminoI(int pos);
    double getCoeficiente(int fil, int col);
    double getRes(int posFil, vector<double> soluciones);
    double getFilas();
    double getColumnas();

    void imprimir();

    void sumarFila(int filaBase, int filaOpera, double multiplo);
    void anularFila(int filaBase, int filaOpera, int colNula);
    void cambiarFila(int filaBase, int filaOpera);



    void acomodarDiagonal();

};

#endif //GAUSSSEINDELNICO_SISTECU_H
