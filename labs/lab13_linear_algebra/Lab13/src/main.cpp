#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <regex>
#include <string>

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

bool Parser(const string& ex, double& a, double& b, double& c) {
    a = 0; b = 0; c = 0;

    regex termRe("([+-]?\\d*\\.?\\d*)([xyz]?)");

    size_t exPos = ex.find('=');
    if (exPos == string::npos) return false;

    string left = ex.substr(0, exPos);
    string right = ex.substr(exPos + 1);

    c = stod(right);

    auto it = sregex_iterator(left.begin(), left.end(), termRe);
    for (; it != sregex_iterator(); ++it) {
        string numPart = (*it)[1].str();
        string varPart = (*it)[2].str();

        if (numPart.empty() && varPart.empty()) continue;

        if ((numPart == "+" || numPart == "-") && varPart.empty()) continue;

        double coeff;
        if (numPart == "+" || numPart.empty()) coeff = 1.0;
        else if (numPart == "-") coeff = -1.0;
        else coeff = stod(numPart);

        if (varPart == "x") a += coeff;
        else if (varPart == "y") b += coeff;
        else if (!varPart.empty()) return false;
        else c -= coeff;
    }
    return true;
}

/*
Элементарные преобразования:
- Перестановка строк;
- Умножение строки на число;
- Прибавление кратной строки.
*/
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

void solutionFull(double** matrix, int lines, int unk_p, ostream& out) {
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
            out << "Inconsistent system -> no general solution" << endl;
            for (int k = 0; k < lines; k++) delete[] copy[k];
            delete[] copy;
            return;
        }
    }

    if (rank == unk_p) {
        out << "No general solution, uniq" << endl;
        for (int k = 0; k < lines; k++) delete[] copy[k];
        delete[] copy;
        return;
    }

    bool* isPivot = new bool[unk_p]();
    int* pivotCol = new int[rank];
    int r = 0;
    for (int col = 0; col < unk_p && r < rank; col++) {
        if (fabs(copy[r][col]) > EPSILON) {
            isPivot[col] = true;
            pivotCol[r] = col;
            r++;
        }
    }

    bool first = true;
    for (int j = 0; j < unk_p; j++) {
        if (!isPivot[j]) {
            if (first) { out << "Free variants: "; first = false; } else out << ", ";
            out << "x" << j + 1;
        }
    }
    out << endl;

    double* solution = new double[unk_p]();
    for (int i = 0; i < rank; i++) {
        solution[pivotCol[i]] = copy[i][unk_p];
    }

    for (int j = 0; j < unk_p; j++) {
        if (j > 0) out << "; ";
        out << "x" << j + 1 << "=" << fixed << setprecision(0) << solution[j];
    }
    out << endl;

    delete[] isPivot;
    delete[] pivotCol;
    delete[] solution;
    for (int k = 0; k < lines; k++) delete[] copy[k];
    delete[] copy;
}

