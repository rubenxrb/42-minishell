#include <minishell.h>
#include <stdlib.h>

void	not_found(const char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exit(0);
}

t_byte	isBuiltin(const char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "clear"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "setenv"))
		return (1);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (1);
	else if (!ft_strcmp(cmd, "cat"))
		return (1);
	else if (!ft_strcmp(cmd, "up"))
		return (1);
	else if (!ft_strcmp(cmd, "history"))
		return (1);
	return (0);
}

void	update_history(t_lst *history, char *line)
{
	t_dlnode	*old;
	t_dlnode	*tmp;

	if (history->len < HISTORY_MAX)
		dllst_addstr(history, line);
	else
	{
		dllst_addstr(history, line);
		old = history->tail;
		tmp = old->prev;
		tmp->next = 0;
		history->tail = tmp;
		ft_memdel((void **)&old);
		history->len--;
	}
}
