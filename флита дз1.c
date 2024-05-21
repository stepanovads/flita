#include <stdio.h>
#include <stdbool.h>

bool read(char set[], int n) {
    printf("Введите количество элементов множества: ");
    scanf("%d", &n);

    printf("Введите элементы множества:");
    for (int i = 0; i < n; i++) {
        scanf(" %c", &set[i]); 
        if (set[i] != '0' && set[i] != '1') {
            printf("Не 2сс.\n");
            return false;
        }
    }
    return true;
}
/*
void convertToDecimal(char set[], int set10[], int n) {
    for (int i = 0; i < n; i++) {
        if set[i]  'цифра из set[i] в числе ==1'
        set10[i]+= 2^i
    }
}
*/
void print(char set[], int set10[], int n) {
    printf("Элементы множеств:\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\n", set[i], set10[i]);
    }
}

int main() {
    char set[100];
    int n;
    bool a;

    a = read(set, n);
    int set10[100];

    if (a) {
        printf("Все ок.\n");
//        convertToDecimal(set, set10, n);
        print(set, set10, n);
    } else {
        return 1; // Завершаем программу с ошибкой
    }

    return 0;
}
