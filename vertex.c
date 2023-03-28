#include "vertex.h"
#include <string.h>


/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField (Vertex *v, char *key, char *value);

Status vertex_setField (Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr){
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p+1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

#define TAG_LENGTH 64

struct _Vertex {
  long id;
  char tag[TAG_LENGTH];
  Label state;

  int index;
};


Vertex * vertex_init() {
  Vertex *v;
  v = (Vertex*) malloc(sizeof(Vertex));

  if(v == NULL) return NULL;

  v->id = 0;
  strcpy(v->tag, "");
  v->state = 0;
  v->index = 0;

  return v;
}


void vertex_free (void * v) {
  free(v);
}


long vertex_getId (const Vertex * v) {
  if (v == NULL) return -1;
  else return v->id;
}

const char* vertex_getTag (const Vertex * v) {
if (v == NULL) return NULL;
  else return v->tag;
}


Label vertex_getState (const Vertex * v) {
if (v == NULL) return ERROR_VERTEX;
  return v->state;
}

int vertex_getIndex (const Vertex * v) {
  if (v == NULL) return -1;
  else return v->index;
}


Status vertex_setId (Vertex * v, const long id) {
  if ((id<0) || (v == NULL)) return ERROR;
  v->id = id;
  return OK;
}


Status vertex_setTag (Vertex * v, const char * tag) {
  if ((strlen(tag)>64) || (v == NULL)) return ERROR;
  strcpy(v->tag, tag);
  return OK;
}

Status vertex_setState (Vertex * v, const Label state) {
  if (v == NULL) return ERROR;
  v->state = state;
  return OK;
}

Status vertex_setIndex (Vertex * v, const int index) {
  if ((index<0) || (v == NULL)) return ERROR;
  v->index = index;
  return OK;
}


int vertex_cmp (const void * v1, const void * v2) {
  int n = 0;
  if (!v1 || !v2)
    return 0;

  if(vertex_getId(v1) != vertex_getId(v2)) {
    n = (vertex_getId(v2) - vertex_getId(v1));
  }
  else {
    n = (strcmp(vertex_getTag(v1), vertex_getTag(v2)));
  }

  return n;
}


Vertex * vertex_copy (const void * src){
  if(src == NULL) return NULL;

  Vertex *v;
  
  v = (Vertex*) malloc(sizeof(Vertex));
  if(v == NULL) return  NULL;

  vertex_setId(v, vertex_getId(src));
  vertex_setTag(v, vertex_getTag(src));
  vertex_setState(v, vertex_getState(src));
  vertex_setIndex(v, vertex_getIndex(src));

  return v;
}


int vertex_print (FILE * pf, const void * v) {
  if (!pf || v==NULL) 
    return -1;
  return fprintf(pf, "[%ld, %s, %d, %d]",vertex_getId(v),vertex_getTag(v), vertex_getState(v), vertex_getIndex(v));  
}
