#include "vertex.h"
#include <stdio.h>

int main (){
    Vertex * v1;
    v1 = vertex_init();
    if(!v1)
        return -1;

    Vertex * v2;
    v2 = vertex_init();
    if(!v2)
        return -1;

    /*inicia v1*/
    vertex_setId(v1,10);
    vertex_setTag(v1, "one");
    vertex_setState(v1, 0);
    /*inicia v2*/
    vertex_setId(v2,20);
    vertex_setTag(v2, "two");
    vertex_setState(v2, 1);

    vertex_print (stdout, v1);
    vertex_print(stdout, v2);
    fprintf(stdout, "\n");

    fprintf(stdout, "Equals? ");
    if(!vertex_cmp(v1, v2)) {
        fprintf(stdout, "Yes\n");
    }
    else {
        fprintf(stdout, "No\n");
    }

    fprintf(stdout, "Vertex 2 tag: %s\n", vertex_getTag(v2));

    Vertex * v3;
    v3 = vertex_copy(v1);
    if(!v3)
        return -1;

    fprintf(stdout, "Vertex 3 id: %ld\n", vertex_getId(v3));

    vertex_print (stdout, v1);
    vertex_print(stdout, v3);
    fprintf(stdout, "\n");

    fprintf(stdout, "Equals? ");
    if(!vertex_cmp(v1, v3)) {
        fprintf(stdout, "Yes\n");
    }
    else {
        fprintf(stdout, "No\n");
    }

    vertex_free(v1);
    vertex_free(v2);
    vertex_free(v3);

    return 0;
}