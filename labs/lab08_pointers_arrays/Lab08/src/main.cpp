#include <iostream>
using namespace std;

//ex2 correct
// int main() {
//     int a, b, c, d;
//     int *x = &a, *y = &b, *z = &c;
//
//     либо без доп переменных
//
//     int *x, *y, *z, d;
//     x = new int;
//     y = new int;
//     z = new int;
//
//     cout << "3 number, please" << endl;
//     cin >> *x >> *y >> *z;
//
//     if (*x > *y)
//     {
//         d = *x;
//         *x = *y;
//         *y = d;
//     }
//     if (*x > *z)
//     {
//         d = *x;
//         *x = *z;
//         *z = d;
//     }
//     if (*y > *z)
//     {
//         d = *y;
//         *y = *z;
//         *z = d;
//     }
//
//     cout << "x = " << *x <<" y = " << *y << " z = " << *z << " difference = "<< *z - *x << endl;
//     return 0;
// }

//--------------------------------------------------------------------------------------------------------------------\\

//ex2 func
// void DoubleVal(int &a, int *b) { //функция для удвоения значений
//     a *= 2;
//     *b *= 2;
// }
// int main() {
//     int x = 10, y = 15;
//     cout << "X before: " << x << ", y before: " << y << endl;
//     DoubleVal(x, &y);
//     cout << "X after " << x << ", Y after: " << y << endl;
//     return 0;
// }

//--------------------------------------------------------------------------------------------------------------------\\

//ex3
// #define N 10 //размер массива
//
// int main() {
//
//     //Статический, индексный ->
//     int s1[N];
//     for (int i = 0; i < N; i++) {
//         s1[i] = i * i;
//     }
//
//     //Вывод
//     for (int i = 0; i < N; i++) {
//         cout << s1[i] << " ";
//     }
//     cout << "<- static index" << endl;
//
//     //Статический, через указатель ->
//     int s2[N];
//     for (int i = 0; i < N; i++) {
//         *(s2 + i) = i * i;
//     }
//
//     //Вывод
//     for (int i = 0; i < N; i++) {
//         cout << *(s2 + i) << " ";
//     }
//     cout << "<- Static ykaz" << endl;
//
//     //Динамический, индексный ->
//     int *d1 = new int[N];
//     for (int i = 0; i < N; i++) {
//         d1[i] = i * i;
//     }
//
//     //Вывод
//     for (int i = 0; i < N; i++) {
//         cout << d1[i] << " ";
//     }
//
//     cout << "<- Dynamic index" << endl;
//     delete[] d1;
//
//     //Динамический, через указатель ->
//     int *d2 = new int[N];
//     for (int i = 0; i < N; i++) {
//         *(d2 + i) = i * i;
//     }
//
//     //Вывод
//     for (int i = 0; i < N; i++) {
//         cout << *(d2 + i) << " ";
//     }
//
//     cout << "<- Dynamic ykaz" << endl;
//     delete[] d2;
//
//     cout << endl;
//     //Объединение двух массивов
//
//     const int size1 = 6;
//     const int size2 = 6;
//
//     //Исходные массивы
//     int A[size1] = {1, 3, 5, 7, 9, 11};
//     int B[size2] = {2, 4, 6, 8, 10, 12};
//
//     //Итоговый массив
//     int C[size1 + size2];
//
//     //Индексы массивов
//     int i = 0, j = 0, k = 0;
//
//     while (i < size1 && j < size2) {
//         if (A[i] < B[j]) {
//             C[k] = A[i];
//             i++;
//         } else {
//             C[k] = B[j];
//             j++;
//         }
//         k++;
//     }
//
//     while (i < size1) {
//         C[k] = A[i];
//         i++;
//         k++;
//     }
//
//     while (j < size2) {
//         C[k] = B[j];
//         j++;
//         k++;
//     }
//
//     //Вывод
//     for (int x = 0; x < size1 + size2; x++) {
//         cout << C[x] << " ";
//     }
//
//     cout << endl;
//     return 0;
// }

//--------------------------------------------------------------------------------------------------------------------\\

//ex4
struct Node {
    int id;
    Node* next;
    Node* prev;
};

void ex4() {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < 10; i++) {
        Node* newItem = new Node;
        newItem->id = i;
        newItem->next = NULL;

        if (head == NULL) {
            newItem->prev = NULL;
            head = newItem;
            tail = newItem;
        }
        else {
            tail->next = newItem;
            newItem->prev = tail;
            tail = newItem;
        }
    }

    Node* current = head;
    while (current != NULL) {
        cout << current->id << " ";
        current = current->next;
    }
}

int main() {
    ex4();
    return 0;
}