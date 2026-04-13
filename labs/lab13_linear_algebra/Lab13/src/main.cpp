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
            double val = matrix[i][j];

            if (fabs(val) < EPSILON) {
                val = 0;
            }

            out << fixed << setw(8) << setprecision(3) << val << " ";
        }
        out << endl;
    }
    out << endl;
}

bool Parser(const string& ex, double coeffs[], int numVars) {
    for (int i = 0; i <= numVars; i++) coeffs[i] = 0;

    regex termRe("([+-]?\\d*\\.?\\d*)([xyz]?)");

    size_t exPos = ex.find('=');
    if (exPos == string::npos) return false;

    string left  = ex.substr(0, exPos);
    string right = ex.substr(exPos + 1);

    string leftClean = "";
    for (char c : left) if (c != ' ') leftClean += c;

    coeffs[numVars] = stod(right);

    char varNames[] = {'x', 'y', 'z'};

    auto it = sregex_iterator(leftClean.begin(), leftClean.end(), termRe);
    for (; it != sregex_iterator(); ++it) {
        string numPart = (*it)[1].str();
        string varPart = (*it)[2].str();

        if (numPart.empty() && varPart.empty()) continue;
        if ((numPart == "+" || numPart == "-") && varPart.empty()) continue;

        double coeff;
        if (numPart == "+" || numPart.empty()) coeff =  1.0;
        else if (numPart == "-") coeff = -1.0;
        else coeff = stod(numPart);

        bool found = false;
        for (int v = 0; v < numVars; v++) {
            if (varPart == string(1, varNames[v])) {
                coeffs[v] += coeff;
                found = true;
                break;
            }
        }
        if (!found && !varPart.empty()) return false;
        if (!found && varPart.empty()) coeffs[numVars] -= coeff;
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

        for (int i = row + 1; i < lines; i++) {
            double factor = matrix[i][col];
            for (int j = 0; j <= unk_p; j++) {
                matrix[i][j] -= matrix[row][j] * factor;
            }
        }
        row++;
        rank++;
    }
}

