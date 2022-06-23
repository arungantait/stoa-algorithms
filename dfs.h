#ifndef __dfs_h__
#define __dfs_h__

#include "graph.h"

typedef void (*visit_ptr)(vertex); 

void traverse(graph, link, visit_ptr, visit_ptr, int *);
void dfs(graph, vertex, visit_ptr, visit_ptr);

#endif