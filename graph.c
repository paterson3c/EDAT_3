#include "vertex.h"
#include "graph.h"
#include <string.h>

/*--------------------------------*/
# define MAX_VTX 4096

struct _Graph {
Vertex *vertices[MAX_VTX]; /*Pointer to an array of Vertex*/
Bool connections[MAX_VTX][MAX_VTX]; /*connections[orig][dest] --> Is connected vertex with id orig to vertex with id dest?*/
int num_vertices; /*number of vertices in the graph*/
int num_edges;  /*number of connections in the graph*/
};

/*  PRIVATE FUNCTIONS   */

long get_id_from_tag(const Graph *g, char *tag) {
    int i=0, id=-1;
    if(!g)
        return -1;
    for(;i<g->num_vertices; i++) {
        if(!strcmp(tag, vertex_getTag(g->vertices[i]))) {
            id = vertex_getId(g->vertices[i]);
            break;
        }
    }
    return id;
}

Status _graph_newEdge_from_Index(Graph *g,const int orig,const int dest) {
    long id1, id2;
    if(!g || (orig < 0) || (dest < 0))
        return ERROR;
    
    id1 = vertex_getId(g->vertices[orig]);
    id2 = vertex_getId(g->vertices[dest]);
    if((id1 < 0) || (id2 < 0))
        return ERROR;
    
    return graph_newEdge(g, id1, id2);
}

int _graph_getNumConnectionsFromIndex(Graph *g, int index) {
    long id;
    if(!g || (index < 0))
        return ERROR;
    
    id = vertex_getId(g->vertices[index]);
    if(id < 0)
        return ERROR;

    return graph_getNumberOfConnectionsFromId(g, id);
}

int _graph_getIndexFromId(Graph *g, long id) {
    int i = 0;
    if(!g || graph_contains(g, id) == FALSE)
        return -1;
    
    for(i=0;i<g->num_vertices; i++) {
        if(vertex_getId(g->vertices[i]) == id)
            return i;
    }

    return -1;
}

/*  START PUBLIC FUNCTIONS  */

