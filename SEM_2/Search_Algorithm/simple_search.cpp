#include<iostream>
#include<vector>
#include<string>
#include<clocale>

using namespace std;

int linearSearch(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}


int interpolationSearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }

        if (arr[high] == arr[low]) {
            if (arr[low] == target) return low;
            return -1;
        }

        int pos = low + static_cast<int>(
            (static_cast<double>(high - low) / (arr[high] - arr[low])) * (target - arr[low])
            );

        if (arr[pos] == target) {
            return pos;
        }
        if (arr[pos] < target) {
            low = pos + 1;
        }
        else {
            high = pos - 1;
        }
    }
    return -1;
}



int directSubstringSearch(const string& text, const string& pattern) {
    if (pattern.empty()) return 0;
    if (text.size() < pattern.size()) return -1;

    size_t n = text.size();
    size_t m = pattern.size();

    for (size_t i = 0; i <= n - m; ++i) {
        size_t j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void showVector(const vector<int>& arr_to_show) {
    cout << "Первоначальный массив: ";
    for (size_t i = 0; i < arr_to_show.size(); ++i) {
        cout << arr_to_show[i] << " ";
    }
    cout << endl;
}

// Объявления функций (описаны выше)
int linearSearch(const vector<int>& arr, int target);
int binarySearch(const vector<int>& arr, int target);
int interpolationSearch(const vector<int>& arr, int target);
int directSubstringSearch(const string& text, const string& pattern);

int main() {
    // Тестовые данные для поиска в массиве
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<int> sortedData = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    showVector(sortedData);
    int target = 70;

    cout << "--- Поиск в массиве (ищем значение " << target << ") ---" << endl;
    cout << "Линейный поиск: индекс " << linearSearch(sortedData, target) << endl;
    cout << "Бинарный поиск: индекс " << binarySearch(sortedData, target) << endl;
    cout << "Интерполяционный поиск: индекс " << interpolationSearch(sortedData, target) << endl;

    cout << "\n--- Поиск подстроки ---" << endl;
    string text = "Hello, world! Program implementation.";
    string pattern = "world";

    int strIndex = directSubstringSearch(text, pattern);
    cout << "Текст: \"" << text << "\"" << endl;
    cout << "Подстрока: \"" << pattern << "\"" << endl;
    if (strIndex != -1) {
        cout << "Прямой поиск подстроки: найдено на индексе " << strIndex << endl;
    }
    else {
        cout << "Прямой поиск подстроки: совпадений не найдено" << endl;
    }

    return 0;
}