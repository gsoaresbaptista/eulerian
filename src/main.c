#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph.h"
#include "stack.h"

void compare_algorithms(int num_vertices, FILE* csv_file) {
    graph* g_hierholzer = create_eulerian_graph(num_vertices);
    graph* g_fleury = create_eulerian_graph(num_vertices);

    stack* hierholzer_circuit = stack_create(10);
    stack* fleury_circuit = stack_create(10);

    clock_t start_hierholzer = clock();
    graph_hierholzer_algorithm(g_hierholzer, 0, hierholzer_circuit);
    clock_t end_hierholzer = clock();
    double time_hierholzer = ((double)(end_hierholzer - start_hierholzer)) / CLOCKS_PER_SEC;

    clock_t start_fleury = clock();
    fleury_algorithm(g_fleury, 0, fleury_circuit);
    clock_t end_fleury = clock();
    double time_fleury = ((double)(end_fleury - start_fleury)) / CLOCKS_PER_SEC;

    fprintf(csv_file, "%d, %f, %f\n", num_vertices, time_hierholzer, time_fleury);

    graph_free(g_hierholzer);
    graph_free(g_fleury);
    stack_free(hierholzer_circuit);
    stack_free(fleury_circuit);
}

int main() {
    FILE* csv_file = fopen("algorithm_comparison.csv", "w");
    fprintf(csv_file, "Graph Size, Hierholzer Time (s), Fleury Time (s)\n");

    int sizes[] = {
        10, 25, 50, 75,
        100, 250, 500, 750,
        1000, 2500, 5000, 7500,
        10000, 25000, 50000, 75000,
        100000, 250000, 500000, 750000,
        1000000, 2500000, 5000000, 7500000,
        10000000, 25000000, 50000000, 75000000,
    };
    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < count; i++) {
        compare_algorithms(sizes[i], csv_file);
    }
    fclose(csv_file);

    return 0;
}