/*---------------------------------------------------------------------------------------------------------------------------*/
Graph * graph_init() {
    Graph *g;
    g = (Graph*) calloc(1, sizeof(Graph)); /*Initialize everything to 0*/
    if(!g)
        return NULL;
    
    return g;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
void graph_free(Graph *g) {
    int i=0;

    if(!g) 
        return;
    
    for(;i<g->num_vertices;i++) {
        vertex_free(g->vertices[i]);
    }
    free(g);
}

/*---------------------------------------------------------------------------------------------------------------------------*/
Status graph_newVertex(Graph *g, char *desc) {
    Vertex *aux;
    
    if(!g || !desc) 
        return ERROR;
    
    aux = vertex_initFromString(desc);
    if(!aux)
        return ERROR;
    
    if(graph_contains(g, vertex_getId(aux))) {
        vertex_free(aux);
        return ERROR;
    }
    vertex_setIndex(aux, g->num_vertices);
    g->vertices[g->num_vertices] = aux;
    g->num_vertices++;

    return OK;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
Status graph_newEdge(Graph *g, long orig, long dest) {
    int index_o, index_d;
    if(!g || !graph_contains(g, orig) || !graph_contains(g, dest))
        return ERROR;
    

    index_o = _graph_getIndexFromId(g, orig);
    index_d = _graph_getIndexFromId(g, dest);

    g->connections[index_o][index_d] = TRUE;
    g->num_edges++;

    return OK;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
Bool graph_contains(const Graph *g, long id) {
    int i;
    
    if(!g)
        return FALSE;
    
    for(i=0;i<g->num_vertices;i++) {
        if(vertex_getId(g->vertices[i]) == id)
            return TRUE;
    }

    return FALSE;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
int graph_getNumberOfVertices(const Graph *g) {
    if(!g)
        return -1;

    return g->num_vertices;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
int graph_getNumberOfEdges(const Graph *g){
    if(!g)
        return -1;

    return g->num_edges;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
Bool graph_connectionExists(const Graph *g, long orig, long dest){
    int index_o, index_d;
    
    if(!g)
        return FALSE;
    
    index_o = _graph_getIndexFromId((Graph*) g, orig);
    index_d = _graph_getIndexFromId((Graph*) g, dest);

    return g->connections[index_o][index_d];
}

/*---------------------------------------------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromId(const Graph *g, long id){
    int i=0, n_connection=0, index;
    
    if(!g || !graph_contains(g, id)) 
        return -1;

    index = _graph_getIndexFromId((Graph*) g, id);
    for(;i<g->num_vertices; i++) {
        if(g->connections[index][i])
            n_connection++;
    }

    return n_connection;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromId(const Graph *g, long id) {
    int i=0, j=0, n_connection, index;
    long *aux;
    
    if(!g || !graph_contains(g, id))
        return NULL;

    n_connection = graph_getNumberOfConnectionsFromId(g, id);

    aux = (long*) malloc(n_connection * sizeof(long));
    if(!aux)
        return NULL;

    index = _graph_getIndexFromId((Graph*) g, id);
    
    for(;i<g->num_vertices && j<n_connection;i++) {
        if(g->connections[index][i]) {
            aux[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }

    return aux;
}

/*---------------------------------------------------------------------------------------------------------------------------*/
int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag) {
    int id;

    if(!g || !tag)
        return -1;
    
    if((id = get_id_from_tag(g, tag)) == -1)
        return -1;

    return graph_getNumberOfConnectionsFromId(g, id);
}

/*---------------------------------------------------------------------------------------------------------------------------*/
long *graph_getConnectionsFromTag(const Graph *g, char *tag) {
    int id;

    if(!g || !tag)
        return NULL;
    
    if((id = get_id_from_tag(g, tag)) == -1)
        return NULL;
    
    return graph_getConnectionsFromId(g, id);
}

/*---------------------------------------------------------------------------------------------------------------------------*/
int graph_print (FILE *pf, const Graph *g) {
    int i=0, n_char=0, j=0;
    
    if(!pf || !g)
        return -1;

    for(i=0;i<g->num_vertices;i++) {
        n_char += vertex_print(pf ,g->vertices[i]);
        n_char += fprintf(pf, ":");
        
        for(j=0;j<g->num_vertices;j++) {
            if(graph_connectionExists(g, vertex_getId(g->vertices[i]), vertex_getId(g->vertices[j])) == TRUE) {
                n_char += fprintf(pf, " ");
                n_char += vertex_print(pf ,g->vertices[j]);
            }
        }
        fprintf(pf, "\n");
    }

    return n_char;
}


/*---------------------------------------------------------------------------------------------------------------------------*/
Status graph_readFromFile (FILE *fin, Graph *g) {
    int num_ver, i=0, orig, dest;
    char desc[MAX_STR];

    if(!g || !fin)
        return ERROR;

    while(fscanf(fin, "%d", &num_ver) == 1);

    for(;i<num_ver;i++) {
        fgets(desc, 64, fin);
        graph_newVertex(g, desc);
    }

    while(fscanf(fin, "%d %d", &orig, &dest) == 2) {
        graph_newEdge(g, orig, dest);
    }

    return OK;
}

/*-------------------------------------------------------------------------------------------------------------------------*/
Vertex *graph_getVertexFromId(Graph *g, long id) {
    int index;

    if(!g || (graph_contains(g, id) == FALSE) )
        return NULL;

    if((index = _graph_getIndexFromId(g, id)) == -1) {
        return NULL;
    }

    return g->vertices[index];
}   

/*-------------------------------------------------------------------------------------------------------------------------*/
Vertex *graph_getVertexFromIndex(Graph *g, int index) {
    if(!g || (graph_contains(g, vertex_getId(g->vertices[index])) == FALSE) )
        return NULL;

    return g->vertices[index];
}

/*-------------------------------------------------------------------------------------------------------------------------*/
int *graph_getConnectionsFromIndex(Graph *g, int index) {
    long id;
    int i, k, num_con, *indices = NULL;

    if(!g || (index < 0))
        return ERROR;
    
    id = vertex_getId(g->vertices[index]);
    if(id < 0)
        return ERROR;

    num_con = graph_getNumberOfConnectionsFromId(g, id);
    indices = (int*) malloc(num_con * sizeof(int*));
    if(!indices)
        return NULL;

    for(i=0, k=0; i<g->num_vertices && k<num_con; i++) {
        if(graph_connectionExists(g, id, vertex_getId(g->vertices[i]))) {
            indices[k] = i;
            k++;
        }
    }

    return indices;
}