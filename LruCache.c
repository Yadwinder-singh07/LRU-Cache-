
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


int value(char str[])
{
    int optimum_hashing = 0;
    int sl = strlen(str);
    for (int i = sl; i >= sl - 5 && i >= 0; i--)
    {
        optimum_hashing += (int)str[i];
    }
    return optimum_hashing;
}

void hash_insert(struct hash_table *buckets[], char str[])
{
    int t = value(str) % length_cache;
    if (buckets[t] == NULL) // If the slot is empty make an struct Queue with its data equals key.
    {
        struct hash_table *new;
        new = (struct hash_table *)malloc(sizeof(struct hash_table));
        strcpy(new->data, str);
        new->left = NULL;
        new->right = NULL;
        buckets[t] = new;
    }

    else
    { // buckets[t] is struct Queue of list
        // make a new struct Queue
        struct hash_table *new_node = (struct hash_table *)malloc(sizeof(struct hash_table));

        // update data
        strcpy(new_node->data, str);

        // Make right of new struct Queue as head and left as NULL
        new_node->right = buckets[t];
        new_node->left = NULL;

        // change left of head struct Queue to new struct Queue
        if (buckets[t] != NULL)
            buckets[t]->left = new_node;

        // move the head to point to the new struct Queue
        buckets[t] = new_node;
    }
}

int hash_search(struct hash_table *buckets[], char str[])
{
    int t = value(str) % length_cache;

    struct hash_table *temp = buckets[t]; // go to the slot where it can be found which we know from the hash function
    while (temp)                          // traverse the list and check if the element is present or not
    {
        if (!strcmp(temp->data, str))
        {
            return 1;
        }
        temp = temp->right;
    }

    if (temp == NULL)
    {
        return 0;
    }
}

void hash_delete(struct hash_table *buckets[], char str[])
{
    int t = value(str) % length_cache;
    struct hash_table *temp = buckets[t];
    while (temp)
    {
        if (!strcmp(temp->data, str))
        {
            break;
        }
        temp = temp->right;
    }

    if (temp == buckets[t]) // if the element is at head of list then move the head to its right
    {
        buckets[t] = buckets[t]->right;
        free(temp);
    }

    else if (temp->right == NULL) // if the element is at last then move the pointer to its left
    {
        temp = temp->left;
        temp->right = NULL;
    }

    else // if it is in between then make the right's left equal to left and left's right equal to right
    {
        struct hash_table *t1 = temp->right;
        struct hash_table *t2 = temp->left;
        t1->left = t2;
        t2->right = t1;
        free(temp);
    }
}




void referencePage(struct Queue *queue, struct hash_table *buckets[], char str[])
{
    struct queue_db_list *temp = queue->front;
    if (hash_search(buckets, str) == 1)
    {
        while (temp)
        {
            if (!strcmp(temp->queue_data, str))
            {
                break;
            }
            temp = temp->next;
        }

        if (!strcmp(temp->queue_data, (queue->front)->queue_data))
        {
            queue->front = temp->next;
            (temp->next)->prev = NULL;
            temp->next = NULL;
            temp->prev = queue->rear;
            (queue->rear)->next = temp;
            queue->rear = temp;
        }
        else if (!strcmp(temp->queue_data, (queue->rear)->queue_data))
        {
            temp = queue->rear;
        }
        else
        {
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            temp->next = NULL;
            temp->prev = queue->rear;
            (queue->rear)->next = temp;
            queue->rear = temp;
        }
    }

    else
    {
        hash_insert(buckets, str);
        if ((queue->count) >= (queue->size))
        {
            // printf("%s",dequeue(queue));
            hash_delete(buckets, dequeue(queue));
            enqueue(queue, str);
        }
        else
        {
            enqueue(queue, str);
        }
    }
}
