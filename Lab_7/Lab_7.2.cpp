#include <iostream>
#include <cstdarg>
#include <cstring>
#include <clocale>

using namespace std;

int days(int dates, ...) {
    va_list args;
    va_start(args, dates);

    for (int i = 0; i < dates; i++) {
        const char* s = va_arg(args, const char*);
        cout << s << " ";
    }

    va_end(args);
    cout << endl;

    return 10;
}


int main() {
    setlocale(LC_ALL, "Russian");

    days(3, "01.12.2024", "23.02.2026", "12.06.2000");

    return 0;
}