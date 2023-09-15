#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::string lagrange_interpolation_expression(const std::vector<double>& x_values, const std::vector<double>& y_values) {
    int n = x_values.size();
    std::stringstream expression;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            expression << " + ";
        }

        expression << y_values[i];

        for (int j = 0; j < n; j++) {
            if (i != j) {
                expression << " * (x - " << x_values[j] << ") / (" << x_values[i] << " - " << x_values[j] << ")";
            }
        }
    }

    return expression.str();
}

int main() {
    //std::vector<double> x_values = {0.0, 1.0, 2.0, 3.0};
    //std::vector<double> y_values = {1.0, 2.7182, 7.3891, 20.0855};

    //std::vector<double> x_values = { 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    //std::vector<double> y_values = {1.0, 2.1190, 2.9100, 3.9450, 5.7200, 8.6950};

    std::vector<double> x_values = {1.0, 2.0, 3.0, 5.0, 6.0};
    std::vector<double> y_values = {4.75, 4.0, 5.25, 19.75, 36.0};

    //std::vector<double> x_values = {0    ,10    , 20   , 30   , 40   , 50   , 60};
    //std::vector<double> y_values = {50000, 35000, 31000, 20000, 19000, 12000, 11000};

    std::string expression = lagrange_interpolation_expression(x_values, y_values);

    std::cout << "La expresión del polinomio de interpolación de Lagrange es: " << expression << std::endl;

    return 0;
}
