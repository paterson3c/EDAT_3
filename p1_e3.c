#include "graph.h"

int main(int argc, char *argv[]) {

    if(!argv[0] || !argv[1] || argv[2] != NULL) 
        return -1;

    Graph *g;
    FILE *f;


    g = graph_init();
    if(!g)
        return -1;
    
    f = fopen(argv[1], "r");
    if(!f) 
        return -1;
    
    if(!graph_readFromFile(f, g))
        return -1;

    graph_print(stdout, g);
    
    fclose(f);
    graph_free(g);

    return 0;
}