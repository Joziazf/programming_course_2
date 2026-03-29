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

void printMatrix(double** matrix, int lines, int unk_p) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j <= unk_p; j++) {
            cout << fixed << setw(8) << setprecision(3) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void makeTriangleForm(double** matrix, int lines, int unk_p, int& rank) {
    rank = 0;
    int row = 0;
    for (int col = 0; col < unk_p && row < lines; col++) {
        int pivot = row;
        for (int i = row + 1; i < lines; i++) {
            if (fabs(matrix[i][col]) > fabs(matrix[pivot][col]))  pivot = i;
        }
        if (fabs(matrix[pivot][col]) < EPSILON) continue;

        swap(matrix[row], matrix[pivot]);

        double val = matrix[row][col];
        for (int j = 0; j <= unk_p; j++) matrix[row][j] /= val;

        for (int i = 0; i < lines; i++) {
            if (i != row) {
                double factor = matrix[i][col];
                for (int j = 0; j <= unk_p; j++) {
                    matrix[i][j] -= matrix[row][j] * factor;
                }
            }
        }
        row++;
        rank++;
    }
}

int main() {
    ifstream fin("tests.txt");
    if (!fin.is_open()) {
        cout << "Error open file" << endl;
        return 1;
    }

    int lines, unk_p;

    fin >> lines >> unk_p;

    if (fin.fail() || lines <= 0 || unk_p <= 0) {
        cout << "Invalid data (M/N)" << endl;
        return 1;
    }
    double** matrix = doMatrix(lines, unk_p);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j <= unk_p; j++) {
            fin >> matrix[i][j];
        }
    }

    fin.close();

    printMatrix(matrix, lines, unk_p);

    int rank = 0;
    makeTriangleForm(matrix, lines, unk_p, rank);

    cout << "------------------------" << endl;
    printMatrix(matrix, lines, unk_p);

    cleanMatrix(matrix, lines);
    return 0;
}