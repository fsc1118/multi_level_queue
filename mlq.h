#pragma once

typedef struct {
    queue_t* queues;
    int size;
} mlq_t;

bool mlq_initialize (mlq_t * mlqueue, int size);
void mlq_release (mlq_t * mlqueue);
bool mlq_enqueue (mlq_t * mlqueue, char * item, int queue_num );
char* mlq_dequeue (mlq_t * mlqueue);
void mlq_promote (mlq_t * mlqueue);
bool mlq_empty (const mlq_t * mlqueue);