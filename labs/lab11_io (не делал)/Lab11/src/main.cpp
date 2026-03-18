#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void demo_io() {
    // cin, cout
    int a;
    cout << "Number: " ;
    cin >> a;
    cout << a << endl;

    // scanf, printf
    int b;
    printf("Number: ");
    scanf("%d", &b);
    printf("%d\n", b);

    while (getchar() != '\n');

    // gets, puts
    char str[100];
    puts("String: ");
    fgets(str, 100, stdin);
    puts(str);

    // read, write
    char str2[100];
    cout << "String: ";
    cin.read(str2, 10);
    cout.write(str2, cin.gcount());
}

void solution() {
    char words[50][26];
    int n = 0;

    FILE *f = fopen("input.txt", "r");

    if (!f) {
        cout << "No file" << endl;
    }

    while (!feof(f) && n < 50) {
        if (fscanf(f, "%s", words[n]) == 1) {
            n++;
        }
    }
    fclose(f);

    if (n == 0) {
        cout << "No words" << endl;
    }


}


int main() {
    demo_io();
}