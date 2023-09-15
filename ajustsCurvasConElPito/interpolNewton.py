
from sympy import symbols, simplify
import matplotlib.pyplot as plt
import numpy as np

def interpolacion_polinomial_newton(coordenadas):
    if len(coordenadas) < 2:
        print("Se requieren al menos dos puntos para la interpolación.")
        return
    
    x = []
    y = []
    for punto in coordenadas:
        x.append(punto[0])
        y.append(punto[1])
    
    n = len(x)
    coeficientes = [[0] * n for _ in range(n)]
    coeficientes[0] = y
    
    for i in range(1, n):
        for j in range(n-i):
            coeficientes[i][j] = (coeficientes[i-1][j+1] - coeficientes[i-1][j]) / (x[j+i] - x[j])
    
    x_var = symbols('x')
    polinomio = coeficientes[0][0]
    producto = 1
    
    for i in range(1, n):
        producto *= (x_var - x[i-1])
        polinomio += coeficientes[i][0] * producto
    
    polinomio_simplificado = simplify(polinomio)
    
    return polinomio_simplificado

def mostrar_tabla_diferencias_divididas(coordenadas):
    if len(coordenadas) < 2:
        print("Se requieren al menos dos puntos para la interpolación.")
        return
    
    x = []
    y = []
    for punto in coordenadas:
        x.append(punto[0])
        y.append(punto[1])
    
    n = len(x)
    diferencias_divididas = [[0] * n for _ in range(n)]
    diferencias_divididas[0] = y
    
    for i in range(1, n):
        for j in range(n-i):
            diferencias_divididas[i][j] = (diferencias_divididas[i-1][j+1] - diferencias_divididas[i-1][j]) / (x[j+i] - x[j])
    
    encabezado = "| {:^8s} | {:^7s} |".format('X', 'Y')
    for i in range(1, n+1):
        encabezado += " {:^8s} |".format('f[X' + str(i) + ']')
    
    separador = "-" * (len(encabezado) + 1)
    
    print(separador)
    print(encabezado)
    print(separador)
    
    for i in range(n):
        fila = "| {:^8.4f} | {:^7.4f} |".format(x[i], y[i])
        for j in range(n-i):
            fila += " {:^8.4f} |".format(diferencias_divididas[j][i])
        print(fila)
        print(separador)

def graficar_polinomio(coordenadas):
    x = []
    y = []
    for punto in coordenadas:
        x.append(punto[0])
        y.append(punto[1])
    
    polinomio = interpolacion_polinomial_newton(coordenadas)
    
    # Crear un array de valores de x para graficar el polinomio
    x_polinomio = np.linspace(min(x), max(x), 100)
    
    # Evaluar el polinomio en los valores de x del array
    y_polinomio = [polinomio.subs('x', val) for val in x_polinomio]
    
    # Graficar el polinomio y los puntos
    plt.plot(x_polinomio, y_polinomio, label='Polinomio')
    plt.scatter(x, y, color='red', label='Puntos')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Gráfico del polinomio y los puntos')
    plt.grid(True)
    plt.legend()
    plt.show()

coordenadas0 = [(0, 1), (1, 2.7182), (2, 7.3891),(3,20.0855)]
coordenadas1 = [(0.5, 1.0), (1.0, 2.1190), (1.5, 2.9100), (2.0, 3.9450), (2.5, 5.7200), (3.0, 8.6950)]
coordenadas2 = [(1.0, 4.75), (2.0, 4.0), (3.0, 5.25), (5.0, 19.75), (6.0, 36.0)]
coordenadas3 = [(0, 50000), (10, 35000), (20, 31000), (30, 20000), (40, 19000), (50, 12000), (60, 11000)]

graficar_polinomio(coordenadas0)

polinomio = interpolacion_polinomial_newton(coordenadas0)
print(polinomio)

mostrar_tabla_diferencias_divididas(coordenadas0)