//Допы
void taskA(ostream& out) {
    ifstream fin("test_graph_A.txt");
    string line;
    getline(fin, line);
    fin.close();

    size_t zap = line.find(',');
    string ex1 = line.substr(0, zap);
    string ex2 = line.substr(zap + 1);

    double a1, b1, c1, a2, b2, c2;
    Parser(ex1, a1, b1, c1);
    Parser(ex2, a2, b2, c2);

    double** matrix = doMatrix(2, 2);
    matrix[0][0] = a1; matrix[0][1] = b1; matrix[0][2] = c1;
    matrix[1][0] = a2; matrix[1][1] = b2; matrix[1][2] = c2;

    int rank = 0;
    makeTriangleForm(matrix, 2, 2, rank);

    bool isParallel = false;
    for (int i = rank; i < 2; i++) {
        if (fabs(matrix[i][2]) > EPSILON) isParallel = true;
    }

    if (isParallel) {
        out << "Lines are parallel" << endl;
        cleanMatrix(matrix, 2);
        return;
    }

    if (rank < 2) {
        out << "Same lines" << endl;
        cleanMatrix(matrix, 2);
        return;
    }

    double x = matrix[0][2];
    double y = matrix[1][2];
    out << "Solution: x -> " << x << "; y -> " << y << endl;

    ofstream script("lines.py");
    script << "import matplotlib.pyplot as plt\n"
           << "import numpy as np\n"
           << "\n\n"
           << "x_c, y_c = " << x << ", " << y << "\n"
           << "x = np.linspace(x_c - 10, x_c + 10, 400)\n"
           << "\n"
           << "plt.xlim(x_c - 10, x_c + 10)\n"
           << "plt.ylim(y_c - 10, y_c + 10)\n"
           << "\n"
           << "if abs(" << b1 << ") > 1e-9:\n"
           << "    plt.plot(x, (" << c1 << " - " << a1 << " * x) / " << b1
           << ", 'b-', label='" << a1 << "x + " << b1 << "y = " << c1 << "')\n"
           << "else:\n"
           << "    plt.axvline(x=" << c1 / a1 << ", color='b', label='x = " << c1 / a1 << "')\n"
           << "\n"
           << "if abs(" << b2 << ") > 1e-9:\n"
           << "    plt.plot(x, (" << c2 << " - " << a2 << " * x) / " << b2
           << ", 'r-', label='" << a2 << "x + " << b2 << "y = " << c2 << "')\n"
           << "else:\n"
           << "    plt.axvline(x=" << c2 / a2 << ", color='r', label='x = " << c2 / a2 << "')\n"
           << "\n"
           << "plt.plot(x_c, y_c, 'go', markersize=8, label=f'({x_c:.3f}, {y_c:.3f})')\n"
           << "plt.annotate(\n"
           << "    f'({x_c:.3f}, {y_c:.3f})',\n"
           << "    (x_c, y_c),\n"
           << "    textcoords='offset points',\n"
           << "    xytext=(8, 8)\n"
           << ")\n"
           << "\n"
           << "plt.axhline(0, color='black', linewidth=0.5)\n"
           << "plt.axvline(0, color='black', linewidth=0.5)\n"
           << "plt.grid(True, alpha=0.3)\n"
           << "plt.legend()\n"
           << "plt.title('First task')\n"
           << "plt.tight_layout()\n"
           << "plt.show()\n";
    script.close();
    script.close();

    system("venv/bin/python lines.py");

    cleanMatrix(matrix, 2);
}

void taskB(ostream& out) {

}

int main() {
    int choice;
    do {
        cout << "Main menu" << endl;
        cout << "1. Run main task" << endl;
        cout << "2. Run additional A task" << endl;
        cout << "3. Run additional B task" << endl;
        cout << "4. Run additional C task" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            ifstream fin("tests.txt");
            if (!fin.is_open()) {
                cout << "Error open file" << endl;
                continue;
            }

            int lines, unk_p;

            fin >> lines >> unk_p;

            if (fin.fail()) {
                cout << "Error reading M and N" << endl;
                continue;
            }

            if (lines <= 0 || unk_p <= 0) {
                cout << "Error incorrect M and N (>0)" << endl;
                continue;
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
                continue;
            }

            fin.close();

            ofstream fout("output.txt");
            if (!fout.is_open()) {
                cout << "Error opening output file" << endl;
                cleanMatrix(matrix, lines);
                continue;
            }

            printMatrix(matrix, lines, unk_p, cout);
            printMatrix(matrix, lines, unk_p, fout);

            int rank = 0;
            makeTriangleForm(matrix, lines, unk_p, rank);

            cout << "------------------------------------------------" << endl;
            fout << "------------------------------------------------" << endl;
            cout << endl;
            fout << endl;

            printMatrix(matrix, lines, unk_p, cout);
            printMatrix(matrix, lines, unk_p, fout);

            cout << "------------------------------------------------ > uniq" << endl;
            fout << "------------------------------------------------ > uniq" << endl;
            solutionUniq(matrix, lines, unk_p, cout);
            solutionUniq(matrix, lines, unk_p, fout);

            cout << endl;
            fout << endl;

            cout << "------------------------------------------------ > full" << endl;
            fout << "------------------------------------------------ > full" << endl;
            solutionFull(matrix, lines, unk_p, cout);
            solutionFull(matrix, lines, unk_p, fout);

            fout.close();
            cleanMatrix(matrix, lines);

        } else if (choice == 2) {
            taskA(cout);

        } else if (choice != 0) {
            cout << "Invalid choice" << endl;

        }
    } while (choice != 0);

    return 0;
}