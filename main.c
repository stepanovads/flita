#include <stdio.h>
#include <stdbool.h>

bool read(int set[], int *n) {
    printf(" Введите количество элементов множества: ");
    scanf(" %d", n);
    
    printf("\n Все элементы множества должны быть уникальны и в двоичной системе счисления");
    printf("\n Введите элементы множества:");

    for (int i = 0; i < *n; i++) {
        scanf("%d", &set[i]);
        
        int b=0;
        b = set[i];
        
        while (b != 0) {
            int a = b % 10;
            if (a != 0 && a != 1) {
                printf(" Ввод неверный");
                return false;
                break;
            }
        b /= 10;
        }
        
        for (int  j = 0; j < i; j++) {
            if (set[j] == set[i]) {
                printf(" Ввод повторный");
                i--;
                return false;
                break;
            }
            else{
                continue;
            }
        }
    }
    return true;
}

int convertToDecimal(int x){
    int result = 0;
    int index = 1;
    
    while(x) {
        result += (x % 10) * index;
        x /= 10;
        index *= 2;
    }
    return result;
}

void convertarrayToDecimal(int set[], int set10[], int n) {
    for(int i = 0; i < n; i++) {
        set10[i] = convertToDecimal(set[i]);
    }
}

void print(int set[], int set10[], int n) {
    printf("\n Элементы множеств:\n");
    
    for (int i = 0; i < n; i++) {
        printf(" %d\t%d\n", set[i], set10[i]);
    }
}

int main() {
    int set[100];
    int n;
    bool a = false;

    a = read(set, &n);
    
    int set10[100];
    
    if (a) {
        printf("\n Ееееееееее\n Ты cмог все норм ввести!!!\n");
        
        convertarrayToDecimal(set, set10, n);
        print(set, set10, n);
    } 
    
    return 0;
}
