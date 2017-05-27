#include <builtin.h>

static char	*filter_envadd(char *entry)
{
	char	*t;
	char	*ret;
	size_t	index;

	t = 0;
	if (!(t = ft_strchr(entry, '=')))
	{
		if (!(t = ft_strchr(entry, ':')))
		{
			ft_putendl_fd("minishell: setenv: invalid format", 2);
			return (0);
		}
	}
	if (!(ret = ft_strdup(entry)))
		return (0);
	index = 0;
	while (*(entry + index) && (*(entry + index) != '=' &&
		*(entry + index) != ':'))
	{
		*(ret + index) = ft_toupper(*(entry + index));
		index++;
	}
	*(ret + index) = '=';
	return (ret);
}

static char	*filter_envdel(char *entry)
{
	char	*ret;
	size_t	index;

	index = 0;
	if (!entry)
		return (0);
	ret = ft_strdup(entry);
	while (*(entry + index) && (*(entry + index) != '=' &&
		*(entry + index) != ':'))
	{
		*(ret + index) = ft_toupper(*(entry + index));
		index++;
	}
	return (ret);
}

int		ft_env(const char **av, t_lst *env, char cmd)
{
	char		**ptr;
	char		*tmp;

	ptr = (char **)av + 1;
	if (cmd > 0)
		while (*ptr)
		{
			tmp = filter_envadd(*ptr++);
			dllst_addstr(env, tmp);
			ft_strdel(&tmp);
		}
	else if (cmd < 0)
		while (*ptr)
		{
			tmp = filter_envdel(*ptr++);
			dllst_delstr(env, tmp, 1);
			ft_strdel(&tmp);
		}
	else
		dllst_print(env, 1);
	return (0);
}
