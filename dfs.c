#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dfs.h"


void traverse(graph g, link lnk, visit_ptr previsit, visit_ptr postvisit, int *visited) {
    link list = g->list;
    if (previsit != NULL) previsit(lnk->v);
    visited[lnk->v - 1] = 1;
    link tmp = list[lnk->v - 1].next;
    while (tmp != NULL) {
        if (!visited[tmp->v - 1]) traverse(g, tmp, previsit, postvisit, visited);
        tmp = tmp->next;
    }
    if (postvisit!= NULL) postvisit(lnk->v);
}

void dfs(graph g, vertex init, visit_ptr previsit, visit_ptr postvisit) {
    int vmax = g->V;
    int *visited = malloc(vmax * sizeof(int));

    // Initialization:
    for (int i = 0; i < vmax; i++) {
        visited[i] = 0;
    }

    /* for (int i = 0; i < vmax; i++) {
        if (!visited[g[i].v - 1]) traverse(g, &g[i], previsit, postvisit, visited);
    } */

    traverse(g, &g->list[init - 1], previsit, postvisit, visited);
}