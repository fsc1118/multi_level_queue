#pragma once

typedef struct node {
    char * data;
    struct node * next;
} node_t;

typedef struct {
    node_t * head;
    node_t * tail;
} queue_t;

void queue_initialize (queue_t * queue);
bool queue_enqueue (queue_t * queue, char * item);
char* queue_dequeue (queue_t * queue);
bool queue_empty (const queue_t * queue);
void queue_merge (queue_t * front, queue_t * rear );
void queue_clear (queue_t * queue);