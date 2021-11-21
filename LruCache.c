
/*
LRU cache implementation
Vijay Dwivedi     -     2020CSB1140
Vinay Kumar       -     2020CSB1141
Yadwinder Singh   -     2020CSB1143
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INF 1000
// #define dbg printf("asdf")

FILE *in;
FILE *out;

int length_cache;
int length_cache;

struct queue_db_list
{
    char queue_data[1000];
    struct queue_db_list *prev, *next;
    // unsigned pageNumber; // the page number stored in this queue_db_list
};
typedef struct queue_db_list dbl;

struct Queue
{
    unsigned count; // Number of filled frames
    unsigned size;  // total number of frames
    dbl *front, *rear;
};
// typedef struct struct Queue;

struct hash_table
{
    char data[1000];
    struct hash_table *right;
    struct hash_table *left;
};

struct Queue *create_queue(int length_of_cache)
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->count = 0;
    queue->size = length_of_cache;
    queue->rear = queue->front = NULL;

    return queue;
}
