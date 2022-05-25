// Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aint.h"

/*
 * query on the segment: [a, b]
 * current segment: [l, r]
 */
void *aint_query(aint *arb, int node, int a, int b, int l, int r)
{
	if (a <= l && b >= r)
		return (char *)arb->arr + node * arb->data_size;

	void *aux1 = NULL, *aux2 = NULL;
	int m = (l + r) / 2;

	if (a <= m)
		aux1 = aint_query(arb, node * 2, a, b, l, m);

	if (b >= m + 1)
		aux2 = aint_query(arb, node * 2 + 1, a, b, m + 1, r);

	if (aux1 && aux2)
		return arb->aint_merge(aux1, aux2);

	if (aux1)
		return aux1;

	return aux2;
}

/*
 * update the element at the specified position with the desired value
 * current segment: [l, r]
 */
void aint_update(aint *arb, int position, int node, void *value, int l, int r)
{
	if (l == r) {
		memcpy((char *)arb->arr + node * arb->data_size, value, arb->data_size);
	} else {
		int m = (l + r) / 2;
		if (position <= m)
			aint_update(arb, position, node * 2, value, l, m);
		else
			aint_update(arb, position, node * 2 + 1, value, m + 1, r);
		void *aux = arb->aint_merge((char *)arb->arr + node * 2 * arb->data_size,
									(char *)arb->arr + (node * 2 + 1) * arb->data_size);
		memcpy((char *)arb->arr + node * arb->data_size, aux, arb->data_size);
	}
}

/*
 * creates an aint and returns it
 */
aint *aint_init(int size, int data_size, void *value, void *(*aint_merge)(void *, void *))
{
	aint *arb = (aint *)malloc(sizeof(aint));
	arb->size = size;
	arb->data_size = data_size;
	arb->aint_merge = aint_merge;

	arb->arr = malloc(4 * size * data_size);
	for (int i = 0; i < 4 * size; ++i)
		memcpy((char *)arb->arr + i * data_size, value, data_size);

	return arb;
}


/*
 * prints the aint in a basic form
 * good for tutorial (and debugging) =)))
 */
void aint_print(aint *arb, int l, int r, int node)
{
	if (l == r) {
		printf("aint[%d, %d] = %d\n", l, r, *(int *)((char *)arb->arr + node * arb->data_size));
	} else {
		printf("aint[%d, %d] = %d\n", l, r, *(int *)((char *)arb->arr + node * arb->data_size));
		aint_print(arb, l, (l + r) / 2, 2 * node);
		aint_print(arb,  1 + (l + r) / 2, r, 2 * node + 1);
	}
}

/*
 * frees the memory of the aint
 */
void aint_free(aint **arb)
{
	free((*arb)->arr);
	free(*arb);
	*arb = NULL;
}
