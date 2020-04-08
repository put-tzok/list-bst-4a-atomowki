#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = {500,2500,5000,7500,1000,12500,15000,20000,30000,50000};

struct node
{
    int key;
    struct node *next;
};

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

void fill_increasing(int *t, int n)
{
    for (int i = 0; i < n; i++)
    {
        t[i] = i;
    }
}

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
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);
            if (enable_shuffle)
            {
                shuffle(t, n);
            }
            clock_t insertion_time = clock();
            for (unsigned int k = 0; k < n; k++)
            {
                struct node *it = list_insert(t[k]);
                assert(it != NULL);
                assert(it->key == t[k]);
            }
            insertion_time = clock() - insertion_time;
            shuffle(t, n);
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++)
            {
                struct node *it = list_search(t[k]);
                assert(it != NULL);
                assert(it->key == t[k]);
            }
            search_time = clock() - search_time;
            shuffle(t, n);
            for (unsigned int k = 0, l = n; k < n; k++, l--)
            {
                assert(list_size() == l);
                list_delete(t[k]);
            }
            assert(list_size() == 0);
            assert(head == NULL);
            free(t);
            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