void makeDiag(double** matrix, int lines, int unk_p) {
    for (int row = lines - 1; row >= 0; row--) {
        int pivot_col = -1;
        for (int col = 0; col < unk_p; col++) {
            if (fabs(matrix[row][col]) > EPSILON) {
                pivot_col = col;
                break;
            }
        }

        if (pivot_col != -1) {
            for (int i = 0; i < row; i++) {
                double factor = matrix[i][pivot_col];
                for (int j = 0; j <= unk_p; j++) {
                    matrix[i][j] -= matrix[row][j] * factor;
                }
            }
        }
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

    makeDiag(copy, lines, unk_p);

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
    makeDiag(copy, lines, unk_p);

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

// Допы
void taskA(ostream& out) {
    ifstream fin("test_graph_A.txt");
    if (!fin.is_open()) {
        cout << "Error open" << endl;
        return;
    }

    string line;
    getline(fin, line);
    fin.close();

    size_t zap = line.find(',');
    string ex1 = line.substr(0, zap);
    string ex2 = line.substr(zap + 1);

    double cof1[3], cof2[3];
    if (!Parser(ex1, cof1, 2) || !Parser(ex2, cof2, 2)) {
        cout << "Error parser" << endl;
        return;
    }

    double a1=cof1[0], b1=cof1[1], c1=cof1[2];
    double a2=cof2[0], b2=cof2[1], c2=cof2[2];

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

    makeDiag(matrix, 2, 2);

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

    system("venv/bin/python lines.py");

    cleanMatrix(matrix, 2);
}

void taskB(ostream& out) {
    ifstream fin("test_b.txt");
    if (!fin.is_open()) {
        cout << "Error open" << endl;
        return;
    }

    string line;
    getline(fin, line);
    fin.close();

    string exs[3];
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    exs[0] = line.substr(0, pos1);
    exs[1] = line.substr(pos1 + 1, pos2 - pos1 - 1);
    exs[2] = line.substr(pos2 + 1);

    double** matrix = doMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        double coeffs[4];
        if (!Parser(exs[i], coeffs, 3)) {
            cout << "Error parser" << i+1 << endl;
            cleanMatrix(matrix, 3);
            return;
        }
        for (int j = 0; j <= 3; j++) matrix[i][j] = coeffs[j];
    }

    int rank = 0;
    makeTriangleForm(matrix, 3, 3, rank);

    bool isParallel = false;
    for (int i = rank; i < 3; i++)
        if (fabs(matrix[i][3]) > EPSILON) isParallel = true;

    if (isParallel) {
        out << "Inconsistent system" << endl;

    } else {
        makeDiag(matrix, 3, 3);

        if (rank < 3) {
            bool* isPivot  = new bool[3]();
            int*  pivotCol = new int[rank];
            int r = 0;
            for (int col = 0; col < 3 && r < rank; col++) {
                if (fabs(matrix[r][col]) > EPSILON) {
                    isPivot[col] = true;
                    pivotCol[r] = col;
                    r++;
                }
            }

            char varNames[] = {'x', 'y', 'z'};
            bool first = true;
            for (int j = 0; j < 3; j++) {
                if (!isPivot[j]) {
                    if (!first) out << ", ";
                    out << varNames[j] << " is free";
                    first = false;
                }
            }
            out << endl;

            double sol[3] = {0, 0, 0};
            for (int i = 0; i < rank; i++)
                sol[pivotCol[i]] = matrix[i][3];

            out << "x = " << fixed << setprecision(3) << sol[0] << ", "
                << "y = " << fixed << setprecision(3) << sol[1] << ", "
                << "z = " << fixed << setprecision(3) << sol[2] << endl;

            delete[] isPivot;
            delete[] pivotCol;
        } else {
            out << "Intersection point:" << endl;
            out << "x = " << fixed << setprecision(3) << matrix[0][3] << endl;
            out << "y = " << fixed << setprecision(3) << matrix[1][3] << endl;
            out << "z = " << fixed << setprecision(3) << matrix[2][3] << endl;
        }
    }
    cleanMatrix(matrix, 3);
}

void taskC(ostream& out) {
    ifstream fin("test_graph_C.txt");
    if (!fin.is_open()) {
        cout << "Error open" << endl;
        return;
    }

    string line;
    getline(fin, line);
    fin.close();

    string exs[3];
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    exs[0] = line.substr(0, pos1);
    exs[1] = line.substr(pos1 + 1, pos2 - pos1 - 1);
    exs[2] = line.substr(pos2 + 1);

    double coeffs[3][3];
    for (int i = 0; i < 3; i++) {
        if (!Parser(exs[i], coeffs[i], 2)) {
            cout << "Error parser" << i+1 << endl;
            return;
        }
    }

    double prs[3][3];
    int pairs[3][2] = {{0, 1}, {0, 2}, {1, 2}};

    for (int p = 0; p < 3; p++) {
        int i = pairs[p][0];
        int j = pairs[p][1];

        double** m = doMatrix(2, 2);
        m[0][0] = coeffs[i][0]; m[0][1] = coeffs[i][1]; m[0][2] = coeffs[i][2];
        m[1][0] = coeffs[j][0]; m[1][1] = coeffs[j][1]; m[1][2] = coeffs[j][2];

        int rank = 0;
        makeTriangleForm(m, 2, 2, rank);

        bool Solution_flag = false;
        for (int k = rank; k < 2; k++) {
            if (fabs(m[k][2]) > EPSILON) Solution_flag = true;
        }

        if (Solution_flag || rank < 2) {
            out << "Degenerate case" << endl;
            cleanMatrix(m, 2);
            return;
        }

        makeDiag(m, 2, 2);

        prs[p][0] = m[0][2];
        prs[p][1] = m[1][2];
        cleanMatrix(m, 2);
    }
    double area = 0.5 * fabs(
        prs[0][0] * (prs[1][1] - prs[2][1]) +
        prs[1][0] * (prs[2][1] - prs[0][1]) +
        prs[2][0] * (prs[0][1] - prs[1][1])
    );

    out << "Area = " << fixed << setprecision(3) << area << endl;

    ofstream script("triangle.py");
    script << "import matplotlib.pyplot as plt\n"
           << "import numpy as np\n"
           << "\n\n"
           << "pts = [\n"
           << "    (" << prs[0][0] << ", " << prs[0][1] << "),\n"
           << "    (" << prs[1][0] << ", " << prs[1][1] << "),\n"
           << "    (" << prs[2][0] << ", " << prs[2][1] << ")\n"
           << "]\n"
           << "\n"
           << "xs = [p[0] for p in pts] + [pts[0][0]]\n"
           << "ys = [p[1] for p in pts] + [pts[0][1]]\n"
           << "\n"
           << "plt.plot(xs, ys, 'b-')\n"
           << "plt.fill(xs, ys, alpha=0.2, color='blue')\n"
           << "\n"
           << "labels = ['P1', 'P2', 'P3']\n"
           << "for i, (px, py) in enumerate(pts):\n"
           << "    plt.plot(px, py, 'bo', markersize=6)\n"
           << "    plt.annotate(\n"
           << "        f'{labels[i]} ({px:.3f}, {py:.3f})',\n"
           << "        (px, py),\n"
           << "        textcoords='offset points',\n"
           << "        xytext=(8, 8)\n"
           << "    )\n"
           << "\n"
           << "x_min, x_max = min(xs) - 5, max(xs) + 5\n"
           << "x = np.linspace(x_min, x_max, 400)\n"
           << "plt.xlim(x_min, x_max)\n"
           << "\n";

    for (int i = 0; i < 3; i++) {
        double a = coeffs[i][0], b = coeffs[i][1], c = coeffs[i][2];

        script << "if abs(" << b << ") > 1e-9:\n"
               << "    plt.plot(\n"
               << "        x, (" << c << " - " << a << " * x) / " << b << ",\n"
               << "        '--', alpha=0.5, label='" << a << "x + " << b << "y = " << c << "'\n"
               << "    )\n"
               << "else:\n"
               << "    plt.axvline(x=" << c / a << ", linestyle='--', alpha=0.5)\n"
               << "\n";
    }

    script << "plt.axhline(0, color='black', linewidth=0.5)\n"
           << "plt.axvline(0, color='black', linewidth=0.5)\n"
           << "plt.grid(True, alpha=0.3)\n"
           << "plt.legend()\n"
           << "plt.title('Triangle  |  Area = " << fixed << setprecision(3) << area << "')\n"
           << "plt.tight_layout()\n"
           << "plt.show()\n";
    script.close();

    system("venv/bin/python triangle.py");
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

        } else if (choice == 3) {
            taskB(cout);

        } else if (choice == 4) {
            taskC(cout);

        } else if (choice != 0) {
            cout << "Invalid choice" << endl;
        }

    } while (choice != 0);

    return 0;
}