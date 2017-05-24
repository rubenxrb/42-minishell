#include <builtin.h>
#include <stdio.h>

/* cmd = set, unset, print */
int		ft_env(const char **av, t_lst *env, char cmd)
{
	char		**ptr;

	if (cmd > 0)
	{
		ptr = (char **)av + 1;
		while (*ptr)
			dllst_addstr(env, *ptr++);
	}
	else if (cmd < 0)
	{
		ptr = (char **)av + 1;
		while (*ptr)
			dllst_delstr(env, *ptr++, 1);
	}
	else
		dllst_print(env, 1);
	return (0);
}
