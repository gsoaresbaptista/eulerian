#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// Create a new node for the adjacency list
node* graph_create_node(int vertex) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

// Create a graph with 'vertices' vertices
graph* graph_create(int vertices) {
    graph* g = (graph*)malloc(sizeof(graph));
    g->num_vertices = vertices;
    g->adj_lists = (node**)malloc(vertices * sizeof(node*));
    g->degrees = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        g->adj_lists[i] = NULL;
        g->degrees[i] = 0;
    }
    return g;
}

// Add an edge to the graph (undirected)
void graph_add_edge(graph* g, int src, int dest) {
    node* new_node = graph_create_node(dest);
    new_node->next = g->adj_lists[src];
    g->adj_lists[src] = new_node;
    g->degrees[src]++;

    new_node = graph_create_node(src);
    new_node->next = g->adj_lists[dest];
    g->adj_lists[dest] = new_node;
    g->degrees[dest]++;
}

// Remove an edge from the graph
void graph_remove_edge(graph* g, int src, int dest) {
    node* temp = g->adj_lists[src];
    node* prev = NULL;

    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev != NULL) {
            prev->next = temp->next;
        } else {
            g->adj_lists[src] = temp->next;
        }
        free(temp);
        g->degrees[src]--;
    }

    temp = g->adj_lists[dest];
    prev = NULL;
    while (temp != NULL && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        if (prev != NULL) {
            prev->next = temp->next;
        } else {
            g->adj_lists[dest] = temp->next;
        }
        free(temp);
        g->degrees[dest]--;
    }
}

// Check if the graph has an Eulerian circuit
bool graph_is_eulerian(graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->degrees[i] % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Function to dump the graph into a .dot file
void graph_dump_to_dot(graph* g, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing: %s\n", filename);
        return;
    }

    // Start the graph definition
    fprintf(file, "graph G {\n");
    fprintf(file, "\tlayout = neato;\n");
    fprintf(file, "\tsplines = true;\n");
    fprintf(file, "\tnode [shape=point, width=0.05, color=\"#FF9B9B\"];\n");
    fprintf(file, "\tedge [color=\"#606676\"];\n");
    fprintf(file, "\tbgcolor=\"none\";\n");

    // Loop over all vertices in the graph and create nodes with letters near the points
    for (int i = 0; i < g->num_vertices; i++) {
        char label = 'A' + i;
        fprintf(file, "\t%d [xlabel=\"%c\", fontsize=12, fontname=\"Arial\", fontcolor=\"#FF9B9B\"];\n", i, label);
    }

    // Loop over all vertices and add edges between them
    for (int i = 0; i < g->num_vertices; i++) {
        node* current = g->adj_lists[i];
        while (current != NULL) {
            // Avoid duplicate edges in an undirected graph
            if (i < current->vertex) {
                fprintf(file, "\t%d -- %d;\n", i, current->vertex);  // Undirected edge from i to vertex
            }
            current = current->next;
        }
    }

    fprintf(file, "}\n");  // End of graph
    fclose(file);

    printf("Graph dumped to %s\n", filename);
}

// Free all dynamically allocated memory in the graph
void graph_free(graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        node* temp = g->adj_lists[i];
        while (temp) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(g->adj_lists);
    free(g->degrees);
    free(g);
}
