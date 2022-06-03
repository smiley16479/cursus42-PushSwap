// pass tab as ptr to see if I can still reach sizeof()
// Réponse : NON on peut pas
#include <stdio.h>
void ptr(int *tab)
{
	printf("func sizeof(tab) %d\n", sizeof(tab));
}

void tab_(int tab[5])
{
	printf("tab_ sizeof(tab) %d\n", sizeof(tab));
}

int main(int argc, char const *argv[])
{
	printf("%d %d\n", sizeof(size_t), sizeof(int));
	return 0;
	int tab[5];
	printf("sizeof(tab) %d\n", sizeof(tab));
	ptr(tab);
	tab_(tab);
	return 0;
}
