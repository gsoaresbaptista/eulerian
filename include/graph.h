#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

typedef struct node {
    int vertex;
    struct node* next;
} node;

typedef struct graph {
    int num_vertices;
    node** adj_lists;
    int* degrees;
} graph;

/**
 * @brief Creates a graph with a specified number of vertices.
 * 
 * @param vertices Number of vertices in the graph.
 * @return Pointer to the newly created graph.
 * 
 * @complexity O(V), where V is the number of vertices.
 */
graph* graph_create(int vertices);

/**
 * @brief Adds an edge between two vertices in the graph (undirected).
 * 
 * @param g Pointer to the graph.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * 
 * @complexity O(1) for each addition.
 */
void graph_add_edge(graph* g, int src, int dest);

/**
 * @brief Removes an edge between two vertices in the graph.
 * 
 * @param g Pointer to the graph.
 * @param src Source vertex.
 * @param dest Destination vertex.
 * 
 * @complexity O(E), where E is the number of edges adjacent to the vertices.
 */
void graph_remove_edge(graph* g, int src, int dest);

/**
 * @brief Checks if the graph has an Eulerian circuit (i.e., all vertices have even degrees).
 * 
 * @param g Pointer to the graph.
 * @return True if the graph has an Eulerian circuit, false otherwise.
 * 
 * @complexity O(V), where V is the number of vertices.
 */
bool graph_is_eulerian(graph* g);

/**
 * @brief Dumps the graph into a .dot file to be used with Graphviz.
 * 
 * @param g Pointer to the graph.
 * @param filename Name of the output file.
 * 
 * @complexity O(V + E), where V is the number of vertices and E is the number of edges.
 */
void graph_dump_to_dot(graph* g, const char* filename);

/**
 * @brief Frees all dynamically allocated memory in the graph.
 * 
 * @param g Pointer to the graph.
 * 
 * @complexity O(V + E), where V is the number of vertices and E is the number of edges.
 */
void graph_free(graph* g);

/**
 * @brief Finds the Eulerian circuit using Hierholzer's Algorithm.
 * 
 * @param g Pointer to the graph.
 * @param start_vertex Starting vertex for the algorithm.
 * @param circuit Stack to store the Eulerian circuit.
 * 
 * @complexity O(E), where E is the number of edges.
 */
void graph_hierholzer_algorithm(graph* g, int start_vertex, stack* circuit);

#endif
