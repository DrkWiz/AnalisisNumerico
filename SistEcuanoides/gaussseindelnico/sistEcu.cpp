//
// Created by francisco on 08/09/23.
//


#include "sistEcu.h"

sistEcu::sistEcu(int fil, int col) {
    filas = fil;
    columnas = col;
    vector<double> filaTemp;


    for(int i = 0; i < filas; i++){
        terminosI.emplace_back(0);
    }

    for(int j = 0; j < columnas; j++)
    {
        filaTemp.emplace_back(0);
    }

    for(int j = 0; j < filas; j++) {
        matrizCoe.emplace_back(filaTemp);
    }

}

void sistEcu::setTerminosI(int size, double *array) {
    if(size != filas)
    {
        throw runtime_error("500");
    }

    for(int i = 0; i < filas; i++){
        terminosI[i] = array[i];
    }
}

void sistEcu::setMatrizCoe(vector<vector<double>> matriz) {
    if(matriz.size() != matrizCoe.size())
    {
        throw runtime_error("500");
    }

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            matrizCoe[i][j] = matriz[i][j];
        }
    }


}

double sistEcu::getTerminoI(int pos) {
    return terminosI[pos];
}

double sistEcu::getRes(int posFil, vector<double> soluciones) {

    double resultado = 0.;

    for(int i = 0; i < columnas; i++)
    {
        resultado += matrizCoe[posFil][i]  * soluciones[i];
    }

    return resultado;
}

void sistEcu::imprimir(){

    for(int i=0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            cout<<matrizCoe[i][j]<<"* X"<<j;
            if(j != columnas - 1)
            {
                cout<<" + ";
            }
        }
        cout<<" = "<<terminosI[i]<<endl;
    }



}

void sistEcu::sumarFila(int filaBase, int filaOpera, double multiplo) {

    terminosI[filaBase] += terminosI[filaOpera] * multiplo;
    for(int i = 0; i < columnas; i++)
    {
        matrizCoe[filaBase][i] += matrizCoe[filaOpera][i] * multiplo;
    }
}

void sistEcu::anularFila(int filaBase, int filaOpera, int colNula) {
    if(colNula < 0 || colNula >= columnas)
    {
        throw runtime_error("600");
    }

    double multiplo = -1. * matrizCoe[filaBase][colNula] / matrizCoe[filaOpera][colNula];


    terminosI[filaBase] += terminosI[filaOpera] * multiplo;
    matrizCoe[filaBase][colNula] = 0;

    for(int i = colNula + 1; i < columnas; i++)
    {
        matrizCoe[filaBase][i] += matrizCoe[filaOpera][i] * multiplo;
    }
}

double sistEcu::getColumnas() {
    return columnas;
}

double sistEcu::getFilas() {
    return filas;
}

double sistEcu::getCoeficiente(int fil, int col) {
    return matrizCoe[fil][col];
}

void sistEcu::acomodarDiagonal() {

    if (filas != columnas)
    {
        throw runtime_error("600");
    }

    vector<double> diagonal, aux;

    for(int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; ++j) {
            if(i == j)
            {
                diagonal.emplace_back(matrizCoe[i][j]);
            }
        }
    }

    // matriz[fila][columna]

    for (int i = 0; i < columnas; ++i) {
        for (int j = filas-1; j > -1; --j) {
            if(matrizCoe[j][i] >= diagonal[i])
            {
                cambiarFila(i,j);
                diagonal[i] = matrizCoe[j][i];
                break;
            }
        }
    }

}

void sistEcu::cambiarFila(int filaBase, int filaOpera) {

    vector<double> aux;
    double TI;

    for(int i = 0; i < filas; i++)
    {
        if(i == filaBase)
        {
            aux = matrizCoe[i];
            TI = terminosI[i];
        }
    }

    matrizCoe[filaBase] = matrizCoe[filaOpera];
    terminosI[filaBase] = terminosI[filaOpera];
    matrizCoe[filaOpera] = aux;
    terminosI[filaOpera] = TI;

}

