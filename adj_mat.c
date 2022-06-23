#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"
struct graph {
	int V; // number of vertices
	int E; // number of edges
	int **adj; // pointer to 2-D adjacency matrix
};

Edge EDGE(vertex u, vertex v)
{
	Edge e = {
			u, v
	};
	return e;
}

int ** MATRIXint(int r, int c, int val)
{
	int i, j;
	int **t = malloc(r * sizeof(int *));

	// for small |V|, the cost of |V| calls to malloc
	// might predominate
	for (i=0; i<r; i++)
		t[i] = malloc(c * sizeof(int));
	for (i=0; i<r; i++)
		for (j=0; j<c; j++)
			t[i][j] = val;
	return t;
}

Graph GRAPHinit(int V)
{
	// In this implementation, initializing 
	// a graph is equivalent to initializing
	// it's adjacency matrix
	Graph G = malloc(sizeof(Graph *));
	G->V = V; G->E = 0;
	G->adj = MATRIXint(V, V, 0);
	return G;
}

void GRAPHinsertE (Graph G, Edge e)
{
	// We are only considering undirected
	// graphs here.
	vertex u = e.u, v = e.v;
	if (G->adj[u][v] == 0) G->E++;
	G->adj[u][v] = 1;
	G->adj[v][u] = 1;
}

void GRAPHremoveE(Graph G, Edge e)
{
	vertex u = e.u, v = e.v;
	if (G->adj[u][v] == 1) G->E--;
	G->adj[u][v] = 0;
	G->adj[v][u] = 0;
}

int GRAPHedges(Edge a[], Graph G)
{
	vertex u, v;
	int E = 0;
	for (u = 0; u < G->V; u++)
		for (v = u+1; v < G->V; v++)
			if (G->adj[u][v] == 1)
				a[E++] = EDGE(u, v);
	return E;
}

void GRAPHshow(Graph G)
{
	int i, j;
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++)
	{
		printf("%2d:", i);
		for (j = 0; j < G->V; j++)
			if(G->adj[i][j] == 1) printf(" %2d", j);
		printf("\n");
	}
}
