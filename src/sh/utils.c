#include <minishell.h>

t_byte	isBuiltin(const char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
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
