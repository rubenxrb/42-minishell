#include <builtin.h>
#include <stdio.h>

int		ft_history(const char **av, t_lst *history)
{
	char		*var;
	size_t		num;
	t_dlnode	*node;

	num = 1;
	node = 0;
	if (*(av + 1))
	{
		if (!ft_strcmp(*(av + 1), "-c"))
		{
			dllst_del(history);
			ft_putendl("History deleted!");
		}
	}
	if (history->head)
		node = history->head;
	while (node)
	{
		var = node->data;
		printf("%5zu   %s\n", num++, var);
		node = node->next;
	}
	return (0);
}
