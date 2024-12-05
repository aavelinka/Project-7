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

    s[*len_str] = '\0';

    return s;
}

int insert(char* s, int* len_str, const char* s0, int len_s0, int position) {
    
    if (position < 0 || position > len_str) {
        printf("Sorry, but your request is incorrect. Try again\n");
        return 0;
    }

    (*len_str) += len_s0;
    s = (char*)realloc(s, (*len_str) * sizeof(char));
    if (s == NULL) {
        printf("Sorry, but memory allocation failed\n");
        return 0;
    }

    for (int i = *len_str - 1; i > position; --i) {
        s[i] = s[i - len_s0 - 1];
    }
    
     for (int i = 0; i < len_s0; ++i) {
        s[position + i] = s0[i];
    }

    return 1;
}

int main() {

    do {
        int len_str, len_s0;
        char c;
        puts("Please, enter the string: ");
        char* s = input_string(&len_str); //указатель на original строку

        printf("Please, select the symbol you want to insert before:  ");
        scanf_s("%c", &c);

        printf("Write a string that will be an insert: ");
        char* s0 = input_string(&len_s0);
        for (int i = 0; i < len_s0 - 1; ++i) {
            s0[i] = s0[i + 1];
        }
        len_s0 -= 1;
        s0[len_s0 - 1] = '\0';

        for (int j = 0; j < len_str; ++j) {
            if (s[j] == c) {
                if (!insert(s, &len_str, s0, len_s0, j)) {
                    continue;
                }
            }
        }

        puts("Result: ");
        printf("%s\n", s);

   //     free(s0);
    //    free(s);

    } while (puts("Do you want to run the program again? Select 1 to continue, 0 to exit"), _getch() == '1');

    printf("Thanks for using the program! All the best!");
    return 0;
}
