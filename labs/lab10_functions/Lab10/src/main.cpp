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
        int k = mpack[i]; // высчитываем кол-во этого элемента в исходном массиве

        for (int j = 0; j < k; j++) { // записываем этот элемент k раз
            arr[cur] = i;
            cur++;
        }
    }
}

int main() {
    const int n = 10000;

    int* orig_arr = new int[n]; // выделение памяти под массив

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

    delete[] orig_arr;
    delete[] repack;
}