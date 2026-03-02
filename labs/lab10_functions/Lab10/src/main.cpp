#include <iostream>
using namespace std;


// arr - исходный массив, n - длина исходника, mpack - запакованный массив.
void pack(int* arr, int n, int* mpack) {
    for (int i = 0; i <= 17; i++) {
        mpack[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int val = arr[i];
        mpack[val]++;
    }
}

void raspack(int* mpack, int* arr) {
    int cur = 0;

    for (int i = 0; i <= 17; i++) {
        int k = mpack[i];

        for (int j = 0; j < k; j++) {
            arr[cur] = i;
            cur++;
        }
    }
}

bool check(int* arr_main, int* arr_after_function, int n) {
    for (int i = 0; i < n; i++) {
        if (arr_main[i] != arr_after_function[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int n = 10000;

    int* orig_arr = new int[n];

    for (int i = 0; i < n; i++) {
        orig_arr[i] = (i * 18) / n;
    }

    int pack_arr[18];

    pack(orig_arr, n, pack_arr);

    for (int i = 0; i <= 17; i++) {
        cout << i << ": " << pack_arr[i] << endl;
    }

    int* repack = new int[n];

    raspack(pack_arr, repack);

    for (int i = 0; i < n; i++) {
        cout << repack[i] << endl;
    }

    if (check(orig_arr, repack, n)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    delete[] orig_arr;
    delete[] repack;
    return 0;
}