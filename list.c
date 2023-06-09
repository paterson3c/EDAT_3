#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file_utils.h"

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

  if (pl->last == NULL) 
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


/**
 * @brief Public function that pushes an element into an ordered list.
 *
 * Inserts in its position a reference of the element received as argument.
 *
 * Note that it is necessary to traverse the list in order to obtain the
 * insert position, so this operation is linear in the number of List elements.
 *
 * @param pl Pointer to the List.
 * @param e Pointer to the element to be inserted into the List.
 * @param f A pointer to the function that must be used to compare the elements.
 * @param order Must takes a positive value for a crescent list and negative
 *  value for decrescent list.
 *
 * @return Status value OK if the insertion could be done, Status value ERROR
 * otherwise.
 */
Status list_pushInOrder (List *pl, void *e, P_ele_cmp f, int order) {
    NodeList *pn = NULL;
    NodeList *pn2 = NULL;
    int cmp = 0;
    
    if(pl == NULL || e == NULL || f == NULL || (order < 0 && order > 0))
        return ERROR;
    
    pn = node_new();
    if(pn == NULL)
        return ERROR;
    
    pn->data = (void *)e;

    if(list_isEmpty(pl) == TRUE) {
      pn->next = pn;
      pl->last = pn;
    }
    else {
      pn2 = pl->last->next;
      cmp = f(pn2->data, e);
      if((cmp > 0 && order > 0) || (cmp < 0 && order < 0)) {
        pn->next = pn2;
        pl->last->next = pn;
      }
      else if(cmp == 0) {
        pn->next = pn2->next;
        pn2->next = pn;
      }
      else {
        do {
          cmp = f(pn2->next->data, e);
          if((cmp > 0 && order > 0) || (cmp < 0 && order < 0)) {
            pn->next = pn2->next;
            pn2->next = pn;
            return OK;
          } 
          pn2 = pn2->next;
        } while(pn2->next != pl->last->next);

        cmp = f(pl->last->data, e);
        if((cmp > 0 && order == 1) || (cmp < 0 && order == -1)) {
            pn->next = pn2->next;
            pn2->next = pn;
        } else {
            pn->next = pl->last->next;
            pl->last->next = pn;
            pl->last = pn;
        }
      }
    }
    
    return OK;
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
  void *pe = NULL;
  if (pl == NULL) return;

  while (list_isEmpty(pl) == FALSE) {
    list_popFront(pl);
  }

  free(pl);
}

size_t list_size (const List *pl){
  NodeList *pn;
  int cont = 1;

  if(!pl)
   return -1;

  pn = pl->last->next;

  while( pn != pl->last) {
    cont++;
    pn = pn->next;
  }

  return cont;
}

int list_print(FILE* fp, const List *pl,  P_ele_print f){
  NodeList *pn = NULL;
  int n = 0;

  if (!fp || !pl || !f) 
    return -1;

	fprintf (fp, "SIZE: %ld \n", list_size(pl));

  if( list_isEmpty(pl)==TRUE ) 
    return -1;

  pn = pl->last->next;

  do {
    n += f (fp, pn->data);
    n+= fprintf(fp, " ");
    pn = pn->next;
  } while( pn != pl->last);

  n += f (fp, pn->data);
  n += fprintf(fp, "\n");
	return n;
}