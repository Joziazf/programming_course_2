#include <iostream>
#include <cmath>

int main() {
    // Задание 1: начальная точка
    double x0 = 0.0;

    double x_end = 4.0;
    double step = (x_end - x0) / 9

    for (int i = 1; i < 10; i++) {
        double x = x0 + i * step;
        double fx = sin(x) / x;
        std::cout << fx;
        if (i < 9) std::cout << " ";
    }



}