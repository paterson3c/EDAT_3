/**
 * @file  delivery.c
 * @author Profesores EDAT
 * @date 10 March 2023
 * @version 1.0
 * @brief Library to manage ADT Delivery
 *
 * @details
 *
 * @see
 */

#include <string.h>
#include <stdlib.h>
#include "delivery.h"

struct _Delivery {
  char *name;
  char *product_name;
  Queue *plan;
};

Delivery *delivery_init (char *name, char *productName){
	Delivery *d;

  if ((name==NULL) || (productName==NULL)){
    return NULL;
  }

	d = (Delivery*) malloc (sizeof(Delivery));
	if (!d){
    return NULL;
  }

  d->name = (char*) calloc(strlen(name)+1, sizeof(char));
  if (d->name == NULL){
    free(d);
    return NULL;
  }
  strcpy(d->name, name);
  
  d->product_name = (char*) calloc(strlen(productName)+1, sizeof(char));
  if (d->product_name == NULL){
    free(d->name);
    free(d);
    return NULL;
  }
  strcpy(d->product_name, productName);

  d->plan = queue_new();
  if (d->plan == NULL){
    free(d->name);
    free(d->product_name);
    free(d);
    return NULL;
  }

	return d;
}

void delivery_free (void *p){
  Delivery *d;

  if (p == NULL){
    return;
  }
  
  d = (Delivery*) p;

  free(d->name);
  free(d->product_name);
  queue_free(d->plan);
  free(d);
}

void delivery_free_products (Delivery *d, p_element_free ffree) {
  if (!(d)) {
    return;
  }

  while (queue_isEmpty(d->plan) == FALSE) {
    ffree(queue_pop(d->plan));
  }

  return;
}

const char *delivery_getName (const Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->name;
}

const char *delivery_getProductName (const Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->product_name;
}

Queue *delivery_getPlan (Delivery *d){
  if (d == NULL){
    return NULL;
  }

  return d->plan;
}

Status delivery_add(FILE *pf, Delivery *d, void *p, p_element_print f){
  if(!pf || !d || !p || !f)
    return ERROR;

  if(queue_push(d->plan, p) == ERROR)
    return ERROR;
  
  fprintf(pf, "Adding: ");
  f(pf, p);
  fprintf(pf, "  to delivery: %s\n" , d->name);
  
  return OK;
}

Status delivery_run_plan(FILE *pf, Delivery *d, p_element_print fprint, p_element_free ffree){
  void *e[queue_size(d->plan)];
  int i = 0, j=0, k=0;

  if(!pf || !d || !fprint || !ffree)
    return ERROR;

  fprintf(pf, "\nRunning delivery plan for queue:\n");
  queue_print(pf, d->plan, fprint);
  
  for(i=0, j=0; queue_isEmpty(d->plan) == FALSE; i++) {
    fprintf(pf, "Delivering %s requested by %s to ", d->product_name, d->name);
    if((e[i] = queue_pop(d->plan)) == NULL) {
      for(k=0; k<j; k++) {
        ffree(e[k]);
      }
      return ERROR;
    }
    fprint(pf, e[i]);
    fprintf(pf, "\n");
    j++;
  }

  for(k=0; k<j; k++) {
    ffree(e[k]);
  }

  return OK;
}

int delivery_cmp (const void *p1, const void *p2){
  int c = 0;
  Delivery *d1, *d2;

  if ((p1 == NULL) || (p2 == NULL)){
    return c;
  }
  
  d1 = (Delivery*) p1;
  d2 = (Delivery*) p2;
  
  c = strcmp(d1->name, d2->name);
  if (c == 0){
    c = strcmp(d1->product_name, d2->product_name);
    if (c == 0){
      c = queue_size(d1->plan) - queue_size(d2->plan);
    }
  }
  
  return c;
}

void *delivery_copy (const void *src){
  Delivery *d, *trg;
  int plan_size, i;
  void *e;
  
  if (src == NULL){
    return NULL;
  }
  
  d = (Delivery*) src;
  trg = delivery_init(d->name, d->product_name);
  
  plan_size = queue_size(d->plan);
  for (i = 0; i<plan_size; i++){
    e = queue_pop(d->plan);
    queue_push(trg->plan, e);
    queue_push(d->plan, e);
  }
  
  return trg;
}

int delivery_print (FILE *pf, const void *p, p_queue_ele_print f){
  Delivery * d;
  int n=0;

  if ((pf == NULL) || (p == NULL)){
    return -1;
  }

  d = (Delivery*) p;
  n += fprintf(pf, "%s delivers %s\n", d->name, d->product_name);
  n += queue_print(pf, d->plan, f);

  return n;
}
