
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
struct queue_db_list *getQNode(char str[], struct queue_db_list *prev)
{
    // Create dynamic memory of QNode
    struct queue_db_list *ref = (struct queue_db_list *)malloc(sizeof(struct queue_db_list));
    if (ref == NULL)
    {
        // Failed to create memory
        return NULL;
    }
    strcpy(ref->queue_data, str);
    // ref->data = data;
    ref->next = NULL;
    ref->prev = prev;
    return ref;
}

void enqueue(struct Queue *ref, char str[])
{
    // Create a new struct Queue
    struct queue_db_list *q = getQNode(str, ref->rear);
    if (ref->front == NULL)
    {
        // When adding a first struct Queue of queue
        ref->front = q;
        ref->count = 1;
    }
    else
    {
        ref->rear->next = q;
        ref->count++;
    }
    ref->rear = q;
}

char *dequeue(struct Queue *ref)
{
    struct queue_db_list *temp = ref->front;
    if (ref->front == ref->rear)
    {
        // When queue contains only one struct Queue
        ref->rear = NULL;
        ref->front = NULL;
    }
    else
    {
        ref->front = ref->front->next;
        ref->front->prev = NULL;
    }
    // Change queue size
    ref->count--;
    return (char *)(temp->queue_data);
}

void queue_display(struct Queue *queue)
{
    struct queue_db_list *node = queue->front;
    printf("Queue Element: \n");
    while (node != NULL)
    {
        printf(" %s ", node->queue_data);
        printf("\n");
        node = node->next;
    }
    printf("\n");
    // printf(" >");
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

int main()
{
    in = freopen("input.txt", "r", stdin);
    out = freopen("output.txt", "w", stdout);
    if (in == NULL)
    {
        char wrong[100] = "Emtpy File! Nothing to Read.";
        char wrong2[100] = "Closing...";
        fputs(wrong, out);
        fputs("\n", out);
        fputs(wrong2, out);
        return 0;
    }
    else
    {
        scanf("%d", &length_cache);
        char str[INF] = "0";
        struct Queue *queue_ptr = create_queue(length_cache);
        struct hash_table *buckets[length_cache];
        for (int i = 0; i < length_cache; i++)
        {
            buckets[i] = NULL;
        }
        int count = 0;
        while (1)
        {

            scanf("%s", str);
            if (!(str[0] == '-' && str[1] == '1' && str[2] == '\0'))
            {
                count++;
                referencePage(queue_ptr, buckets, str);
                if (count == 1)
                {
                    printf("After 1st input: ");
                }
                else if (count == 2)
                {
                    printf("After 2nd input: ");
                }
                else if (count == 3)
                {
                    printf("After 3rd input: ");
                }
                else
                {
                    printf("After %dth input: ", count);
                }
                queue_display(queue_ptr);
                printf("\n");
            }
            else
            {
                break;
            }
        }
        printf("\n");
        printf("At the End, Least recently accessed element in cache is: ");
        printf("\n");
        printf("%s", queue_ptr->front->queue_data);
        printf("\n");
        printf("\n");
        printf("At the End, most recently accessed element in cache is: ");
        printf("\n");
        printf("%s", queue_ptr->rear->queue_data);
        // queue_display(queue_ptr);
        fclose(in);
        fclose(out);
        return 0;
    }
}
