#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = {500,2500,5000,7500,10000,12500,15000,20000,30000,50000};

// each list node contains an integer key value and pointer to next list node
struct node
{
    int key;
    struct node *next;
};

// list's beginning is called the head of list
struct node *head = NULL;

struct node* list_insert(int value)
{
    struct node*create = (struct node*)malloc(sizeof(struct node));
    create->key = value;
    create->next = head;
    head = create;
    return create;
    //return NULL;
}

struct node *it;

struct node* list_search(int value)
{
    struct node*it = head;
    while((it != NULL) && (it->key != value))
    {
        it = it->next;
    }
    return it;
    //return NULL;
}

void list_delete(int value)
{
    if (head->key == value)
    {
        head = head->next;
    }
    else
    {
        struct node *prev = head;
        it = head->next;
        while (it != NULL && it->key != value)
        {
            prev = it;
            it = it->next;
        }
        if (it != NULL)
        {
            prev->next = it->next;
        }
    }
}

unsigned int list_size()
{
    int size = 0;
    struct node* it = head;
    while(it != NULL )
    {
        size += 1;
        it = it->next;
    }
    return size;
}

/*
    * Fill an array with increasing values.
    *
    * Parameters:
    *      int *t:     pointer to the array
    *      int n:      number of elements in the array
*/

void fill_increasing(int *t, int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = i;
    }
}

/*
    * Reorder array elements in a random way.
    *
    * Parameters:
    *      int *t:     pointer to the array
    *      int n:      number of elements in the array
*/

void shuffle(int *t, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

int main()
{
    bool no_yes[] = {false,true};

    for (unsigned int i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++)
    {
        bool enable_shuffle = no_yes[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++)
        {
            unsigned int n = ns[j];
            int *t = malloc(n * sizeof(*t));    // always create an array of size `n` and fill it with increasing values
            fill_increasing(t, n);
            if (enable_shuffle)  // if true, reorder array elements randomly
            {
                shuffle(t, n);
            }
            clock_t insertion_time = clock();    // insert elements in the order present in array `t`
            for (unsigned int k = 0; k < n; k++)
            {
                struct node *it = list_insert(t[k]);
                assert(it != NULL);         // inserted element cannot be NULL
                assert(it->key == t[k]);   // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;
            shuffle(t, n);  // reorder array elements before searching
            clock_t search_time = clock();  // search for every element in the order present in array `t`
            for (unsigned int k = 0; k < n; k++)
            {
                struct node *it = list_search(t[k]);
                assert(it != NULL);       // found element cannot be NULL
                assert(it->key == t[k]); // found element must contain the expected value
            }
            search_time = clock() - search_time;
            shuffle(t, n);  // reorder array elements before deletion
            for (unsigned int k = 0, l = n; k < n; k++, l--)     // delete every element in the order present in array `t`
            {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);    // after all deletions, the list size is zero
            assert(head == NULL);       // after all deletions, the list's head is NULL
            free(t);
            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    getchar();
    getchar();
    return 0;
}
