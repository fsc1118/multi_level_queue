/*************Macros************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mlq.h"

#ifndef MAX_LENGTH
#define MAX_LENGTH 64
#endif

#define IS_NULL(x) (x == NULL)

#define CHECK_MALLOC(x)\
do {\
    if (IS_NULL(x) == true) {\
        return false;\
    }\
} while(0)

#define INITIALIZE_MLQ(mlq)\
do {\
    mlq = malloc(sizeof(mlq_t));\
    CHECK_MALLOC(mlq);\
    if (mlq_initialize(mlq, atoi(argv[1])) == false) {\
        print_error_messages(MEMORY_FAILED);\
        return 1;\
    }\
} while (0)
/*******************************/

typedef enum {
    DEQUEUE_EMPTY_LIST,
    ENQUEUE_OUT_OF_RANGE,
    MEMORY_FAILED,
    ERROR_IN_ENQUEUE,
    UNRECOGNIZED_INPUT,
    INVALID_INPUT
} ERROR_TYPES;

typedef enum {
    ENQUEUE,
    DEQUEUE,
    PROMOTE,
    QUIT
} COMMAND;

static mlq_t* mlq = NULL;

/***************Function prototype**************/
static void check_command_argument(int argc, char *argv[]);
static void print_error_messages(ERROR_TYPES err);
static void response(COMMAND command, char* input);
static void read_line(FILE*, char* dest);
static void parse_input(char*);
/***********************************************/

int main(int argc, char *argv[]) {
    check_command_argument(argc, argv);
    INITIALIZE_MLQ(mlq);
    char input_buffer[MAX_LENGTH];
    while (1) {
        read_line(stdin, input_buffer);
        parse_input(input_buffer);
    }
    return 0;
}

static void check_command_argument(int argc, char *argv[]) {
    if (argc != 2) {
        print_error_messages(INVALID_INPUT);
        exit(1);
    }
    char* pt;
    strtol(argv[1], &pt, 10);
    if (*pt != '\0') {
        print_error_messages(INVALID_INPUT);
        exit(3);
    }
}

static void print_error_messages(ERROR_TYPES err) {
    switch (err) {
    case DEQUEUE_EMPTY_LIST:
        printf("%s\n", "ERROR: Queue empty on dequeue command");
        break;
    case ENQUEUE_OUT_OF_RANGE:
        printf("%s\n", "ERROR: Invalid queue for enqueue command");
        break;
    case MEMORY_FAILED:
        printf("%s\n", "ERROR: Out of memory");
        break;
    case ERROR_IN_ENQUEUE:
        printf("%s\n", "ERROR: Incorrect inputs for enqueue command");
        break;
    case UNRECOGNIZED_INPUT:
        printf("%s\n", "ERROR: Invalid command");
        break;
    case INVALID_INPUT:
        printf("%s\n", "ERROR: Requires number of queues");
        break;          
    }
}

static void response(COMMAND command, char* input) {
    switch (command) {
    case ENQUEUE: {
        char augument1[MAX_LENGTH];
        int augument2;
        char* argument3 = malloc(sizeof(char) * MAX_LENGTH);
        if (sscanf(input, "%s %d %s", augument1, &augument2, argument3) != 3) {
            print_error_messages(ERROR_IN_ENQUEUE);
            return;
        }
        if (!mlq_enqueue(mlq, argument3, augument2)) {
            print_error_messages(ENQUEUE_OUT_OF_RANGE);
        }
        break;
    }
    case DEQUEUE: {
        char* result = mlq_dequeue(mlq);
        if (result == NULL) {
            print_error_messages(DEQUEUE_EMPTY_LIST);
        } else {
            printf("%s\n", result);
        }
        break;
    }
    case PROMOTE:
        mlq_promote(mlq);
        break;
    case QUIT:
		mlq_release(mlq);
        exit(0);
    }
}

static void read_line(FILE* in, char* input_buffer) {
    fflush(stdin);
    int index = 0;
    for (char c = getchar(); c != '\n'; c = getchar()) {
        input_buffer[index++] = c;
    }
    input_buffer[index] = '\0';
}

static void parse_input(char* input) {
    char command[MAX_LENGTH];
    sscanf(input, "%s", command);
    if (strcmp(command, "enqueue") == 0) {
        response(ENQUEUE, input);
    } else if (strcmp(command, "dequeue") == 0) {
        response(DEQUEUE, input);
    } else if (strcmp(command, "promote") == 0) {
        response(PROMOTE, input);
    } else if (strcmp(command, "quit") == 0) {
        response(QUIT, input);
    } else {
        print_error_messages(UNRECOGNIZED_INPUT);
    }
}