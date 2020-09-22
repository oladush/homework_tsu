#include <stdio.h>

int main(){
    int number;
    int count_even = 0;
    int count_odd = 0;

    printf("Enter numbers(to exit enter -1):\n");
    do {
        scanf("%d", &number);

        switch (number % 2) {
            case 0 : count_even++; break;
            case 1 : count_odd++ ; break;
        }

    } while (number != -1);

    printf("\nCount even: %d\nCount odd: %d\n", count_even, count_odd);

    return 0;
}
