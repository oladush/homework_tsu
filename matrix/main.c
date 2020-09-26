/* Задача:
Дана целочисленная матрица A порядка n на m.
Получить матрицу B из матрицы A удалением n-й
строки и k-го столбца.

Данная программа сохраняет массив A, и затем
удаляет строку n (последнюю) и столбец k
(введенный пользователем). При этом матрицы
A и B хранятся в оперативной памяти устройства.

 */

#include <stdio.h>

int main() {
    int n, m;
    printf("Enter size matrix A(n x m):\n");
    scanf("%d %d", &n, &m);

    // matrix A input
    int A[n][m];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            scanf("%d", &A[i][j]);
        }
    }

    // build matrix B
    int B[n-1][m-1], k;
    printf("Enter k (deleted column):\n");
    scanf("%d", &k);

    int t = 0;
    for (int i = 0; i < n-1; i++){
        t = 0;
        for(int j = 0; j < m; j++){
            if (j != k-1) {
                B[i][t] = A[i][j];
                printf("%d ", B[i][t]);
                t++;
            }
        }
        printf("\n");
    }

    return 0;
}
