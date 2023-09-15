from sympy import symbols, simplify, expand

def interpolacion_lagrange(coordenadas):
    n = len(coordenadas)
    polinomio = 0
    polinomios_Ln = []

    x = symbols('x')

    for i in range(n):
        x_i, y_i = coordenadas[i]
        termino = 1

        for j in range(n):
            if j != i:
                x_j, _ = coordenadas[j]
                termino *= (x - x_j) / (x_i - x_j)

        polinomio += y_i * termino
        polinomios_Ln.append(termino)  # Almacena el polinomio Lagrange en la lista

    return polinomio, polinomios_Ln

# Ejemplo de uso
coordenadas0 = [(0, 1), (1, 2.7182), (2, 7.3891), (3, 20.0855)]

polinomio, polinomios_Ln = interpolacion_lagrange(coordenadas0)
print("Polinomio no simplificado:")
print(polinomio)
polinomio_simplificado = simplify(polinomio)
print("\nPolinomio simplificado:")
print(polinomio_simplificado)
print("\nPolinomios Ln en el formato Ax^2 + Bx + C:")

for i, Ln in enumerate(polinomios_Ln):
    simplified_Ln = simplify(Ln)
    expanded_Ln = expand(simplified_Ln)
    print(f"L{i}(x) = {expanded_Ln}")
