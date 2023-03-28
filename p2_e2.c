#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "graph.h"
#include "stack.h"
#include "file_utils.h"
#include "algorithms.h"
#include "types.h"

int main(int argc, char *argv[]){
    Graph *g = NULL;
    long to_id, from_id;
    FILE *f;

    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL || argv[0] == NULL) {
        fprintf(stdout, "Usage: %s <filename> <from_id> <to_id>\n", argv[0]);
        return -1;
    }

    f = fopen(argv[1], "r");
    if(!f) {
        fprintf(stdout, "ERROR: 2");
        return -1;
    }

    g = graph_init();
    if(!g){
        fprintf(stdout, "ERROR: 3");
        fclose(f);
        graph_free(g);
        g = NULL;
        return -1;
    }

    if(graph_readFromFile(f, g) == ERROR) {
        fprintf(stdout, "ERROR: 4");
        fclose(f);
        graph_free(g);
        return -1;
    }

    from_id = (long)atoi(argv[2]);
    to_id = (long)atoi(argv[3]);
    if(!graph_contains(g, from_id) || !graph_contains(g, to_id)) {
        fprintf(stdout, "ERROR: 5");
        fclose(f);
        graph_free(g);
        return -1;
    }

    if(graph_depthSearch(g, from_id, to_id) == ERROR) {
        fprintf(stdout, "ERROR: Fallo en depth search");
        fclose(f);
        graph_free(g);
        return -1;
    }

    fclose(f);
    graph_free(g);
    return 0;
}
