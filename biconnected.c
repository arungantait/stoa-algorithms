#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dfs.h"

typedef struct vnode_t {
    vertex v;
    struct vnode_t *next;
} vnode;

vertex *prev;
vnode *stack;
int *rank;
int *low;
int clock;
void push(vnode *, vertex);
vertex pop(vnode *);
void previsit(vertex);
void postvisit(vertex);

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
    // gprint(my_graph, directed); 

    // biconnected components
    // biconnected(my_graph, 1);
    dfs(my_graph, 2, previsit, postvisit);
    /* printf("%d\n", my_bcc);
    for (int i = 0; i < my_bcc; i++) {
        bcc_show(my_graph, i);
    } */

    return 0;
}

void push(vnode *S, vertex v) {
    vnode *node = malloc(sizeof(vnode));
    node->v = v;
    node->next = NULL;
    if (S == NULL) S->next = node;
    else {
        node->next = S->next;
        S->next = node;
    }
}

vertex pop(vnode *S) {
    vertex v = S->next->v;
    S->next = S->next->next;
    return v;
}

void traverse(graph g, link lnk, visit_ptr previsit, visit_ptr postvisit, int *visited) {
    link list = g->list;
    if (previsit != NULL) previsit(lnk->v);
    visited[lnk->v - 1] = 1;
    link tmp = list[lnk->v - 1].next;
    while (tmp != NULL) {
        if (!visited[tmp->v - 1]){
            prev[tmp->v - 1] = lnk->v;
            traverse(g, tmp, previsit, postvisit, visited);
        } else {
            low[lnk->v - 1] = (low[lnk->v - 1] < rank[tmp->v - 1]) ? low[lnk->v - 1] : rank[tmp->v - 1];  
        }
        tmp = tmp->next;
    }
    if (postvisit!= NULL) postvisit(lnk->v);
}

void dfs(graph g, vertex init, visit_ptr previsit, visit_ptr postvisit) {
    int vmax = g->V;
    int *visited = malloc(vmax * sizeof(int));
    stack = malloc(sizeof(vnode));
    stack->v = 0;
    stack->next = NULL;
    prev = calloc((g->V), sizeof(vertex));
    rank = calloc((g->V) , sizeof(int));
    low = calloc((g->V) , sizeof(int));

    // Initialization:
    for (int i = 0; i < vmax; i++) {
        visited[i] = 0;
    }

    /* for (int i = 0; i < vmax; i++) {
        if (!visited[g[i].v - 1]) traverse(g, &g[i], previsit, postvisit, visited);
    } */

    traverse(g, &g->list[init - 1], previsit, postvisit, visited);
}

void previsit(vertex v) {
    clock += 1;
    rank[v - 1] = clock;
    low[v - 1] = clock;
    push(stack, v);
}

void postvisit(vertex s){
    if (rank[prev[s - 1]] == 1) {
        vertex p;
        while ((p = pop(stack)) != s) {
            printf("%d - ", p);
        }
        printf("%d - %d\n", s, prev[s - 1]);
    } else {
        if (low[s - 1] < rank[prev[s - 1]]) {
            low[prev[s-1]] = (low[prev[s-1]] < low[s-1]) ? low[prev[s-1]] : low[s-1];
            return; 
        } else {
            vertex p;
            while ((p = pop(stack)) != s) {
                printf("%d - ", p);
            }
            printf("%d - %d\n", s, prev[s - 1]);
        }
    }
}