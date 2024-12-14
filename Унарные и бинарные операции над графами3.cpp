#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define N 5  
// Функция для вывода матрицы смежности
void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для объединения графов
void union_graphs(int M1[N][N], int M2[N][N], int G[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            G[i][j] = M1[i][j] || M2[i][j];
        }
    }
}

// Функция для пересечения графов
void intersection_graphs(int M1[N][N], int M2[N][N], int G[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            G[i][j] = M1[i][j] && M2[i][j];
        }
    }
}

// Функция для кольцевой суммы графов
void symmetric_difference_graphs(int M1[N][N], int M2[N][N], int G[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            G[i][j] = M1[i][j] != M2[i][j];
        }
    }
}

int main() {
    setlocale(LC_ALL, ""); 
  
    int M1[N][N] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };

    int M2[N][N] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    int G[N][N];  
    // Объединение графов
    printf("Объединение графов G1 и G2:\n");
    union_graphs(M1, M2, G);
    print_matrix(G);

    // Пересечение графов
    printf("\nПересечение графов G1 и G2:\n");
    intersection_graphs(M1, M2, G);
    print_matrix(G);

    // Кольцевая сумма графов
    printf("\nКольцевая сумма графов G1 и G2:\n");
    symmetric_difference_graphs(M1, M2, G);
    print_matrix(G);

    return 0;
}
