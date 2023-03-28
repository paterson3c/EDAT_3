#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vertex.h"
#include "types.h"
#include "queue.h"
#include "delivery.h"

#define MAX_STR 128

/**
* @brief Builds a delivery from the information read on the file.
*
* @param pf File descriptor. The file should contains the following
information:
* Firt line: delivery_name product_name
* Second line: number of cities/vertices
* Following lines: vertices description
*
* @return A pointer to the fullfilled delivery. If there have been
errors returns NULL.
*/
Delivery* build_delivery(FILE * pf){
    Delivery *d;
    char name[MAX_STR + 1], product_name[MAX_STR + 1];
    int n, i;
    char desc1[MAX_STR + 1], desc2[MAX_STR + 1];
    Vertex *v;

    if(!pf)
        return NULL;

    if(fscanf(pf, "%s %s", name, product_name) != 2)
        return NULL;

    d = delivery_init(name, product_name);
    if(!d)
        return NULL;

    if(fscanf(pf, "%d", &n) != 1) {
        delivery_free((void*)d);
        return NULL;
    }

    for(i = 0; i < n; i++) {
        fscanf(pf, "%s", desc1);
        fscanf(pf, "%s", desc2);
        strcat(desc1, " ");
        strcat(desc1, desc2);


        if((v = vertex_initFromString(desc1)) == NULL) {
            delivery_free((void*)d);
            return NULL;
        }

        if(delivery_add(stdout, d, (void*)v, (p_element_print)vertex_print) == ERROR) {
            delivery_free((void*)d);
            return NULL;
        }
    }

    return d;

}


int main(int argc, char *argv[]){
    Delivery *d;
    FILE *f;


    if(!argv[0] || !argv[1] || argv[2] != NULL)
        return -1;

    f = fopen(argv[1], "r");
    if(!f) 
        return -1;

    d = build_delivery(f);
    if(!d){
        delivery_free((void*)d);
        fclose(f);
        return -1;
    }
    fclose(f);

    if(delivery_run_plan(stdout, d, (p_element_print)vertex_print, (p_element_free)vertex_free) == ERROR){
        delivery_free((void*)d);
        return -1;
    }
    
    delivery_free((void*)d);
    
    return 0;
}