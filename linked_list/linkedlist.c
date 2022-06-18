#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "linkedlist.h"

linked_list_t* ll_create(int data_size)
{
    linked_list_t *new_list;

    new_list = (linked_list_t *) malloc(sizeof(linked_list_t));
    DIE(!new_list, "Malloc failed");

    new_list->head = NULL;
    new_list->data_size = data_size;
    new_list->size = 0;

    return new_list;
}

ll_node_t* ll_node_create(linked_list_t* list, const void* new_data)
{
    ll_node_t *new_node;

    new_node = (ll_node_t *) malloc(sizeof(ll_node_t));
    DIE(!new_node, "Malloc failed");

    new_node->next = NULL;
    new_node->data = malloc(list->data_size);
    DIE(!new_node->data, "Malloc failed");

    memcpy(new_node->data, new_data, list->data_size);

    return new_node;

}

void ll_add_nth_node(linked_list_t* list, int n, const void* new_data)
{
    ll_node_t *new_node;

    new_node = ll_node_create(list, new_data);

    if (n > list->size)
        n = list->size;

    ++list->size;

    if (n == 0) {
        new_node->next = list->head;
        list->head = new_node;
        return;
    }

    ll_node_t *aux = list->head;
    for (int i = 0; i < n - 1; ++i)
        aux = aux->next;

    new_node->next = aux->next;
    aux->next = new_node;
}

ll_node_t* ll_remove_nth_node(linked_list_t* list, int n)
{

    if (list->size == 0)
        return NULL;

    if (n > list->size - 1)
        n = list->size - 1;

    --list->size;

    if (n == 0) {
        ll_node_t *garbage = list->head;
        list->head = list->head->next;
        return garbage;
    }

    ll_node_t *aux = list->head, *garbage;
    for (int i = 0; i < n - 1; ++i)
        aux = aux->next;

    garbage = aux->next;
    aux->next = aux->next->next;

    return garbage;
}

int ll_get_size(linked_list_t* list)
{
    return list->size;
}

void free_node(ll_node_t *node)
{
    free(node->data);
    free(node);
}

void ll_free(linked_list_t** pp_list)
{
    for (int i = 0; i < (*pp_list)->size; ++i) {
        ll_node_t *garbage = (*pp_list)->head;
        (*pp_list)->head = (*pp_list)->head->next;
        free_node(garbage);
    }

    free(*pp_list);
    *pp_list = NULL;
}

void ll_print_int(linked_list_t* list)
{
    ll_node_t *aux = list->head;
    for (int i = 0; i < list->size; ++i) {
        printf("%d ", *((int *)aux->data));
        aux = aux->next;
    }
    printf("\n");
}

void ll_print_string(linked_list_t* list)
{
    ll_node_t *aux = list->head;
    for (int i = 0; i < list->size; ++i) {
        printf("%s ", (char *)aux->data);
        aux = aux->next;
    }
    printf("\n");
}
