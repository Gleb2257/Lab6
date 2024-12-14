#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define N 5 
int is_valid_index(int index) {
    return index >= 0 && index < N;
}

// Функция для вывода матрицы смежности
void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция отождествления двух вершин в матрице смежности
void merge_vertices_matrix(int matrix[N][N], int v1, int v2) {
    if (!is_valid_index(v1) || !is_valid_index(v2)) {
        printf("Ошибка: неверные индексы вершин.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        if (matrix[v2][i] == 1) {
            matrix[v1][i] = 1; 
            matrix[i][v1] = 1;
        }
        matrix[v2][i] = 0; 
        matrix[i][v2] = 0;
    }
    printf("Матрица после отождествления вершин %d и %d:\n", v1, v2);
    print_matrix(matrix);
}

// Функция стягивания ребра между двумя вершинами в матрице смежности
void contract_edge_matrix(int matrix[N][N], int v1, int v2) {
    merge_vertices_matrix(matrix, v1, v2);
    printf("Матрица после стягивания ребра между вершинами %d и %d:\n", v1, v2);
    print_matrix(matrix);
}

// Функция расщепления вершины в матрице смежности
void split_vertex_matrix(int matrix[N][N], int v) {
    if (!is_valid_index(v)) {
        printf("Ошибка: неверный индекс вершины.\n");
        return;
    }

    int new_vertex = N - 1; 
    for (int i = 0; i < N; i++) {
        if (matrix[v][i] == 1 && i != v) {
            matrix[v][i] = 0;
            matrix[i][v] = 0;
            matrix[new_vertex][i] = 1;
            matrix[i][new_vertex] = 1;
        }
    }
    printf("Матрица после расщепления вершины %d:\n", v);
    print_matrix(matrix);
}

int main() {
    setlocale(LC_ALL, ""); 
    int matrix[N][N] = { {0, 1, 0, 1, 0},
                         {1, 0, 1, 0, 1},
                         {0, 1, 0, 1, 0},
                         {1, 0, 1, 0, 1},
                         {0, 1, 0, 1, 0} };

    printf("Исходная матрица смежности:\n");
    print_matrix(matrix);

    int v1, v2, v;

    printf("\nВведите вершины для отождествления в матрице (v1 v2): ");
    scanf_s("%d %d", &v1, &v2);
    if (is_valid_index(v1) && is_valid_index(v2)) {
        merge_vertices_matrix(matrix, v1, v2);
    }
    else {
        printf("Ошибка: введены неверные индексы вершин.\n");
    }

    printf("\nВведите вершины для стягивания ребра в матрице (v1 v2): ");
    scanf_s("%d %d", &v1, &v2);
    if (is_valid_index(v1) && is_valid_index(v2)) {
        contract_edge_matrix(matrix, v1, v2);
    }
    else {
        printf("Ошибка: введены неверные индексы вершин.\n");
    }

    printf("\nВведите вершину для расщепления в матрице: ");
    scanf_s("%d", &v);
    if (is_valid_index(v)) {
        split_vertex_matrix(matrix, v);
    }
    else {
        printf("Ошибка: введен неверный индекс вершины.\n");
    }

    return 0;
}

