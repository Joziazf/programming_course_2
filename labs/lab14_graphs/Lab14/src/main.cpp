#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void exercise1(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile);
    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> M(n, std::vector<int>(n, 0));

    int i, j;
    for (int k = 0; k < m; k++) {
        fin >> i >> j;
        M[i][j] = 1;
        M[j][i] = 1;
    }
    fin.close();

    std::ofstream fout(outputFile);
    fout << n << "\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fout << M[i][j];
            if (j < n - 1) fout << ' ';
        }
        fout << '\n';
    }
    fout.close();
}

void exercise2(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile);
    int n;
    fin >> n;

    std::vector<std::vector<int>> M(n, std::vector<int>(n));
    int m = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> M[i][j];
            if (i < j && M[i][j] == 1) {
                m++;
            }
        }
    }
    fin.close();

    std::vector<int> S(n), L(n), D;
    int current_s = 0;

    for (int i = 0; i < n; i++) {
        S[i] = current_s;
        int neighbors_count = 0;

        for (int j = 0; j < n; j++) {
            if (M[i][j] == 1) {
                D.push_back(j);
                neighbors_count++;
            }
        }
        L[i] = neighbors_count;
        current_s += neighbors_count;
    }

    std::ofstream fout(outputFile);
    fout << n << ' ' << m << '\n';

    for (int x : S) fout << x << ' '; fout << '\n';
    for (int x : L) fout << x << ' '; fout << '\n';
    for (int x : D) fout << x << ' '; fout << '\n';

    fout.close();
}

void exercise3(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream fin(inputFile);
    int n, m;
    fin >> n >> m;

    std::vector<int> S(n), L(n), D(2 * m);
    for (int i = 0; i < n; i++) fin >> S[i];
    for (int i = 0; i < n; i++) fin >> L[i];
    for (int i = 0; i < 2 * m; i++) fin >> D[i];
    fin.close();

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int idx = S[i]; idx < S[i] + L[i]; idx++) {
            if (i < D[idx]) {
                edges.push_back({i, D[idx]});
            }
        }
    }

    std::ofstream fout(outputFile);
    fout << n << ' ' << edges.size() << '\n';
    for (const auto& edge : edges) {
        fout << edge.first << ' ' << edge.second << '\n';
    }
    fout.close();
}

int main() {
    exercise1("input_first.txt","output_first.txt");
    exercise2("output_first.txt","output_second.txt");
    exercise3("output_second.txt","output_third.txt");
    return 0;
}