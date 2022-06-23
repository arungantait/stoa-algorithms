#include <stdio.h>
#include "GRAPH.h"
#include <stdlib.h>
/* Add:
 * 1) GRAPHcopy
 * 2) GRAPHdestroy
 * 3) GRAPHremoveE
 * 4) GRAPHshow
 */

typedef struct node *link;
struct node { int v; link next; };
struct graph {int V; int E; link *adj; };

link NEW (int v, link next) {
    link x = malloc(sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}

Graph GRAPHinit (int V) {
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = malloc(V*sizeof (link));
    for (v=0; v<V; v++) G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE(Graph G, Edge e) {
    // observe that we are not checking
    // for multiple edges; hence this can
    // build multigraphs. This also keeps
    // insertion time constant.
    int u = e.u;
    int v = e.v;
    G->adj[u] = NEW(v, G->adj[u]);
    G->adj[v] = NEW(u, G->adj[v]);
    G->E++;
}

int GRAPHedges(Edge a[], Graph G) {
    int v, E=0; link t;
    for (v = 0; v < G->V; v++)
        for (t = G->adj[v]; t != NULL; t = t->next)
            if (v < t->v) a[E++] = EDGE(v, t->v);
    return E;
}
