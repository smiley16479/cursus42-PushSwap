#include <stdio.h>
// Pour voir commment faire pour modifier une streucture passeé en param
// Bon courage si tu reprends l'exemple d'ici... 
typedef struct t_node {
	int	data;
	struct t_node *next;
}node;

typedef struct test {
	int *ptr;
	node *nod;
}test;

int func(int i, int*ptr)
{
	printf("\nDans Func\n");
	printf("&i %p, ptr %p, &ptr %p\n", &i, ptr, &ptr);
}

int func1(node nod)
{
	printf("Ds func1 nod.next->next->data %d\n", nod.next->next->data);
	nod.next = nod.next->next;
}

int func2(node* nod)
{
	printf("Ds func2 nod.next->next->data %d\n", nod->next->next->data);
	*nod/* ->next */ = *nod->next->next;
	printf("nod->data %d, nod->next->data %d\n", nod->data/*, nod->next->data, structure.nod.next->next->data */);

}

int main(int argc, char const *argv[])
{
/* 	int i = 111;
	int *ptr = &i;
	printf("&i %p, ptr %p, &ptr %p\n", &i, ptr, &ptr);
	func(i, ptr); 
	return 0;
*/
	int i = 111;
	node node2 = {2, NULL};
	node node1 = {1, &node2};
	node node0 = {0, &node1};
	test structure = {&i, &node0};
	printf("%p\n", &node2);
	// printf("node0.data %d, node1.data %d\n", structure.nod.data, *structure.nod.next); // le truc qui marche en faisant déconner le param suivant
	printf("node0.data %d, node1.data %d, node2.data %d\n", structure.nod->data, structure.nod->next->data, structure.nod->next->next->data);
	// func1(structure.nod);
	func2(structure.nod);
	printf("node0.data %d, node1.data %d, node2.data %d\n", structure.nod->data/*, structure.nod->next->data, structure.nod.next->next->data */);
	printf("%p\n", &(structure.nod));
	
}
