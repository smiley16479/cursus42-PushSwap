#include "get_next_line.h"
#include "utils.h"
#include "stdio.h"

void freeStrs(char **strs)
{
	char **toFree;

	toFree = strs;
	if (!strs)
		return;
	while (*strs)
	{
		printf("str : %s\n", *strs);
		free(*strs);
		++strs;
	}
	free(toFree);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		++s1;
		++s2;
	}
	return ((unsigned)*s1 - (unsigned)*s2);
}

int execAction(char *action)
{
	char *a[] = {
				"", "sa", "sb" ,"ss", "pa",
				"pb","ra", "rb", "rr",
				"rra", "rrb" , "rrr", NULL
				};
	int i;

	i = -1;
	while (a[++i])
		if (!ft_strcmp(a[i], action))
			return (i);
	return (-1);
}

static inline void is_last_ptr(stacks *s)
{
	// printf("hello\n");
}

void arm_func_array(void (*func[12])(stacks *s))
{
	func[0] = is_last_ptr; // fonction pour savoir si la "" est le dernier *ptr
	func[1] = sa;
	func[2] = sb;
	func[3] = ss;
	func[4] = pa;
	func[5] = pb;
	func[6] = ra;
	func[7] = rb;
	func[8] = rr;
	func[9] = rra;
	func[10] = rrb;
	func[11] = rrr;
}


void execManip(stacks *s, char **actions)
{
	int i;
	int action;
	void (*func[12])(stacks *s);

	i = -1;
	arm_func_array(func);
	func[0](s);
	while (actions && actions[++i])
		if ((action = execAction(actions[i])) == -1)
			panicERROR();
		else
			func[action](s);
}

int main(int ac, char *av[])
{
	stacks s;
	char *action;
	char **action_S;

	action_S = NULL;
	while (get_next_line(0, &action))
		action_S = gnl_2000(action_S, action);
	free(action);
	init(--ac, ++av, &s);

	for (size_t i = 0; action_S && action_S[i]; i++)
		printf("str[%d] : %s\n", i , action_S[i]);
	execManip(&s, action_S);
	if (isSorted(s.l_A, s.sizeA, e_true))
		write(1, "OK\n", 3);
	else
		write(1, "NOT SORTED\n", 11);
	freeStrs(action_S);
	free(s.action);
	free(s.head_A);
	free(s.tackSort);
	return 0;
}
