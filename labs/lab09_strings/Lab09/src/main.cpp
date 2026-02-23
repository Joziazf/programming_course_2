#include <iostream>
#include <cstring> // для Char-строк
#include <string>  // для C++-строк
using namespace std;

void first() {
    // char C
    char c_str_1[20] = "Hello";
    char c_str_2[] = " World";
    char c_str_copy[20];

    cout << "1. len: " << strlen(c_str_1) << endl; // 1
    cout << "2. append: " << strcat(c_str_1, c_str_2) << endl; // 2
    cout << "3. Copy: " << strcpy(c_str_copy, c_str_1) << endl; // 3

    // string cpp
    string cpp_str = "School";

    cout << "1. len: " << cpp_str.length() << endl; // 1
    cout << "2. append: " << cpp_str.append(" in TSU") << endl; // 2
    string cpp_str_sub = cpp_str.substr(0, 11);
    cout << "3. substr: " << cpp_str_sub << endl;

}

int main() {
    first();
    return 0;
}
//упражнение 4 -> реализовать через char и через str, ввод через клаву значений до 20, проверка из условия
//реализация через войды и основной main