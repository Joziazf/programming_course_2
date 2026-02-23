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
    cout << "3. сopy: " << strcpy(c_str_copy, c_str_1) << endl; // 3

    // string cpp
    string cpp_str = "Education";

    cout << "1. len: " << cpp_str.length() << endl; // 1
    cout << "2. append: " << cpp_str.append(" in TSU") << endl; // 2
    string cpp_str_sub = cpp_str.substr(0, 11);
    cout << "3. substr: " << cpp_str_sub << endl;

}

void fourth_char() {
    int n = 0;

    // проверка на ввод
    do {
        cin >> n;
        if (n < 1 || n > 20) {
            cout << "Invalid input. n -> [1; 20]" << endl;
        }
    } while (n < 1 || n > 20); // для проверки n, чтобы if-ом не прерывать выполнение всей программы

    char words[20][11]; // количество слов - 20; количество символов - 11, тк есть символ окончания строки "\0"
    char temp[100]; // просто буфер

    for (int i = 0; i < n; i++) {
        cin >> temp;

        // 1 вариант
        if (strlen(temp) > 10) {
            temp[10] = '\0'; // просто обрежу строку (11 символ = '\0')
        }

        // 2 вариант (не нравится мне)
        // if (strlen(temp) > 10) {
        //     i--;
        //     cout << "len > 10. Try again" << endl;
        // }

        strcpy(words[i], temp);
    }
    for (int i = 1; i < n; i += 2) {
        cout << words[i] << endl;
    }
    cout << endl;
}

void fourth_string() {
    int n = 0;

    // такая же проверка ввода
    do {
        cin >> n;
        if (n < 1 || n > 20) {
            cout << "Invalid input. n -> [1; 20]" << endl;
        }
    } while (n < 1 || n > 20);

    string words[20];
    string temp;

    for (int i = 0; i < n; i++) {
        cin >> temp;

        // 1 вариант
        if (temp.length() > 10) {
            temp = temp.substr(0, 10);
        }

        // 2 вариант
        // if (temp.length() > 10) {
        //     i--;
        //     cout << "len > 10. Try again" << endl;
        // }
        words[i] = temp;
    }

    for (int i = 1; i < n; i += 2) {
        cout << words[i] << endl;
    }
}

int main() {
    first();
    fourth_char();
    fourth_string();
    return 0;
}