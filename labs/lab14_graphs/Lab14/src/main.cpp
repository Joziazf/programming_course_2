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




int main() {
    exercise1("input_first.txt","output_first.txt");
    return 0;
}