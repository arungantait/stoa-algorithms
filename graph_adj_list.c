#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph create_graph(int vmax) {
    graph new_graph = malloc(vmax * sizeof(node_t));
    if (new_graph == NULL) {
        printf("CREATE_GRAPH: Failure in memory allocation\n");
        return NULL;
    }

    for (int i = 0; i < vmax; i++) {
        new_graph[i].v = i + 1;
        new_graph[i].next = NULL;
    }

    return new_graph;
}

void destroy_graph(graph g, int vmax) {
    if (g == NULL) return;

    for (int i = 0; i < vmax; i++) {
        free(&g[i]);
    }

    return;
}

graph add_edge_dir(graph g, vertex u, vertex v, int vmax) {
    if (v > vmax || u > vmax) {
        printf("ADD_EDGE: vertex not found: maximum number of vertices is %d\n", vmax);
        return g;
    } else if (u == v) {
        printf("ADD_EDGE: self-loops not allowed\n");
        return g;
    }

    link tmp = &g[u-1];
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    link new_edge = malloc(sizeof(node_t));
    new_edge->v = v;
    new_edge->next = NULL;
    tmp->next = new_edge;
    return g;
}

graph add_edge_undir(graph g, vertex u, vertex v, int vmax) {

    // add both the edges (u, v) and (v, u) since
    // the graph is undirected.
    g = add_edge_dir(g, u, v, vmax);
    g = add_edge_dir(g, v, u, vmax);

    return g;
}

link find_edge(graph g, edge_t e, int vmax) {
    if (e.v > vmax || e.u > vmax) {
        printf("FIND_EDGE: edge not found: maximum number of vertices is %d\n", vmax);
        return NULL;
    } else if (e.v == e.u) {
        printf("FIND_EDGE: edge not found: self-loop not allowed\n");
        return NULL;
    }

    link tmp = &g[e.u-1];
    while (tmp->next != NULL) {
        if (tmp->next->v == e.v) return tmp;
        
        tmp = tmp->next;
    }

    return NULL;
    
}

graph delete_edge_dir(graph g, edge_t e, int vmax) {
    if (e.u > vmax || e.v > vmax) {
        printf("DELETE_EDGE: edge not found: maximum number of vertices is %d\n", vmax);
        return g;
    } else if (e.u == e.v) {
        printf("DELETE_EDGE: edge not found: self-loops not allowed\n");
        return g;
    }

    link myedge = find_edge(g, e, vmax);
    if (myedge == NULL) return g;

    link tmp = myedge->next;
    myedge->next = myedge->next->next;
    free(tmp); // freeing is very important
    return g;
}

graph delete_edge_undir(graph g, edge_t e, int vmax) {
    // delete both the edges (e., e.v) and (e.v, e,u)
    edge_t rev_e = {e.v, e.u}; 
    g = delete_edge_dir(g, e, vmax);
    g = delete_edge_dir(g, rev_e, vmax);
    return g;
}
void print_graph(graph g, int vmax) {
    for (int i = 0; i < vmax; i++) {
        printf("%d: ", g[i].v);
        link tmp = g[i].next;
        while (tmp != NULL) {
            printf("%d - ", tmp->v);
            tmp = tmp->next;
        }
        printf("\b\b  \n");
    }
}