/********************Macros*********************/
#include <stdlib.h> /*malloc(), free()*/
#include <stdbool.h>
#include "queue.h"
#include <assert.h> /*assert()*/

#define IS_NULL(x) (x == NULL)

#define CHECK_MALLOC(x)\
do {\
    if (IS_NULL(x) == true) {\
        return false;\
    }\
} while(0)

#define INITIALIZE_NODE(node,content)\
do {\
    node = (node_t*)malloc(sizeof(node_t));\
    CHECK_MALLOC(new_node);\
    new_node->data = item;\
} while(0)

#define TREATMENT_WITH_QUEUE_WITH_ONE_ELEMENT(queue)\
do {\
    if (queue->head == queue->tail) {\
        char* returned_string = queue->tail->data;\
		free(queue->tail);\
        queue->tail = NULL;\
        queue->head = NULL;\
        return returned_string;\
    }\
} while (0)

/********************Macros*********************/

void queue_initialize (queue_t * queue){
    queue->head = NULL;
    queue->tail = NULL;
}

bool queue_enqueue (queue_t * queue, char * item) {
    node_t* new_node = NULL;
    INITIALIZE_NODE(new_node, item);
    if (queue_empty(queue)){
        queue->head = new_node;      
    } else {
        queue->tail->next = new_node;
    }
    queue->tail = new_node;
    return true;
}

char* queue_dequeue (queue_t * queue) {
    assert(queue_empty(queue) == false);
    TREATMENT_WITH_QUEUE_WITH_ONE_ELEMENT(queue);
    node_t* original_head = queue->head;
    char* returned_string = original_head->data;
    queue->head = original_head->next;
	free(original_head);
    return returned_string;
}

bool queue_empty (const queue_t * queue) {
    return queue->head == NULL;
}

void queue_merge (queue_t * front, queue_t * rear) {
    if (queue_empty(front) == false && queue_empty(rear) == false) {
        front->tail->next = rear->head;
        front->tail = rear->tail;
    } else if (queue_empty(front) == true && queue_empty(rear) == false) {
        front->head = rear->head;
        front->tail = rear->tail;       
    }
    /*The other two cases fallthroughs*/
    rear->head = NULL;
    rear->tail = NULL;
}

void queue_clear (queue_t * queue) {
    for (node_t* i = queue->head; i != NULL; ) {
        node_t* next = i->next;
        free(i->data);
        free(i);
        i = next;
    }
    free(queue);
    queue = NULL;
}