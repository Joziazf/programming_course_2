#include <iostream>
#include <cmath>
#include <cstdio>

int main() {
    // Задание 1: начальная точка
    double x0 = 0;

    double x_end = 4.0;
    double step = (x_end - x0) / 10.0;

    for (int i = 1; i <= 10; i++) {
        double x = x0 + i * step;
        double fx = sin(x) / x;
        std::cout << fx;
        if (i < 10) std::cout << " ";
    }
    std::cout << "\n";

    // Задание 2: значение MAX
    long long MAX = 1000;

    long long fib1 = 1, fib2 = 1;
    long long S = 0;
    int N = 0;

    while (S <= MAX) {
        S += fib1;
        N++;

        long long next = fib1 + fib2;
        fib1 = fib2;
        fib2 = next;
    }
    std::cout << N << " " << S;
    std::cout << "\n";
}