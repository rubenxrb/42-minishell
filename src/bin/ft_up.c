#include <builtin.h>


/*
 *	get current working dir path
 * if av > 2 return usage
 * atoi(av + 1) to get level
 * chdir to "../" that many times lol
 */
int		ft_up(const char **av, t_lst *env)
{
	size_t	i;
	int		up;
	int		ret;

	i = 0;
	ret = 0;
	while (*(av + i))
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: up: too many arguments", 2);
		return (1);
	}
	if (!*(av + 1))
		return (change_dir("../", env));
	else if (!ft_strcmp(*(av + 1), "-help"))
	{
		ft_putendl("up [NUMBER]");
		return (0);
	}
	up = ft_atoi(*(av + 1));
	while (up--)
		ret = change_dir("../", env);
	return (ret);
}
