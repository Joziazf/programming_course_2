#include <iostream>
using namespace std;


// arr - исходный массив, n - длина исходника, mpack - запакованный массив.
void pack(int* arr, int n, int* mpack) {
    for (int i = 0; i < 17; i++) {
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