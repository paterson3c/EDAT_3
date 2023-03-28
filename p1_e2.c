#include "graph.h"

int main() {

    Graph *g;
    int cont = 1, i=0;
    long *aux;

    g = graph_init();
    if(!g)
        return -1;

    cont = graph_newVertex(g, "id:111 tag:Madrid");
    fprintf(stdout, "Inserting Madrid... result...: %d\n", cont);
    if(!cont) {
        graph_free(g);
        return -1;
    }

    cont = graph_newVertex(g, "id:222 tag:Toledo");
    fprintf(stdout, "Inserting Toledo... result...: %d\n", cont);
    if(!cont) {
        graph_free(g);
        return -1;
    }

    fprintf(stdout ,"Inserting edge: 222 ---> 111\n");
    graph_newEdge(g, 222, 111);
    
    fprintf(stdout, "111 --> 222? ");
    if(graph_connectionExists(g, 111, 222)) {
        fprintf(stdout, "Yes\n");
    }
    else {
        fprintf(stdout, "No\n");
    }

    fprintf(stdout, "222 --> 111? ");
    if(graph_connectionExists(g, 222, 111)) {
        fprintf(stdout, "Yes\n");
    }
    else {
        fprintf(stdout, "No\n");
    }

    fprintf(stdout, "Number of connections from 111: %d\n", graph_getNumberOfConnectionsFromId(g, 111));
    fprintf(stdout, "Number of connections from 222: %d\n", graph_getNumberOfConnectionsFromTag(g, "Toledo"));

    fprintf(stdout, "Connections from Toledo:");

    aux = graph_getConnectionsFromTag(g, "Toledo");
    if(!aux) {
        graph_free(g);
        return -1;
    }
    for(i=0, cont = graph_getNumberOfConnectionsFromId(g, 222);i<cont;i++) {
        fprintf(stdout, " %ld", aux[i]);
    }

    fprintf(stdout, "\nGraph:\n");
    
    cont = graph_print(stdout, g);
    if(cont<=0) {
        graph_free(g);
        return -1;
    }

    graph_free(g);
    free(aux);
    return 0;
}