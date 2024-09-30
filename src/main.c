#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

// Function to check if a vertex has any unvisited edges
bool graph_has_unvisited_edges(graph* g, int vertex) {
    return g->adj_lists[vertex] != NULL;
}

// Hierholzer's Algorithm to find the Eulerian circuit
void graph_find_eulerian_circuit(graph* g, int start_vertex, stack* circuit) {
    stack* current_path = stack_create(10);
    stack_push(current_path, start_vertex);

    while (current_path->top != -1) {
        int current_vertex = current_path->items[current_path->top];

        if (graph_has_unvisited_edges(g, current_vertex)) {
            node* next_node = g->adj_lists[current_vertex];
            int next_vertex = next_node->vertex;

            graph_remove_edge(g, current_vertex, next_vertex);
            stack_push(current_path, next_vertex);
        } else {
            int vertex = stack_pop(current_path);
            stack_push(circuit, vertex);
        }
    }

    stack_free(current_path);
}

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
    graph_find_eulerian_circuit(g, 0, circuit);

    // Output the Eulerian circuit
    printf("Eulerian circuit: ");
    for (int i = circuit->top; i >= 0; i--) {
        printf("%d ", circuit->items[i]);
    }
    printf("\n");

    // Free allocated memory
    graph_free(g);
    stack_free(circuit);

    return 0;
}
