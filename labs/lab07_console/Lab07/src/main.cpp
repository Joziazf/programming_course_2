#include <iostream>
#include <cmath>

int main() {
    // Задание 1: начальная точка
    double x0 = 0.1;

    // if (x0 <= 0 || x0 > 4) {
    //     return 0;
    // }

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

    // Задание 3: сумма, срок, процентная ставка
    double summa = 150000;
    int srok = 12;
    double stavka = 14;

    double dolg = summa;
    double month_dolg = summa / srok;
    double month_stavka = stavka / 12 / 100;
    double total = 0;

    for (int i = 1; i <= srok; i++) {
        double procent = dolg * month_stavka;
        double platej = month_dolg + procent;
        total += procent;
        printf("%d\t%.2f\t%.2f\t\t%.2f\n", i, dolg, procent, platej);

        dolg -= month_dolg;
    }
    printf("%.2f", total);
}