#include <cstdio>
#include <cstring>

// Функция удаляет знаки препинания в конце слова (очень примитивно)
void clean_word(char* word) {
    size_t len = strlen(word);
    while (len > 0 && (word[len-1] == '.' || word[len-1] == ',' || 
                       word[len-1] == '!' || word[len-1] == '?' || 
                       word[len-1] == ';' || word[len-1] == ':')) {
        word[len-1] = '\0';
        len--;
    }
}

int main() {
    char str[1000];
    printf("Введите строку: ");
    fgets(str, sizeof(str), stdin);

    // Убираем перевод строки в конце
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }

    char words[100][100];   // до 100 слов, каждое не длиннее 99 символов
    int counts[100] = {0};
    int wordCount = 0;

    int i = 0;
    while (str[i] != '\0') {
        // Пропускаем пробелы
        while (str[i] == ' ') {
            i++;
        }
        if (str[i] == '\0') break;

        // Начало очередного слова
        int start = i;
        while (str[i] != ' ' && str[i] != '\0') {
            i++;
        }
        int end = i;

        // Копируем слово во временный буфер (не более 99 символов)
        char temp[100];
        int k;
        int length = end - start;
        if (length > 99) length = 99; // обрезаем, если слишком длинное
        for (k = 0; k < length; k++) {
            temp[k] = str[start + k];
        }
        temp[length] = '\0';

        // Удаляем знаки препинания в конце слова
        clean_word(temp);

        // Если после очистки слово стало пустым – пропускаем
        if (strlen(temp) == 0) {
            continue;
        }

        // Ищем, встречалось ли такое слово раньше
        int found = -1;
        for (int j = 0; j < wordCount; j++) {
            if (strcmp(words[j], temp) == 0) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            counts[found]++;
        } else {
            // Используем strcpy, но предварительно убеждаемся, что не переполним words
            strcpy(words[wordCount], temp);
            counts[wordCount] = 1;
            wordCount++;
        }
    }

    // Поиск самого частого слова
    if (wordCount > 0) {
        int maxIdx = 0;
        for (int i = 1; i < wordCount; i++) {
            if (counts[i] > counts[maxIdx]) {
                maxIdx = i;
            }
        }
        printf("Самое частое слово: %s\n", words[maxIdx]);
    } else {
        printf("В строке нет слов.\n");
    }

    return 0;
}