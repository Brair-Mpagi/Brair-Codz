#include <stdio.h>
#include <stdlib.h>

swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return(*a , *b);
}

int main() {
    int a = 0;
    int b = 0;

    printf("Enter numbers to swap\n");
    printf("num1: "); 
    scanf("%d", &a);
    printf("num2: "); 
    scanf("%d", &b);

    printf("Before Swap: %d  %d\n", a, b);
    swap(&a, &b);
    printf("After swap: %d %d\n", a, b);

    return 0;
}

