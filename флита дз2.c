#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 5
#define MAX_COLS 40

struct Edge {
    struct Vertex * first, * second;
    char observed;
};
struct Vertex{
    int value;
    char observed;
};
struct Graph{
    struct Edge edges[MAX_COLS];
    struct Vertex vertices[MAX_ROWS];
    int matrix[MAX_ROWS][MAX_COLS], vertices_size, edges_size;
};

void get_size(int* rows, int* currentColumns, FILE *file) {
    int columns = 0;
    char tmp, ch;
    while (fscanf(file, "%c", &ch) == 1) {
        if (ch != '\n' && ch != ' ') {
            if (*rows == 0) columns++;
            tmp = ch;
        } else if (ch == '\n') {
            if (*rows == 0) columns++;
            (*rows)++;
            if (*rows == 1) *currentColumns = columns;
            columns = 0;
        }
    }
}
void ReadMatrixFromFile(const char* inputFilename, int matrix_of_incidence[MAX_ROWS][MAX_COLS], int* vertices_size, int* edges_size) {
    FILE *file = fopen(inputFilename, "r");
    get_size(vertices_size, edges_size, file);
    (*edges_size)--;
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < (*vertices_size); i++)
        for (int j = 0; j < (*edges_size); j++) fscanf(file, "%d", &matrix_of_incidence[i][j]);
    fclose(file);
}
void GetEdges(struct Graph * graph) {
    for (int j = 0; j < graph->edges_size; j++) {
        char loop = 1;
        for (int i = 0; i < graph->vertices_size; i++) {
            if (graph->matrix[i][j] && !graph->edges[j].observed) {
                graph->edges[j].first = &graph->vertices[i];
                graph->vertices[i].value = i;
                graph->edges[j].observed = 1;
                graph->vertices[i].observed = 1;
            }
            else if (graph->matrix[i][j]) {
                graph->edges[j].second = &graph->vertices[i];
                graph->vertices[i].observed = 1;
                graph->vertices[i].value = i;
                loop = 0;
                break;
            }
        }
        if (loop) graph->edges[j].second = graph->edges[j].first;
    }
}
void WriteDotFile(struct Graph *graph) {
    FILE* writer = fopen("graph.dot", "w");
    fprintf(writer, "graph {\n");
    for (int i = 0; i < graph->edges_size; i++) fprintf(writer, "%d -- %d;\n", *graph->edges[i].first, *graph->edges[i].second);
    for (int i = 0; i < graph->vertices_size; i++)
        if (!graph->vertices[i].observed) fprintf(writer, "%d;\n", i);
    fprintf(writer, "}\n");
    fclose(writer);
}
int main() {
    int file_number;
    char inputFilename[200];
    printf("Enter the number of matrix\n>> ");
    scanf("%d", &file_number);
    sprintf(inputFilename, "tests/matrix_of_incendence%d.txt", file_number);
    struct Graph graph = {.edges_size = 0, .vertices_size = 0};
    ReadMatrixFromFile(inputFilename, graph.matrix, &graph.vertices_size, &graph.edges_size);
    for (int i = 0; i < graph.edges_size; i++)  graph.edges[i].observed = 0;
    for (int i = 0; i < graph.vertices_size; i++)  graph.vertices[i].observed = 0;
    GetEdges(&graph);
    WriteDotFile(&graph);
    system("dot -Tpng graph.dot -o graph.png");
    return 0;
}
