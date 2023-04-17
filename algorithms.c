#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"


Status mergeStacks (Stack *sin1, Stack *sin2, Stack *sout, int (*cmp)(const void *, const void *)) {
    Status st = OK;
    Stack *ps;
    void *e;

    if(!sin1 || !sin2)
        return ERROR;

    while(!stack_isEmpty(sin1) && !stack_isEmpty(sin2)) {
        if(cmp(stack_top(sin1), stack_top(sin2)) < 0)
            e = stack_pop(sin1);
        else
            e = stack_pop(sin2);

        if(!e)
            return ERROR;
        st = stack_push(sout, e);
        if(!st)
            return ERROR;
    }

    if(stack_isEmpty(sin1))
        ps = sin2;
    else
        ps = sin1;

    while(!stack_isEmpty(ps)) {
        e = stack_pop(ps);
        if(!e)
            return ERROR;
        st = stack_push(sout, e);
    }

    return st;
}   

Status graph_depthSearch (Graph *g, long from_id, long to_id) {
    int i, num_connections, num_vertices;
    int *array_positions;
    Vertex *vf = NULL, *vt = NULL;
    Vertex *v=NULL;
    Stack *s=NULL;
    Status st=OK;

    if(!g || !graph_contains(g, from_id) || !graph_contains(g, to_id))
        return ERROR;

    num_vertices = graph_getNumberOfVertices(g);

    for(i=0; i<num_vertices; i++) {
        st=vertex_setState(graph_getVertexFromIndex(g, i), WHITE); 
        if(st==ERROR) 
            return ERROR;
    }

    s=stack_init();
    if(!s)
        return ERROR;

    vf = graph_getVertexFromId(g, from_id);
    vt = graph_getVertexFromId(g, to_id);

    st=stack_push(s, vf);
    if(st==ERROR) {
        stack_free(s);
        return ERROR;
    }

    while (stack_isEmpty(s)==FALSE && st==OK){
        v = (Vertex*)stack_pop(s);
        if(!v) {
            vertex_free(v);
            stack_free(s);
            return ERROR;
        }

        if(vertex_cmp(v, vt) == 0) {
            vertex_setState(v, BLACK);
            vertex_print(stdout, v);
            fprintf(stdout, "\n");
            break;
        } 
        else {
            num_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(v));
            array_positions = graph_getConnectionsFromIndex(g, vertex_getIndex(v));
            if(array_positions == NULL) {
                fprintf(stdout, "ERROR: ARRAY POS");
                return  ERROR;
            }

            if(vertex_getState(v)==WHITE) {
                vertex_setState(v, BLACK);
                vertex_print(stdout, v);
                fprintf(stdout, "\n");

                for(i=0; i<num_connections; i++) {
                    if(vertex_getState(graph_getVertexFromIndex(g, array_positions[i]))==WHITE) {
                        st=stack_push(s, graph_getVertexFromIndex(g, array_positions[i]));
                    }
                    if(st==ERROR) {
                        vertex_free(v);
                        stack_free(s);
                        return ERROR;
                    }
                }
            }
        }

        free(array_positions);
    }
    
    stack_free(s);

    return st;
}

Status graph_breathSearch (Graph *g, long from_id, long to_id) {
    int i, num_connections, num_vertices;
    int *array_positions;
    Vertex *vf = NULL, *vt = NULL;
    Vertex *v=NULL;
    Queue *q=NULL;
    Status st=OK;

    if(!g || !graph_contains(g, from_id) || !graph_contains(g, to_id))
        return ERROR;

    num_vertices = graph_getNumberOfVertices(g);

    for(i=0; i<num_vertices; i++) {
        st=vertex_setState(graph_getVertexFromIndex(g, i), WHITE); 
        if(st==ERROR) 
            return ERROR;
    }

    q=queue_new();
    if(!q)
        return ERROR;

    vf = graph_getVertexFromId(g, from_id);
    vt = graph_getVertexFromId(g, to_id);

    st=queue_push(q, vf);
    if(st==ERROR) {
        queue_free(q);
        return ERROR;
    }

    while (queue_isEmpty(q)==FALSE && st==OK){
        v = (Vertex*)queue_pop(q);
        if(!v) {
            vertex_free(v);
            queue_free(q);
            return ERROR;
        }

        if(vertex_cmp(v, vt) == 0) {
            vertex_setState(v, BLACK);
            vertex_print(stdout, v);
            fprintf(stdout, "\n");
            break;
        } 
        else {
            num_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(v));
            array_positions = graph_getConnectionsFromIndex(g, vertex_getIndex(v));
            if(array_positions == NULL) {
                fprintf(stdout, "ERROR: ARRAY POS");
                return  ERROR;
            }

            if(vertex_getState(v)==WHITE) {
                vertex_setState(v, BLACK);
                vertex_print(stdout, v);
                fprintf(stdout, "\n");

                for(i=0; i<num_connections; i++) {
                    if(vertex_getState(graph_getVertexFromIndex(g, array_positions[i]))==WHITE) {
                        st=queue_push(q, graph_getVertexFromIndex(g, array_positions[i]));
                    }
                    if(st==ERROR) {
                        vertex_free(v);
                        queue_free(q);
                        return ERROR;
                    }
                }
            }
        }

        free(array_positions);
    }
    
    queue_free(q);

    return st;
}