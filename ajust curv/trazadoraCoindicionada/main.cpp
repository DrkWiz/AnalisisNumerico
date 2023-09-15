#include <iostream>
#include <vector>

// Estructura para almacenar los puntos (x, y)
struct Point {
    double x;
    double y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

// Función para calcular el polinomio de spline cúbico condicionado
std::vector<double> calculate_conditioned_spline(const std::vector<Point>& points, double derivative_at_start, double derivative_at_end) {
    int n = points.size();
    std::vector<double> h(n - 1, 0.0);
    std::vector<double> alpha(n - 1, 0.0);
    std::vector<double> l(n + 1, 0.0);
    std::vector<double> mu(n + 1, 0.0);
    std::vector<double> z(n + 1, 0.0);
    std::vector<double> c(n + 1, 0.0);
    std::vector<double> b(n, 0.0);
    std::vector<double> d(n, 0.0);

    // Paso 1: Calcular las diferencias de x
    for (int i = 0; i < n - 1; ++i) {
        h[i] = points[i + 1].x - points[i].x;
    }

    // Paso 2: Calcular los coeficientes alpha
    for (int i = 1; i < n - 1; ++i) {
        alpha[i] = (3.0 / h[i]) * (points[i + 1].y - points[i].y) - (3.0 / h[i - 1]) * (points[i].y - points[i - 1].y);
    }

    // Paso 3: Resolver el sistema tridiagonal de ecuaciones
    l[0] = 2.0 * h[0];
    mu[0] = 0.5;
    z[0] = (alpha[0] - 3.0 / h[0] * derivative_at_start) / l[0];

    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2.0 * (points[i + 1].x - points[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = h[n - 2];
    z[n] = (3.0 / h[n - 2]) * (derivative_at_end - alpha[n - 2]) / l[n - 1];

    // Paso 4: Calcular los coeficientes c
    c[n - 1] = z[n - 1];

    for (int j = n - 2; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (points[j + 1].y - points[j].y) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    // Construir el polinomio resultante
    std::vector<double> coefficients;
    for (int i = 0; i < n - 1; ++i) {
        coefficients.push_back(points[i].y);
        coefficients.push_back(b[i]);
        coefficients.push_back(c[i]);
        coefficients.push_back(d[i]);
    }

    return coefficients;
}

int main() {
    std::vector<Point> points1 = {Point(0.5, 1.0), Point(1.0, 2.1190), Point(1.5, 2.9100), Point(2.0, 3.9450), Point(2.5, 5.7200), Point(3.0, 8.6950)};

    double derivative_at_start = 0.0;  // Derivada primera en el punto inicial
    double derivative_at_end = 0.0;    // Derivada primera en el punto final

    std::vector<double> coefficients = calculate_conditioned_spline(points1, derivative_at_start, derivative_at_end);

    // Imprimir el polinomio resultante
    std::cout << "Polinomio resultante:" << std::endl;

    for (int i = 0; i < coefficients.size(); i += 4) {
        std::cout << "S" << i / 4 << "(x) = " << coefficients[i] << " + " << coefficients[i + 1] << "(x - " << points1[i / 4].x << ") + " << coefficients[i + 2] << "(x - " << points1[i / 4].x << ")^2 + " << coefficients[i + 3] << "(x - " << points1[i / 4].x << ")^3" << std::endl;
    }

    return 0;
}
