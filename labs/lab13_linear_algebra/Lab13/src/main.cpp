// ввод x - кол-во уравнений, y - кол-во неизвестных (x y) --> 1 строка, считывать файл!!!!!!!!!
// красивый ввод матрицы
// x <= y, другие проверки, лобовой алгоритм решения, через ведущие(по области/по столбцу)
// основной войд по приведению к ступенчатому, доп войды для решений(общее и единственное)
// доп задания:
// - реализация графика двух пересекающихся прямых с нахождением точки пересечения(единственное решение) на плюсах GUI
// - трёхмерное пространство, нахождение точки пересечения плоскостей
// - реализация графика трех прямых с нахождением площади образуемой фигуры

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

const double EPSILON = 1e-9;

double** doMatrix(int lines, int unk_p) {
    double** matrix = new double*[lines];
    for (int i = 0; i < lines; i++) {
        matrix[i] = new double[unk_p + 1];
        for (int j = 0; j <= unk_p; j++) matrix[i][j] = 0;
    }
    return matrix;
}

void cleanMatrix(double** matrix, int lines) {
    for (int i = 0; i < lines; i++) delete[] matrix[i];
    delete[] matrix;
}