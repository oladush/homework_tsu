// Не очень красивое решение. С циклом for вышло бы лучше.

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int i = 0;
    int fib_now = 0, fib_old = 1, t;

    while(i < n){
        t = fib_now;
        fib_now += fib_old;
        fib_old = t;
        i++;

        printf("%d ", fib_now);
    }
}
