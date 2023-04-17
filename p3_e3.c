#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file_utils.h"

#define MAX_SIZE 128


/**
 * @brief Se leerán notas del fichero de
manera que la primera, tercera, quinta, etc. se insertarán por el final de una lista, mientras que
las demás (segunda, cuarta, sexta, etc.) se insertarán por el principio. Cuando se ha terminado
de insertar, el programa irá extrayendo los elementos de la lista de uno en uno: la primera mitad
desde el principio y la segunda mitad por el final. Cada vez que se extraiga una nota de la lista
(ya sea del principio o del final) se insertará en orden en otra lista de acuerdo a una función de
comparación. El orden será creciente o decreciente, según indique un argumento recibido en
línea de comandos (por terminal): 1 indicará que los elementos se han de insertar de manera
creciente en la lista y ‑1 indicará orden decreciente.
Para trabajar con los floats se pueden utilizar las funciones de la práctica anterior, especificadas
9
*/
int main(int argc, char* argv[]) {
    List *l1 = NULL, *l2 = NULL;
    FILE *f;
    float grade;
    float *e[MAX_SIZE];
    void *elem = NULL;
    int i = 0, j = 0, k = 0, order = 0, n;

    if (argc != 3) {
        fprintf(stdout, "Usage: %s <filename> <orden>\n", argv[0]);
        return -1;
    }

    /*OPEN FILE*/
    f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stdout, "ERROR: 2");
        return -1;
    }

    /*INITIALIZE L1*/
    l1 = list_new();
    if (!l1) {
        fprintf(stdout, "ERROR: 3");
        fclose(f);
        return -1;
    }

    /*INITIALIZE L2*/
    l2 = list_new();
    if (!l2) {
        fprintf(stdout, "ERROR: 3");
        fclose(f);
        list_free(l1);
        return -1;
    }

    order = atoi(argv[2]);
    if (order != 1 && order != -1) {
        fprintf(stdout, "ERROR: 4");
        fclose(f);
        list_free(l1);
        list_free(l2);
        return -1;
    }


    fscanf(f, "%d", &n);

    for(i=0; i<n; i++) {
        fscanf(f, "%f", &grade);

        e[k] = float_init(grade);
        if(!e[k]) {
            fprintf(stdout, "ERROR: 5");
            fclose(f);
            list_free(l1);
            list_free(l2);
            for(j=0; j<k; j++) {
                float_free(e[j]);
            }
            return -1;
        }

        if (i % 2 == 0) {
            if (list_pushBack(l1, e[k]) == ERROR) {
                fprintf(stdout, "ERROR: 5");
                fclose(f);
                list_free(l1);
                list_free(l2);
                for(j=0; j<k; j++) {
                    float_free(e[j]);
                }
                return -1;
            }
        } else {
            if (list_pushFront(l1, e[k]) == ERROR) {
                fprintf(stdout, "ERROR: 6");
                fclose(f);
                list_free(l1);
                list_free(l2);
                for(j=0; j<k; j++) {
                    float_free(e[j]);
                }
                return -1;
            }
        }
        k++;
    }

    if(list_print(stdout, l1, float_print) <= 0) {
        fprintf(stdout, "ERROR: 7");
        fclose(f);
        list_free(l1);
        list_free(l2);
        for(j=0; j<k; j++) {
            float_free(e[j]);
        }
        return -1;
    }
    printf("\nFinished inserting. Now we extract from the beginning and insert in order:\n");

    for(i=0; i<n/2; i++) {
        if ((elem = list_popFront(l1)) == ERROR) {
            fprintf(stdout, "ERROR: 8");
            fclose(f);
            list_free(l1);
            list_free(l2);
            for(j=0; j<k; j++) {
                float_free(e[j]);
            }
            return -1;
        }

        float_print(stdout, elem);
        printf(" ");

        if (list_pushInOrder(l2, elem, float_cmp, order) == ERROR) {
            fprintf(stdout, "ERROR: 9");
            fclose(f);
            list_free(l1);
            list_free(l2);
            for(j=0; j<k; j++) {
                float_free(e[j]);
            }
            return -1;
        }
    }

    printf("\nNow we extract from the end and insert in order:\n");

    while(list_isEmpty(l1) == FALSE) {
        if ((elem = list_popBack(l1)) == ERROR) {
            fprintf(stdout, "ERROR: 10");
            fclose(f);
            list_free(l1);
            list_free(l2);
            for(j=0; j<k; j++) {
                float_free(e[j]);
            }
            return -1;
        }

        float_print(stdout, elem);
        printf(" ");

        if (list_pushInOrder(l2, elem, float_cmp, order) == ERROR) {
            fprintf(stdout, "ERROR: 11");
            fclose(f);
            list_free(l1);
            list_free(l2);
            for(j=0; j<k; j++) {
                float_free(e[j]);
            }
            return -1;
        }
    }
    printf("\n");

    if(list_print(stdout, l2, float_print) <= 0) {
        fprintf(stdout, "ERROR: 12");
        fclose(f);
        list_free(l1);
        list_free(l2);
        for(j=0; j<k; j++) {
            float_free(e[j]);
        }
        return -1;
    }

    fclose(f);
    list_free(l1);
    list_free(l2);
    for(j=0; j<k; j++) {
        float_free(e[j]);
    }

    return 0;
}