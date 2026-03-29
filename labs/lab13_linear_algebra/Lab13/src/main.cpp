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

void printMatrix(double** matrix, int lines, int unk_p, ostream& out) {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j <= unk_p; j++) {
            out << fixed << setw(8) << setprecision(3) << matrix[i][j] << " ";
        }
        out << endl;
    }
    out << endl;
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

void solutionUniq(double** matrix, int lines, int unk_p, ostream& out) {
    double** copy = new double*[lines];
    for (int i = 0; i < lines; i++) {
        copy[i] = new double[unk_p + 1];
        for (int j = 0; j <= unk_p; j++) {
            copy[i][j] = matrix[i][j];
        }
    }

    int rank = 0;
    makeTriangleForm(copy, lines, unk_p, rank);

    for (int i = rank; i < lines; i++) {
        if (fabs(copy[i][unk_p]) > EPSILON) {
            out << "Inconsistent system" << endl;
            for (int k = 0; k < lines; k++) delete[] copy[k];
            delete[] copy;
            return;
        }
    }

    if (rank != unk_p) {
        out << "Infinite solutions, rank = " << rank << " < N = " << unk_p << endl;
        for (int k = 0; k < lines; k++) delete[] copy[k];
        delete[] copy;
        return;
    }

    for (int i = 0; i < unk_p; i++) {
        out << "x" << i + 1 << " = " << fixed << setprecision(3) << copy[i][unk_p] << endl;
    }
    for (int k = 0; k < lines; k++) delete[] copy[k];
    delete[] copy;
}

int main() {
    ifstream fin("tests.txt");
    if (!fin.is_open()) {
        cout << "Error open file" << endl;
        return 1;
    }

    int lines, unk_p;

    fin >> lines >> unk_p;

    if (fin.fail()) {
        cout << "Error reading M and N" << endl;
        return 1;
    }

    if (lines <= 0 || unk_p <= 0) {
        cout << "Error incorrect M and N (>0)" << endl;
        return 1;
    }

    double** matrix = doMatrix(lines, unk_p);

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j <= unk_p; j++) {
            fin >> matrix[i][j];
        }
    }

    if (fin.fail()) {
        cout << "Error missing data" << endl;
        cleanMatrix(matrix, lines);
        return 1;
    }

    fin.close();

    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cout << "Error opening output file" << endl;
        cleanMatrix(matrix, lines);
        return 1;
    }

    printMatrix(matrix, lines, unk_p, cout);
    printMatrix(matrix, lines, unk_p, fout);

    int rank = 0;
    makeTriangleForm(matrix, lines, unk_p, rank);

    cout << "------------------------" << endl;
    printMatrix(matrix, lines, unk_p, cout);
    printMatrix(matrix, lines, unk_p, fout);

    solutionUniq(matrix, lines, unk_p, cout);
    solutionUniq(matrix, lines, unk_p, fout);

    fout.close();
    cleanMatrix(matrix, lines);
    return 0;
}