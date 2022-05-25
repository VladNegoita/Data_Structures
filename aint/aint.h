// Copyright 2022 311CA Vlad Negoita <vlad1negoita@gmail.com>

#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	void *arr;
	int size, data_size;
	void *(*aint_merge)(void *, void *);
} aint;

void *aint_query(aint *arb, int node, int a, int b, int l, int r);
void aint_update(aint *arb, int position, int node, void *value, int l, int r);
aint *aint_init(int size, int data_size, void *value, void *(*aint_merge)(void *, void *));
void aint_print(aint *arb, int l, int r, int node);
void aint_free(aint **arb);
