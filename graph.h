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

typedef struct Graph {
    int V;
    int E;
    link list;
} graph_t;

typedef graph_t *graph;

graph create_graph(int);
void destroy(graph);
int add_edge_dir(graph, vertex, vertex);
int add_edge_undir(graph, vertex, vertex);
int delete_edge_dir(graph, edge_t);
int delete_edge_undir(graph, edge_t);
graph reverse_graph(graph);
link find_edge(graph, edge_t);
void print_graph(graph);
void print_digraph(graph);
graph gscan(int);
void gprint(graph, int);

#endif