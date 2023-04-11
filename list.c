#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct _NodeList {
  void* data;
  struct _NodeList *next;
} NodeList;

struct _List {
  NodeList *last;
};

NodeList *node_new();
void NodeList_free(NodeList *pn);

/*-----------------*/

NodeList *node_new() {
  NodeList *pn = NULL;

  pn = (NodeList *)malloc(sizeof(NodeList));
  if (!pn) return NULL;

  pn->data = NULL;
  pn->next = NULL;
  
  return pn;
}

void NodeList_free(NodeList *pn){
  if(!pn)
   return;

  free(pn);
}

/*-----------------*/

List *list_new() {
  List *pl = NULL;

  pl = (List *)malloc(sizeof(List));
  if (pl == NULL) 
    return NULL;

  pl->last = NULL;
  
  return pl;
}

Bool list_isEmpty(const List *pl) {
  if (pl == NULL) 
    return TRUE;

  if (pl->last->next == NULL)
     return TRUE;

  return FALSE;
}

Status list_pushFront(List *pl, void *e) {
  NodeList *pn = NULL;

  if (pl == NULL || e == NULL) 
    return ERROR;

  pn = node_new();
  if (pn == NULL) 
    return ERROR;

  pn->data = (void *)e;
  
  if (list_isEmpty(pl)) {
    pn->next = pn;
    pl->last = pn;
  } 
  else {
    pn->next = pl->last->next;
    pl->last->next = pn;
  }

  return OK;
}

Status list_pushBack(List *pl, void *e) {
  NodeList *pn = NULL;
  if (pl == NULL || e == NULL)
   return ERROR;

  pn = node_new();
  if (pn == NULL) 
    return ERROR;

  pn->data = (void *)e;
  if (list_isEmpty(pl) == TRUE) {
    pn->next = pn;
    pl->last = pn;
  } 
  else {
    pn->next = pl->last->next;
    pl->last->next = pn;
    pl->last = pn;
  }

  return OK;
}

Status list_pushInOrder (List *pl, void *e, P_ele_cmp f, int order){
  NodeList *pn == NULL;
  if(pl == NULL || e == NULL || !f )
    return ERROR;

  
  
}


void *list_popFront(List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;

  if (pl == NULL || list_isEmpty(pl) == TRUE)
   return NULL;

  pn = pl->last->next;
  pe = pn->data;

  if (pl->last->next == pl->last) {
    pl->last = NULL;
  } 
  else {
    pl->last->next = pn->next;
  }

  free(pn);

  return pe;
}

void *list_popBack(List *pl) {
  NodeList *pn = NULL;
  void *pe = NULL;

  if (pl == NULL || list_isEmpty(pl) == TRUE)
   return NULL;

  if (pl->last->next == pl->last) {
    pe = pl->last->data;
    free(pl->last);
    pl->last = NULL;

    return pe;
  }

  pn = pl->last;
  while (pn->next != pl->last) {
    pn = pn->next;
  }

  pe = pl->last->data;
  pn->next = pl->last->next;
  free(pl->last);
  pl->last = pn;
  
  return pe;
}

void list_free(List *pl) {
  if (pl == NULL) return;

  while (list_isEmpty(pl) == FALSE) {
    list_popFront(pl);
  }

  free(pl);
}

size_t list_size (const List *pl){
  NodeList *pn;
/*  int cont=1;*/

  if(!pl)
   return -1;

  return (pl->last + 1);

/* Valdria con lo de arriba o habria que hacer un conteo como hago aqui
  pn = pl->last->next;

  while( pn != pl->last) {
    cont++;
    pn = pn->next;
  }

  return cont;
*/
}

int list_print(FILE* fp, const List *pl,  P_ele_print f){
  NodeList *pn = NULL;
  int n = 0;

  if (!fp || !pl || !f) 
    return -1;

	fprintf (fp, "SIZE: %d \n", list_size(pl));

  if( list_isEmpty(pl)==TRUE ) 
    return -1;

  pn = pl->last->next;

  while( pn != pl->last) {
    n += f (fp, pn->data);
    pn = pn->next;
  }

	return n;
}

