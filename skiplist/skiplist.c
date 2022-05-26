#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_HEIGHT 8

typedef struct node {
    int key;
    int value;
    struct node **forward;
} node;

typedef struct skiplist {
    int level;
    struct node *header;
} skiplist;

skiplist *slist_init(skiplist *list) {
    int i;
    node *header = (node *)malloc(sizeof(struct node));
    list->header = header;
    header->key = INT_MAX;
    header->forward = (node **)malloc(sizeof(node *) * MAX_HEIGHT);
    for (int i = 0; i <MAX_HEIGHT; ++i)
        header->forward[i] = list->header;
    list->level = 1;
    return list;
}

int level_rand()
{
    int l = 1;
    while (rand() < RAND_MAX >> 1 && l < MAX_HEIGHT)
        l++;
    return l;
}

int skiplist_insert(skiplist *list, int key, int value) {
    node *update[MAX_HEIGHT + 1];
    node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }
    x = x->forward[1];

    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        level = level_rand();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }

        x = (node *) malloc(sizeof(node));
        x->key = key;
        x->value = value;
        x->forward = (node **) malloc(sizeof(node*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = x;
        }
    }
    return 0;
}

node *skiplist_search(skiplist *list, int key) {
    node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
    }
    if (x->forward[1]->key == key) {
        return x->forward[1];
    } else {
        return NULL;
    }
    return NULL;
}

void skiplist_node_free(node *x) {
    if (x) {
        free(x->forward);
        free(x);
    }
}

int skiplist_delete(skiplist *list, int key) {
    int i;
    node *update[MAX_HEIGHT + 1];
    node *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->forward[i]->key < key)
            x = x->forward[i];
        update[i] = x;
    }

    x = x->forward[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x->forward[i];
        }
        skiplist_node_free(x);

        while (list->level > 1 && list->header->forward[list->level]
                == list->header)
            list->level--;
        return 0;
    }
    return 1;
}

void skiplist_free(skiplist *list)
{
    node *current_node = list->header->forward[1];
    while(current_node != list->header) {
        node *next_node = current_node->forward[1];
        free(current_node->forward);
        free(current_node);
        current_node = next_node;
    }
    free(current_node->forward);
    free(current_node);
    free(list);
}

void skiplist_dump(skiplist *list) {
    node *x = list->header;
    while (x && x->forward[1] != list->header) {
        printf("%d[%d]->", x->forward[1]->key, x->forward[1]->value);
        x = x->forward[1];
    }
    printf("NULL\n");
}

int main() {
    skiplist * list;
    list = (skiplist *)malloc(sizeof(skiplist));
    slist_init(list);
    int n;
    printf("Number of elements to insert:");
    scanf("%d", &n);
    printf("Insert:\n");
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d ", &a);
        printf("OK\n");
        skiplist_insert(list, a, a);
    }
    skiplist_dump(list);
    printf("All elements inserted.\n");
    printf("The number of keys you want to search for:\n");
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int b;
        scanf("%d ", &b);
        node *x = skiplist_search(list, b);
        if (x) {
            printf("value = %d\n", x->value);
        } else {
            printf("not found\n");
        }
    }

    skiplist_dump(list);
    skiplist_free(list);

    return 0;
}
