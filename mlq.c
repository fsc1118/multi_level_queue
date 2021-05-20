/****************Macros*****************/

#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "mlq.h"

#define IS_NULL(x) (x == NULL)

#define CHECK_MALLOC(x)\
do {\
    if (IS_NULL(x) == true) {\
        return false;\
    }\
} while(0)

/****************Macros*****************/
bool mlq_initialize (mlq_t* mlqueue, int size) {
    if (size <= 0) {
        return false;
    }
    CHECK_MALLOC(mlqueue);
    mlqueue->queues = malloc(sizeof(queue_t) * size);
    CHECK_MALLOC(mlqueue->queues);
    for (int i = 0; i < size; i++) {
        queue_t* new_queue = (queue_t*)malloc(sizeof(queue_t));
        CHECK_MALLOC(new_queue);
        queue_initialize(new_queue);
        (mlqueue->queues)[i] = *new_queue;
    }
    mlqueue->size = size;
    return true;
}

void mlq_release (mlq_t* mlqueue) {
    for (int i = 0; i < mlqueue->size; i++) {
        queue_clear(&(mlqueue->queues[i]));
    }
    free(mlqueue->queues);
}

bool mlq_enqueue (mlq_t* mlqueue, char* item, int queue_num) {
    if (queue_num < 0 || queue_num >= mlqueue->size) {
        return false;
    }
    return queue_enqueue(&(mlqueue->queues)[queue_num], item);
}

bool mlq_empty (const mlq_t * mlqueue) {
    for (int i = 0; i < mlqueue->size; i++) {
        if (!queue_empty(&(mlqueue->queues[i]))) {
            return true;
        }
    }
    return false;
}

char* mlq_dequeue (mlq_t * mlqueue) {
    queue_t* queue = mlqueue->queues;
    for (int i = 0; i < mlqueue->size; i++) {
        if (queue_empty(&(queue[i])) == false) {
            return queue_dequeue(&(queue[i]));
        }
    }
    return NULL;
}

void mlq_promote (mlq_t * mlqueue) {
    for (int i = 1; i < mlqueue->size; i++) {
        queue_t* rear = &(mlqueue->queues[i]);
        queue_t* front = &(mlqueue->queues[i - 1]);
        queue_merge(front, rear);
    }
}