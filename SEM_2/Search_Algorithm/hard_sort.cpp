#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <clocale>
using namespace std;

// Алгоритм Кнута-Морриса-Пратта
vector<int> computePrefixFunction(const string& pattern) {
    int m = static_cast<int>(pattern.size());
    vector<int> pi(m, 0);
    int j = 0;
    
    for (int i = 1; i < m; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int kmpSearch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> pi = computePrefixFunction(pattern);
    int j = 0; // Количество совпавших символов
    
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
        }
        if (j == m) {
            return i - m + 1; // Индекс первого вхождения
        }
    }
    return -1;
}



// Алгоритм Бойера-Мура-Хорспула
void preprocessHorspool(const string& pattern, vector<int>& shift) {
    int m = static_cast<int>(pattern.size());
    for (int i = 0; i < 256; ++i) {
        shift[i] = m;
    }
    // Вычисляем сдвиги для всех символов шаблона, кроме последнего
    for (int i = 0; i < m - 1; ++i) {
        shift[static_cast<unsigned char>(pattern[i])] = m - 1 - i;
    }
}

int horspoolSearch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> shift(256);
    preprocessHorspool(pattern, shift);

    int s = 0; // Сдвиг окна шаблона относительно текста
    while (s <= n - m) {
        int j = m - 1;
        // Сравнение справа налево
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            return s; // Совпадение найдено
        }
        // Сдвиг на основе крайнего правого символа в окне текста
        s += shift[static_cast<unsigned char>(text[s + m - 1])];
    }
    return -1;
}



// Полный алгоритм Бойера-Мура
// Эвристика плохой буквы (Bad Character Heuristic)
vector<int> preprocessBadChar(const string& pattern) {
    int m = static_cast<int>(pattern.size());
    vector<int> badChar(256, -1);
    for (int i = 0; i < m; ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = i;
    }
    return badChar;
}

// Эвристика хорошего суффикса (Good Suffix Heuristic)
void preprocessStrongSuffix(const string& pattern, vector<int>& shift, vector<int>& bpos) {
    int m = static_cast<int>(pattern.size());
    int i = m;
    int j = m + 1;
    bpos[m] = j;

    while (i > 0) {
        while (j <= m && pattern[i - 1] != pattern[j - 1]) {
            if (shift[j] == 0) {
                shift[j] = j - i;
            }
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }

    j = bpos[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0) {
            shift[i] = j;
        }
        if (i == j) {
            j = bpos[j];
        }
    }
}

int boyerMooreSearch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> badChar = preprocessBadChar(pattern);
    vector<int> shift(m + 1, 0);
    vector<int> bpos(m + 1, 0);

    preprocessStrongSuffix(pattern, shift, bpos);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        // Сравнение справа налево
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }
        if (j < 0) {
            return s; // Шаблон найден
        } else {
            // Сдвиг по эвристике плохой буквы
            int charShift = j - badChar[static_cast<unsigned char>(text[s + j])];
            // Сдвиг по эвристике хорошего суффикса
            int suffixShift = shift[j + 1];
            // Выбираем максимальный сдвиг
            s += max(charShift, suffixShift);
        }
    }
    return -1;
}



int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string text = "abacadabrabracabara";
    string pattern = "abrac";

    cout << "Текст: \"" << text << "\"" << endl;
    cout << "Шаблон: \"" << pattern << "\"" << endl;

    int posKMP = kmpSearch(text, pattern);
    int posHorspool = horspoolSearch(text, pattern);
    int posBM = boyerMooreSearch(text, pattern);

    cout << "\nРезультаты работы алгоритмов:" << endl;
    cout << "1. KMP: найден на индексе " << posKMP << endl;
    cout << "2. Boyer-Moore-Horspool: найден на индексе " << posHorspool << endl;
    cout << "3. Boyer-Moore: найден на индексе " << posBM << endl;

    return 0;
}