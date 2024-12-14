#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define N1 3  
#define N2 3  
#define N (N1 * N2)  
// Функция для вывода матрицы смежности
void print_matrix(int matrix[N][N], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для вычисления декартова произведения графов
void cartesian_product(int M1[N1][N1], int M2[N2][N2], int G[N][N]) {
    for (int i1 = 0; i1 < N1; i1++) {
        for (int j1 = 0; j1 < N2; j1++) {
            for (int i2 = 0; i2 < N1; i2++) {
                for (int j2 = 0; j2 < N2; j2++) {
                    int v1 = i1 * N2 + j1;  
                    int v2 = i2 * N2 + j2;  
                    if ((i1 == i2 && M2[j1][j2] == 1) || (j1 == j2 && M1[i1][i2] == 1)) {
                        G[v1][v2] = 1;
                    }
                    else {
                        G[v1][v2] = 0;
                    }
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, ""); 
  
    int M1[N1][N1] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    int M2[N2][N2] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    int G[N][N];  
   
    cartesian_product(M1, M2, G);

    // Вывод результата
    printf("Матрица смежности декартова произведения G = G1 x G2:\n");
    print_matrix(G, N);

    return 0;
}
