#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

char* strcat(char* str1, const char* str2) {
    char* original_str1 = str1;
    while (*str1)
    {
        str1++;
    }
    while (*str2)
    {
        *str1 = *str2;
        str1++;
        str2++;
    }
    *str1 = '\0';
    return original_str1;
}
//объединение строк

int enter_number(int* n) {
    if (scanf_s("%d", n) != 1 || *n <= 0) {
        printf("Data is incorrect\n");
        return 0;
    }
    return 1;
}

char* input_string(int* len_str) {
    *len_str = 0;
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* s = (char*)malloc(capacity * sizeof(char)); // динамическая пустая строка

    char c = getchar(); // символ для чтения данных

    do {
        s[(*len_str)++] = c; // заносим в строку новый символ

        // если реальный размер больше размера контейнера, то увеличиваем ёмкость строки в два раза
        if (*len_str >= capacity) {
            capacity *= 2;
            s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }

        c = getchar();

    } while ((c != '\n'));

    if (*len_str > 0 && s[*len_str] != ' ') {
        s[(*len_str)++] = ' ';
    }

    if (s[0] == '\n') {
        for (int j = 0; j < *len_str - 1; ++j) {
            s[j] = s[j + 1];
        }
        (*len_str) -= 1;
    }

    s[*len_str] = '\0';

    return s;
}

void sort_insert(char** a_str, int* short_words, int n) {
    for (int i = 0; i < n; ++i) {
        int min = short_words[i];
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (short_words[j] < min) {
                min = short_words[j];
                min_index = j;
            }
        }
        int tmp = short_words[i];
        short_words[i] = short_words[min_index], short_words[min_index] = tmp;
        char* temp = a_str[i];
        a_str[i] = a_str[min_index], a_str[min_index] = temp;
    }
}

int len_word(const char** a_str, int len_s_n, int i) {
    int min = 0, count = 0;
    for (int j = 0; j < len_s_n; ++j) {
        if (a_str[i][j] != ' ')
            count++;
        if (a_str[i][j] == ' ') {
            if (min != 0 && min > count) {
                min = count;
            }
            else if (min == 0) {
                min = count;
            }
            count = 0;
        }
    }
    if (min != 0) {
        return min;
    }
    else return 0;
}

int main() {

    do {
        int n;

        printf("Please, enter the desired number of strings: ");
        if (!enter_number(&n)) {
            continue;
        }
        char** a_str = (char**)malloc(n * sizeof(char*)); 
        if (!a_str) {
            printf("Sorry, memory allocation failed");
            free(a_str);
            continue;
        }
        int* short_words = (int*)malloc(n * sizeof(int));
        if (!short_words) {
            printf("Sorry, memory allocation failed");
            free(short_words);
            continue;
        }

        for (int i = 0; i < n; ++i) {
            int len_s_n;
            printf("Please, enter the %d string: ", i + 1);
            a_str[i] = input_string(&len_s_n); //указатель на i-ую строку
            short_words[i] = len_word(a_str, len_s_n, i);
        }
       
        sort_insert(a_str, short_words, n);

        puts("Result: ");
        for (int i = 0; i < n; ++i) {
            printf("%s\n", a_str[i]);
        }
        
    } while (puts("Do you want to run the program again? Select 1 to continue, 0 to exit"), _getch() == '1');

    printf("Thanks for using the program! All the best!\n");
    return 0;
}
