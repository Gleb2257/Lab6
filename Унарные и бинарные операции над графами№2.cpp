#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_VERTICES 10

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node* adjLists[MAX_VERTICES];
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph == NULL) {
        printf("Ошибка выделения памяти для графа\n");
        exit(1);
    }
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Добавление ребра
void addEdge(struct Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Ошибка: неверные индексы вершин\n");
        return;
    }

    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Вывод графа
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("Вершина %d:", v);
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void mergeVertices(struct Graph* graph, int v1, int v2) {
    if (v1 >= graph->numVertices || v2 >= graph->numVertices || v1 == v2) {
        printf("Ошибка: неверные индексы вершин или одинаковые вершины\n");
        return;
    }

    struct Node* temp = graph->adjLists[v2];
    while (temp) {
        addEdge(graph, v1, temp->vertex);
        temp = temp->next;
    }
    free(graph->adjLists[v2]);
    graph->adjLists[v2] = NULL;
    printf("Вершины %d и %d отождествлены.\n", v1, v2);
}

void contractEdge(struct Graph* graph, int v1, int v2) {
    if (v1 >= graph->numVertices || v2 >= graph->numVertices || v1 == v2) {
        printf("Ошибка: неверные индексы вершин или одинаковые вершины\n");
        return;
    }

    mergeVertices(graph, v1, v2);
    printf("Ребро между %d и %d стянуто.\n", v1, v2);
}

// Расщепление вершины
void splitVertex(struct Graph* graph, int v) {
    if (v >= graph->numVertices) {
        printf("Ошибка: неверный индекс вершины\n");
        return;
    }

    int newVertex = graph->numVertices++;
    graph->adjLists[newVertex] = NULL;

    struct Node* temp = graph->adjLists[v];
    while (temp) {
        addEdge(graph, newVertex, temp->vertex);
        temp = temp->next;
    }
    printf("Вершина %d расщеплена на %d и %d.\n", v, v, newVertex);
}

int main() {
    setlocale(LC_ALL, "");

    int vertices = 5;
    struct Graph* graph = createGraph(vertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    printf("Изначальный граф:\n");
    printGraph(graph);

    int v1, v2;
    printf("Введите вершины для отождествления: ");
    scanf("%d %d", &v1, &v2);
    mergeVertices(graph, v1, v2);
    printGraph(graph);

    printf("Введите вершины для стягивания ребра: ");
    scanf("%d %d", &v1, &v2);
    contractEdge(graph, v1, v2);
    printGraph(graph);

    printf("Введите вершину для расщепления: ");
    scanf("%d", &v1);
    splitVertex(graph, v1);
    printGraph(graph);

    return 0;
}

