#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

int main() {
    // Create a graph with 5 vertices
    int vertices = 9;
    graph* g = graph_create(vertices);

    // Add edges
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 2);
    graph_add_edge(g, 0, 3);
    graph_add_edge(g, 0, 7);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 1, 3);
    graph_add_edge(g, 1, 4);
    graph_add_edge(g, 2, 4);
    graph_add_edge(g, 2, 5);
    graph_add_edge(g, 2, 6);
    graph_add_edge(g, 2, 6);
    graph_add_edge(g, 3, 4);
    graph_add_edge(g, 3, 7);
    graph_add_edge(g, 4, 5);
    graph_add_edge(g, 4, 7);
    graph_add_edge(g, 4, 8);
    graph_add_edge(g, 5, 6);
    graph_add_edge(g, 5, 8);
    graph_add_edge(g, 6, 8);
    graph_add_edge(g, 7, 8);

    // Dump the graph to a .dot file
    graph_dump_to_dot(g, "graph.dot");

    // Check if the graph has an Eulerian circuit
    if (!graph_is_eulerian(g)) {
        printf("The graph does not have an Eulerian circuit.\n");
        graph_free(g);
        return 0;
    }

    // Find the Eulerian circuit starting from vertex 0
    stack* circuit = stack_create(10);
    graph_hierholzer_algorithm(g, 0, circuit);

    // Output the Eulerian circuit
    printf("Eulerian circuit: ");
    for (int i = circuit->top; i >= 0; i--) {
        printf("%c ", 'a' + circuit->items[i]);
    }
    printf("\n");

    // Free allocated memory
    graph_free(g);
    stack_free(circuit);

    return 0;
}
