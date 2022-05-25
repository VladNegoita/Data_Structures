// Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include "aint.h"

void *merge_int_max(void *x, void *y)
{
	if (*(int *)x > *(int *)y)
		return x;
	return y;
}

int main()
{
	int n, q;
	scanf("%d %d", &n, &q);

	int neutral_element = 0;
	aint *arb = aint_init(n, sizeof(int), &neutral_element, merge_int_max);

	int type, a, b;
	while (q--) {
		scanf("%d %d %d", &type, &a, &b);
		if (type == 0) // query on the interval [a, b]
			printf("%d\n", *(int *)aint_query(arb, 1, a, b, 1, n));
		else // update at position a => the new value is b
			aint_update(arb, a, 1, &b, 1, n);
	}

	aint_print(arb, 1, n, 1);
	aint_free(&arb);
	
	return 0;
}
