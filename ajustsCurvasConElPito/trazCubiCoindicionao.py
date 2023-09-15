import numpy as np

# Estructura para almacenar los puntos (x, y)
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Función para calcular el polinomio de spline cúbico condicionado
def calculate_conditioned_spline(points, derivative_at_start, derivative_at_end):
    n = len(points) # Calcula la longitud de la lista de puntos y la guarda en la variable n.
    h = np.zeros(n - 1) # Crea un arreglo h de tamaño n-1 lleno de ceros.
    alpha = np.zeros(n - 1) # Crea un arreglo alpha de tamaño n-1 lleno de ceros.
    l = np.zeros(n + 1) # Crea un arreglo l de tamaño n+1 lleno de ceros.
    mu = np.zeros(n + 1) # Crea un arreglo mu de tamaño n+1 lleno de ceros.
    z = np.zeros(n + 1) # Crea un arreglo z de tamaño n+1 lleno de ceros.
    c = np.zeros(n + 1) # Crea un arreglo c de tamaño n+1 lleno de ceros.
    b = np.zeros(n) # Crea un arreglo b de tamaño n lleno de ceros.
    d = np.zeros(n) # Crea un arreglo d de tamaño n lleno de ceros.

    # Paso 1: Calcular las diferencias de x
    for i in range(n - 1): # Recorre la lista de puntos desde el punto 0 hasta el punto n-1
        h[i] = points[i + 1].x - points[i].x # Calcula la diferencia de x entre el punto i+1 y el punto i

    # Paso 2: Calcular los coeficientes alpha
    for i in range(1, n - 1): # Recorre la lista de puntos desde el punto 1 hasta el punto n-2
        alpha[i] = (3.0 / h[i]) * (points[i + 1].y - points[i].y) - (3.0 / h[i - 1]) * (points[i].y - points[i - 1].y) # Calcula el coeficiente alpha

    # Paso 3: Resuelve un sistema tridiagonal de ecuaciones para calcular los valores intermedios de l, mu, y z.
    l[0] = 2.0 * h[0]
    mu[0] = 0.5
    z[0] = (alpha[0] - 3.0 / h[0] * derivative_at_start) / l[0]

    for i in range(1, n - 1): # Recorre la lista de puntos desde el punto 1 hasta el punto n-2
        l[i] = 2.0 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1] # Calcula el coeficiente l
        mu[i] = h[i] / l[i] # Calcula el coeficiente mu
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i] # Calcula el coeficiente z

    l[n] = h[n - 2]
    z[n] = (3.0 / h[n - 2]) * (derivative_at_end - alpha[n - 2]) / l[n - 1]

    # Paso 4: Calcular los coeficientes c
    c[n - 1] = z[n - 1]

    for j in range(n - 2, -1, -1): # Recorre la lista de puntos desde el punto n-2 hasta el punto 0
        c[j] = z[j] - mu[j] * c[j + 1] # Calcula el coeficiente c
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0 # Calcula el coeficiente b
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]) # Calcula el coeficiente d

    # Construye el polinomio resultante combinando los coeficientes y lo guarda en la lista coefficients.
    coefficients = []
    for i in range(n - 1):
        coefficients.extend([points[i].y, b[i], c[i], d[i]])

    return coefficients # Retorna la lista de coeficientes coefficients que define el polinomio de spline.

# Ejemplo de uso
points0 = [Point(0, 1),Point(1, 2.7182),Point(2, 7.3891), Point(3, 20.0855)]
points1 = [Point(0.5, 1.0), Point(1.0, 2.1190), Point(1.5, 2.9100), Point(2.0, 3.9450), Point(2.5, 5.7200), Point(3.0, 8.6950)]
points2 = [Point(1.0, 4.75), Point(2.0, 4.0), Point(3.0, 5.25), Point(5.0, 19.75), Point(6.0, 36.0)]
points3 = [Point(0, 50000), Point(10, 35000), Point(20, 31000), Point(30, 20000), Point(40, 19000), Point(50, 12000), Point(60, 11000)]

points = points1

derivative_at_start = 0.0  # Derivada primera en el punto inicial
derivative_at_end = 0.0  # Derivada primera en el punto final

coefficients = calculate_conditioned_spline(points, derivative_at_start, derivative_at_end)

# Imprimir el polinomio resultante
print("Polinomio resultante:")

for i in range(0, len(coefficients), 4):
    print(f"S{i//4}(x) = {coefficients[i]} + {coefficients[i+1]}(x - {points[i//4].x}) + {coefficients[i+2]}(x - {points[i//4].x})^2 + {coefficients[i+3]}(x - {points[i//4].x})^3")
