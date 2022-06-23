#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dfs.h"

int *components; // array storing the connected component of a vertex 
int cc;          // number of connected components
int connected_components(graph);
void component_show(graph, int);
void mark(vertex);

int main(int argc, char *argv[]) {
    printf("Enter directed or undirected (d/u)>> ");
    char dir = getchar(); int directed;
    if (dir == 'd') directed = 1;
    if (dir == 'u') directed = 0;
    if (dir != 'd' && dir != 'u') {
        printf("Incorrect type specifier: Specifier must be \'d\' or \'u\'\n");
        return 1;
    }
    graph my_graph = gscan(directed);
    gprint(my_graph, directed); 

    int my_cc = connected_components(my_graph); // works
    printf("%d\n", my_cc);
    for (int i = 0; i < my_cc; i++) {
        component_show(my_graph, i); // works
    }
}

int connected_components(graph g) {
    int vmax = g->V;
    cc = 0;
    components = malloc(vmax * sizeof(int));

    // initialize
    for (int i = 0; i < vmax; i++) {
        components[i] = -1;
    }

    for (int i = 0; i < vmax; i++) {
        if (components[i] == -1) {
            dfs(g, i+1, mark, NULL);
            cc++;
        }
    }

    return cc;
}

void component_show(graph g, int c_number) {
    int vmax = g->V;
    if (c_number > cc) {
        printf("COMPONENT_SHOW: error: There are only %d components\n", cc);
        return;
    }
    printf("cc %d: ", c_number+1);
    for (int i = 0; i < vmax; i++) {
        if (components[i] == c_number) printf("%d - ", g->list[i].v);
    }
    printf("\b\b  \n");
}

void mark(vertex v) {
    components[v - 1] = cc;
}