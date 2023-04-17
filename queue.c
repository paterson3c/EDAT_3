#include "queue.h"


#define MAX_QUEUE 100

struct _Queue {
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new() {
    Queue *q;
    q = (Queue*) malloc(sizeof(Queue));
    if (!q)
        return NULL;

    for(int i = 0; i < MAX_QUEUE; i++){
        q->data[i] = NULL;
    }

    q->front = q->rear = &(q->data[0]);
    return q;
}

void queue_free(Queue *q) {
    if (q == NULL)
        return;

    free(q);
}

Bool queue_isEmpty(const Queue *q) {
    if (q == NULL)
        return TRUE;
    
    if (q->front == q->rear)
        return TRUE;
    
    return FALSE;
}

Bool _queue_isFull(Queue *q) {
    if (q == NULL)
        return TRUE;
    
    if ((q->rear + 1 - q->front) % MAX_QUEUE == 0)
        return TRUE;

    return FALSE;
}

Status queue_push(Queue *q, void *p) {
    if (q == NULL || p == NULL || _queue_isFull(q))
        return ERROR;

    *(q->rear) = (void*) p;
    q->rear = q->data + (q->rear + 1 - q->data) % MAX_QUEUE;

    return OK;
}

void *queue_pop(Queue *q) {
    void *p;

    if (q == NULL || queue_isEmpty(q))
        return NULL;

    p = *(q->front);
    *(q->front) = NULL;
    q->front = q->data + (q->front + 1 - q->data) % MAX_QUEUE;

    return p;
}

void *queue_getFront(const Queue *q) {
    if (q == NULL || queue_isEmpty(q))
        return NULL;

    return *(q->front);
}

void *queue_getBack(const Queue *q) {
    void **last_elem;

    if (q == NULL || queue_isEmpty(q))
        return NULL;
    
    if(q->rear == q->data)
        last_elem = ((Queue*)q)->data + MAX_QUEUE - 1;
    else
        last_elem = q->rear - 1;

    return *last_elem;
}

size_t queue_size(const Queue *q) {
    if (q == NULL)
    return 0;

  if (queue_isEmpty(q) == TRUE)
    return 0;

  if (q->rear == q->front)
    return MAX_QUEUE;

  return (MAX_QUEUE + q->rear - q->front) % MAX_QUEUE;
}

int queue_print(FILE *fp, Queue *q, p_queue_ele_print f) {
    int n = 0;
    void **aux;

    if (fp == NULL || q == NULL || f == NULL)
        return -1;

    aux = q->front;
    while(aux != q->rear) {
        n += f(fp, *aux);
        aux = q->data + (aux + 1 - q->data) % MAX_QUEUE;
    }

    return n;
}