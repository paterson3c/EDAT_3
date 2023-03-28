#include <stdlib.h>
#include "stack.h"

#define INIT_CAPACITY 2 /*init stack capacity*/
#define FCT_CAPACITY 2  /*multyply the stack capacity*/


/*----------------------------------------------------------------------------------------------------*/
struct _Stack {
    void **item;    /*!<Static array of elements*/
    int top;        /*!<index of the top element in the stack*/
    int capacity;   /*!<xcapacity of the stack*/
};

/*----------------------------------------------------------------------------------------------------*/
Stack * stack_init () {
    Stack *s = NULL;
    s = (Stack*) malloc(sizeof(Stack));
    if(!s)
        return NULL;
    
    s->item = (void**) malloc(INIT_CAPACITY * sizeof(void*));
    if(!s->item) {
        free(s);
        s = NULL;
        return NULL;
    }

    s->capacity = INIT_CAPACITY;
    s->top = -1;

    return s;
}

/*----------------------------------------------------------------------------------------------------*/
void stack_free (Stack *s) {
    if(!s)
        return;
    free(s->item);
    free(s);

    return;
}

/*----------------------------------------------------------------------------------------------------*/
Status stack_push (Stack *s, const void *ele) {
    void **new_item = NULL;
    if(!s || !ele)
        return ERROR;
    
    if(s->capacity <= (s->top + 1)) {
        s->capacity *= FCT_CAPACITY;
        new_item = realloc( s->item, s->capacity * sizeof(void*));
        if(!new_item) {
            return ERROR;
        }

        s->item = new_item;
    }
    
    s->item[++s->top] = (void*) ele;

    return OK;
}

/*----------------------------------------------------------------------------------------------------*/
void * stack_pop (Stack *s) {
    void *ele = NULL;
    if(!s)
        return NULL;
    if(stack_isEmpty(s))
        return NULL;

    ele = s->item[s->top];
    s->item[s->top] = NULL;
    s->top--;    

    return ele;
}


/*----------------------------------------------------------------------------------------------------*/
void * stack_top (const Stack *s) {
    if(!s || stack_isEmpty(s))
        return NULL;

    if(!s->item[s->top])
        return NULL;

    return s->item[s->top];
}

/*----------------------------------------------------------------------------------------------------*/
Bool stack_isEmpty (const Stack *s) {
    if(!s)
        return TRUE;

    if(s->top == -1)
        return TRUE;
    else
        return FALSE;
}

/*----------------------------------------------------------------------------------------------------*/
size_t stack_size (const Stack *s) {
    if(!s)
        return -1;
    
    return (s->top + 1);
}

/*----------------------------------------------------------------------------------------------------*/
int stack_print(FILE* fp, const Stack *s,  P_stack_ele_print f) {
    int n = 0, i;
    if(!s || !s || !f)
        return -1;

    n += fprintf(fp, "SIZE: %d\n", (s->top + 1));

    for(i=s->top; i>=0; i--) {
        n += f(fp, s->item[i]);
        n += fprintf(fp, "\n");
    }
    
    if(n == 0)
        return -1;
    else
        return n;
}