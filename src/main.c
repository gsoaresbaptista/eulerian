#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"

int main() {
    int sizes[] = {4, 6, 8};  // Tamanhos dos grafos
    int count = sizeof(sizes) / sizeof(sizes[0]);
    
    // Criar múltiplos grafos Eulerianos
    graph** eulerian_graphs = create_multiple_eulerian_graphs(sizes, count);

    // Dump para arquivos .dot para visualizar os grafos
    for (int i = 0; i < count; i++) {
        char filename[20];
        sprintf(filename, "graph%d.dot", i);
        graph_dump_to_dot(eulerian_graphs[i], filename);
        graph_free(eulerian_graphs[i]);
    }

    free(eulerian_graphs);
    return 0;
}
