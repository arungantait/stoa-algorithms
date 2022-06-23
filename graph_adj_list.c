#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph create_graph(int vertices) {
    graph new_graph = malloc(sizeof(graph_t));
    if (new_graph == NULL) {
        printf("CREATE_GRAPH: Failure in memory allocation\n");
        return NULL;
    }

    new_graph->V = vertices;
    new_graph->E = 0;
    new_graph->list = malloc(vertices * sizeof(node_t));
    if (new_graph->list == NULL) {
        printf("CREATE_GRAPH: Failure in memory allocation\n");
        return NULL;
    }
    link list = new_graph->list;

    for (int i = 0; i < vertices; i++) {
        list[i].v = i + 1;
        list[i].next = NULL;
    }

    return new_graph;
}

void destroy_graph(graph g) {
    if (g == NULL) return;

    int vmax = g->V;
    link list = g->list;
    for (int i = 0; i < vmax; i++) {
        free(list[i].next);
    }
    free(g);

    return;
}

int add_edge_dir(graph g, vertex u, vertex v) {
    int vmax = g->V;
    if (v > vmax || u > vmax) {
        printf("ADD_EDGE: vertex not found: maximum number of vertices is %d\n", vmax);
        return 1;
    } else if (u == v) {
        printf("ADD_EDGE: self-loops not allowed\n");
        return 1;
    }
    edge_t e = {u, v};
    if (find_edge(g, e) != NULL) {
        printf("ADD_EDGE: parallel edges not allowed\n");
        return 1;
    }
    link list = g->list;
    link tmp = &list[u-1];
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    link new_edge = malloc(sizeof(node_t));
    new_edge->v = v;
    new_edge->next = NULL;
    tmp->next = new_edge;
    g->E++;
    return 0;
}

int add_edge_undir(graph g, vertex u, vertex v) {

    edge_t e = {u, v}; edge_t f = {v, u};
    if (find_edge(g, e) != NULL || find_edge(g, f) != NULL) {
        printf("ADD_EDGE: parallel edges not allowed\n");
        return 1;
    }
    // add both the edges (u, v) and (v, u) since
    // the graph is undirected.
    int failed1 = add_edge_dir(g, u, v);
    if (failed1) return 1;
    int failed2 = add_edge_dir(g, v, u);
    if (failed2) return 1;
    
    g->E--;  // if both additions were successful g->E has increased by 2
             // once for each call of add_edge_dir()
    return 0;
}

link find_edge(graph g, edge_t e) {
    int vmax = g->V;
    if (e.v > vmax || e.u > vmax) {
        printf("FIND_EDGE: edge not found: maximum number of vertices is %d\n", vmax);
        return NULL;
    } else if (e.v == e.u) {
        printf("FIND_EDGE: edge not found: self-loop not allowed\n");
        return NULL;
    }

    link list = g->list;
    link tmp = &list[e.u-1];
    while (tmp->next != NULL) {
        if (tmp->next->v == e.v) return tmp;
        
        tmp = tmp->next;
    }

    return NULL;
    
}

int delete_edge_dir(graph g, edge_t e) {
    int vmax = g->V;
    if (e.u > vmax || e.v > vmax) {
        printf("DELETE_EDGE: edge not found: maximum number of vertices is %d\n", vmax);
        return 1;
    } else if (e.u == e.v) {
        printf("DELETE_EDGE: edge not found: self-loops not allowed\n");
        return 1;
    }

    link myedge = find_edge(g, e);
    if (myedge == NULL) return 1;

    link tmp = myedge->next;
    myedge->next = myedge->next->next;
    free(tmp); // freeing is very important
    g->E--;
    return 0;
}

int delete_edge_undir(graph g, edge_t e) {
    // delete both the edges (e., e.v) and (e.v, e,u)
    edge_t rev_e = {e.v, e.u}; 
    int failed1 = delete_edge_dir(g, e);
    if (failed1) return 1;
    int failed2 = delete_edge_dir(g, rev_e);
    if (failed2) return 1;

    g->E++; // if both deletions were successful g->E has decreased by 2 
            // for each call of delete_edge_dir()
    return 0;
}

graph reverse_graph(graph g) {
    graph g_r = create_graph(g->V);
    link list = g->list;
    for (int i = 0; i < g->V; i++) {
        vertex v = list[i].v;
        link tmp = list[i].next;
        while (tmp != NULL) {
            vertex u = tmp->v;
            add_edge_dir(g_r, u, v);
            tmp = tmp->next;
        }
    }
    return g_r;
}

void print_graph(graph g) {
    int vmax = g->V;
    link list = g->list;
    for (int i = 0; i < vmax; i++) {
        printf("%d: ", list[i].v);
        link tmp = list[i].next;
        while (tmp != NULL) {
            printf("%d - ", tmp->v);
            tmp = tmp->next;
        }
        printf("\b\b  \n");
    }
}

void print_digraph(graph g) {
    for (int i = 0; i < g->V; i++) {
        printf("%d:  ", g->list[i].v);
        link tmp = g->list[i].next;
        for (; tmp != NULL; tmp = tmp->next) {
            printf("%d -> ", tmp->v);
        }
        printf("\b\b\b   \n");
    }
}

graph gscan(int directed) {
    printf("Enter the number of vertices>> ");
    int V;
    scanf("%d", &V);
    graph g = create_graph(V);
    printf("Enter the edges in the format \'a - b\':\n");
    printf(">> ");
    vertex u, v;
    while ((scanf("%d - %d", &u, &v)) == 2) {
        if (u > V || v > V) {
            printf("GREAD: Maximum number of vertices is %d. Please try again..\n", V);
            printf(">> ");
            continue;
        } 
        if (u <= 0 || v <= 0) {
            printf("GREAD: Vertices are integers from 1 to %d. Please try again..\n", V);
            printf(">> ");
            continue;
        }
        if (directed) {
            add_edge_dir(g, u, v);
        } else {
            add_edge_undir(g, u, v);
        }
        printf(">> ");
    }
    return g;
}

void gprint(graph g, int directed) {
    if (directed) print_digraph(g);
    if (!directed) print_graph(g);
}