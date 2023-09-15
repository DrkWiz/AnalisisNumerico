#include <iostream>
#include <vector>

// Estructura para almacenar los puntos (x, y)
struct Point {
    double x;
    double y;
};

// Función para calcular el polinomio de spline cúbico
std::vector<double> calculateSplinePolynomial(const std::vector<Point>& points) {
    int n = points.size();
    std::vector<double> h(n), alpha(n), l(n + 1), mu(n + 1), z(n + 1), c(n + 1), b(n), d(n);

    // Paso 1: Calcular las diferencias de x
    for (int i = 0; i < n - 1; i++) {
        h[i] = points[i + 1].x - points[i].x;
    }

    // Paso 2: Calcular los coeficientes alpha
    for (int i = 1; i < n - 1; i++) {
        alpha[i] = (3.0 / h[i]) * (points[i + 1].y - points[i].y) - (3.0 / h[i - 1]) * (points[i].y - points[i - 1].y);
    }

    // Paso 3: Resolver el sistema tridiagonal
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n - 1; i++) {
        l[i] = 2.0 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;
    c[n] = 0.0;

    // Paso 4: Calcular los coeficientes c
    for (int j = n - 2; j >= 0; j--) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    // Paso 5: Construir el polinomio resultante
    std::vector<double> coefficients(4 * (n - 1));
    int index = 0;

    for (int i = 0; i < n - 1; i++) {
        coefficients[index++] = points[i].y;
        coefficients[index++] = b[i];
        coefficients[index++] = c[i];
        coefficients[index++] = d[i];
    }

    return coefficients;
}

int main() {
    // Ejemplo de uso
    //std::vector<Point> points = {{0.0, 1.0}, {1.0, 2.7182}, {2.0, 7.3891}, {3.0, 20.0855}};
    std::vector<Point> points = {{0.5, 1.0}, {1.0, 2.1190}, {1.5, 2.9100}, {2.0, 3.9450}, {2.5, 5.7200}, {3.0, 8.6950}};
    //std::vector<Point> points = {{1.0, 4.75}, {2.0, 4.0}, {3.0, 5.25}, {5.0, 19.75}, {6.0, 36.0}};
    //std::vector<Point> points = {{0.0, 50000.0}, {10.0, 35000.0}, {20.0, 31000.0}, {30.0, 20000.0}, {40.0, 19000.0}, {50.0, 12000.0}, {60.0, 11000.0}};


    std::vector<double> coefficients = calculateSplinePolynomial(points);

    // Imprimir el polinomio resultante
    std::cout << "Polinomio resultante:" << std::endl;
    for (int i = 0; i < coefficients.size(); i += 4) {
        std::cout << "S" << i / 4 << "(x) = " << coefficients[i] << " + " << coefficients[i + 1] << "(x - " << points[i / 4].x << ") + "
                  << coefficients[i + 2] << "(x - " << points[i / 4].x << ")^2 + " << coefficients[i + 3] << "(x - " << points[i / 4].x << ")^3"
                  << std::endl;
    }

    return 0;
}
