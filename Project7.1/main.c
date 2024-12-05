#include <malloc.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

int enter_number(int* n, int words) {
    if (scanf_s("%d", n) != 1 || *n > words || *n < 1) {
        printf("Sorry, but your request is incorrect. Try again\n");
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
            s = (char*)realloc(s, capacity * sizeof(char));  // создаём новую строку с увеличенной ёмкостью  
            if (s == NULL) {
                return 1;
            }
        }

        c = getchar();         
    } while (c != '\n');

    if (* len_str > 0 && s[*len_str] != ' ') {
        s[(*len_str)++] = ' ';
    }
  
    s[*len_str] = '\0';

    return s; 
}

int n_words(char* s, int len_str) {
    int number = 0;
    for (int i = 0; i < len_str; ++i) {
        if (s[i] == ' ') {
            number++;
        }
    }
    return number + 1;
}

int k_word_change(char* s, int len_str, int k) {
    int counter = 0;
    int ind_1 = -1, ind_2 = -1; //индексы начала и конца слова
    if (k == 1) {
        ind_1 = 0;
        for (int i = 0; i < len_str; ++i) {
            if (s[i] == ' ') {
                ind_2 = i - 1;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < len_str; ++i) {
            if (s[i] == ' ') {
                counter++;
            }
            if (s[i] == ' ' && counter == k - 1) {
                ind_1 = i + 1; //нашли начало слова
            }
            if (s[i] == ' ' && counter == k) {
                ind_2 = i - 1; //нашли конец слова
                break;
            }
        }
    }
    if (ind_1 != -1 && ind_2 != -1) {
        for (int j = 0; j < (ind_2 - ind_1 + 1) / 2; ++j) {
            int tmp = s[ind_1 + j];
            s[ind_1 + j] = s[ind_2 - j];
            s[ind_2 - j] = tmp;
        }
        return 1;
    }
    else {
        return 0;
    }
}

int main() {

    do{
        int len_str, k = 0;
        printf("Please, enter the string: \n");
        char* s = input_string(&len_str); //указатель на строку

        int words = n_words(s, len_str); //кол-во слов

        printf("Please, enter the number of the word you want to 'change': ");
        if (!enter_number(&k, words)) {
            free(s);
            continue;
        }
        printf("\n");

         if (!k_word_change(s, len_str, k)) {
            printf("Sorry, but your request is incorrect. Try again\n");
            continue;
        }

        puts("Result: ");
        printf("%s\n", s); 

      // free(s);   
       
    } while (puts("Do you want to run the program again? Select 1 to continue, 0 to exit"), _getch() == '1');

    printf("Thanks for using the program! All the best!\n");
    return 0;
}
