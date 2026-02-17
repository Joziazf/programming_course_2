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

//ex2 func
void DoubleVal(int &a, int *b) { //функция для удвоения значений
    a *= 2;
    *b *= 2;
}
int main() {
    int x = 10, y = 15;
    cout << "X before: " << x << ", y before: " << y << endl;
    DoubleVal(x, &y);
    cout << "X after " << x << ", Y after: " << y << endl;
    return 0;
}