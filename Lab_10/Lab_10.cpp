#include <cstdio>
#include <cstring>

#define MAX_STR 100   // максимальное количество строк
#define MAX_LEN 100   // максимальная длина строки

int main() {
    int N;
    printf("Введите количество строк: ");
    scanf("%d", &N);
    getchar(); // очищаем символ новой строки после ввода числа

    if (N <= 0 || N > MAX_STR) {
        printf("Некорректное количество строк.\n");
        return 1;
    }

    // Двумерный массив для хранения строк
    char strings[MAX_STR][MAX_LEN + 1]; // +1 для завершающего нуля

    // Ввод строк
    for (int i = 0; i < N; ++i) {
        printf("Введите строку %d: ", i + 1);
        fgets(strings[i], MAX_LEN + 1, stdin);
        // Убираем символ перевода строки, если он есть
        size_t len = strlen(strings[i]);
        if (len > 0 && strings[i][len - 1] == '\n') {
            strings[i][len - 1] = '\0';
        }
    }

    // Поиск индекса самой короткой строки
    int min_index = 0;
    size_t min_len = strlen(strings[0]);
    for (int i = 1; i < N; ++i) {
        size_t cur_len = strlen(strings[i]);
        if (cur_len < min_len) {
            min_len = cur_len;
            min_index = i;
        }
    }

    printf("Самая короткая строка: \"%s\"\n", strings[min_index]);
    printf("Удаляем её...\n");

    // Сдвигаем все последующие строки влево
    for (int i = min_index; i < N - 1; ++i) {
        strcpy(strings[i], strings[i + 1]);
    }
    --N; // уменьшаем количество строк

    // Вывод результата
    printf("Осталось строк: %d\n", N);
    for (int i = 0; i < N; ++i) {
        printf("Строка %d: %s\n", i + 1, strings[i]);
    }

    return 0;
}