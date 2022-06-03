#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct stacks{
	int *tack;
	int *tackSort;
	int *tackA;
	int *tackB;
	int size;
	int sizeA;
	int indexA;
	int sizeB;
	int indexB;
}stacks;

void init(int ac, char *av[], stacks *s);
int checkArg(char **av, stacks *s);
int putNb(char *strNb);

#endif