CC = gcc
CFLAGS = -Wall -g

connected: connected.c dfs.c graph_adj_list.c
	${CC} ${CFLAGS} -o connected $^

biconnected: biconnected.c graph_adj_list.c
	${CC} ${CFLAGS} -o biconnected $^

clean:
	rm -rf *.o