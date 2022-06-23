#ifndef __graph_h__
#define __graph_h__

typedef unsigned int vertex;

typedef struct edge {
    vertex u;   // first vertex
    vertex v;   // second vertex
} edge_t;

typedef struct node *link;

typedef struct node {
    vertex v;
    link next;
} node_t;

typedef node_t *graph;

graph create_graph(int);
void destroy(graph, int);
graph add_edge_dir(graph, vertex, vertex, int);
graph add_edge_undir(graph, vertex, vertex, int);
graph delete_edge_dir(graph, edge_t, int);
graph delete_edge_undir(graph, edge_t, int);
link find_edge(graph, edge_t, int);
void print_graph(graph, int);

#endif