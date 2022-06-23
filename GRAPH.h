#ifndef __graph_h__
#define __graph_h__

typedef int vertex;

typedef struct { vertex u; vertex v; } Edge;
Edge EDGE(vertex, vertex); // Edge constructor
typedef struct graph *Graph; // representation independent construction
Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHremoveE(Graph, Edge);
int GRAPHedges(Edge[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph);

#endif
