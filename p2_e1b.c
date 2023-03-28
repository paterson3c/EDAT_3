#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "stack.h"
#include "file_utils.h"


#define MAX_SIZE 128
#define MAX_STR 128

/**
* @brief: Merges two stacks
*
* @param sin1, first input stack
* @param sin2, second input stack
* @param sout, result stack
* @return The function returns OK or ERROR
**/
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

int main(int argc, char *argv[]) {

    Stack *s1, *s2, *s;
    FILE *f;
    char aux1[MAX_STR], aux2[MAX_STR];
    Vertex *e1[MAX_SIZE], *e2[MAX_SIZE];
    int n_elems1, n_elems2, i=0, j=0, k=0, h=0;

    if(!argv[0] || !argv[1] || !argv[2] || argv[3] != NULL)
        return -1;

/*initialize s1*/
    s1 = stack_init();
    if(!s1)
        return -1;

    f = fopen(argv[1], "r");
    if(!f) {
        stack_free(s1);
        return -1;
    }

    while(fscanf(f, "%d", &n_elems1) == 1);

    for(i=0, k=0; i < n_elems1; i++) {
        fscanf(f, "%s", aux1);
        fscanf(f, "%s", aux2);
        strcat(aux1, " ");
        strcat(aux1, aux2);

        e1[k] = vertex_initFromString(aux1);
        if(!e1[k]) {
            stack_free(s1);
            fclose(f);
            for(j=0;j<k;j++){
                vertex_free(e1[j]);
            }
            return -1;
        }

        if(!stack_push(s1, e1[k])) {
            stack_free(s1);
            fclose(f);
            for(j=0;j<k;j++){
                vertex_free(e1[j]);
            }
            return -1;
        }
        k++;
    }
    fclose(f);

/*print s1*/
    fprintf(stdout, "Ranking 0:\n");
    stack_print(stdout, s1, vertex_print);

/*initialize s2*/
    s2 = stack_init();
    if(!s2) {
        stack_free(s1);
        return -1;
    }

    f = fopen(argv[2], "r");
    if(!f) {
        stack_free(s1);
        stack_free(s2);
        return -1;
    }

    while(fscanf(f, "%d", &n_elems2) == 1);

    for(i=0, h=0; i < n_elems2; i++) {
        fscanf(f, "%s", aux1);
        fscanf(f, "%s", aux2);
        strcat(aux1, " ");
        strcat(aux1, aux2);

        e2[h] = vertex_initFromString(aux1);

        if(!e2[h]) {
            stack_free(s2);
            fclose(f);
            for(j=0;j<h;j++){
                vertex_free(e2[j]);
            }
            return -1;
        }

        if(!stack_push(s2, e2[h])) {
            stack_free(s2);
            fclose(f);
            for(j=0;j<h;j++){
                vertex_free(e2[j]);
            }
            return -1;
        }
        h++;
    }
    fclose(f);

/*print s2*/
    fprintf(stdout, "Ranking 1:\n");
    stack_print(stdout, s2, vertex_print);

/*initialize s*/
    s = stack_init();
    if(!s) {
        for(j=0;j<k;j++){
            vertex_free(e1[j]);
        }
        for(j=0;j<h;j++){
            vertex_free(e2[j]);
        }
        stack_free(s1);
        stack_free(s2);
    }

    if(!mergeStacks(s1, s2, s, vertex_cmp)) {
        for(j=0;j<k;j++){
            vertex_free(e1[j]);
        }
        for(j=0;j<h;j++){
            vertex_free(e2[j]);
        }
        stack_free(s);
        stack_free(s1);
        stack_free(s2);
    }

/*printf s*/
    fprintf(stdout, "Joint Ranking:\n");
    stack_print(stdout, s, vertex_print);

/*free allocated memory*/
    for(j=0;j<k;j++){
        vertex_free(e1[j]);
    }
    for(j=0;j<h;j++){
        vertex_free(e2[j]);
    }
    stack_free(s);
    stack_free(s1);
    stack_free(s2);

    return 0;
}