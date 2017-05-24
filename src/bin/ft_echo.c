#include <builtin.h>
#include <stdio.h>

static void		trim_entry(const char *var)
{
	while (*var)
	{
		if (*var == '"')
			var++;
		else
			ft_putchar(*var++);
	}
}

static void		print_env(const char *var, t_lst *env)
{
	t_dlnode	*node;
	char		*name;

	name = (char *)var + 1;
	if (name)
	{
		if (!(node = dllst_findstr(env, name, 1)))
			return ;
		else if (node->data)
		{
			name = node->data + ft_strlen(var);
			ft_putstr(name);
		}
	}
}

static char		*convert_bslash(const char *str)
{
	char	*ptr;
	char	*ret;
	char	seq[2];
	size_t	seq_n;

	seq_n = 0;
	ptr = (char *)str;
	while (*ptr)
		if (isEscapeSeq(ptr++, 2))
			seq_n++;
	ret = ft_strnew(ft_strlen(str) - seq_n);
	ptr = ret;
	while (*str)
	{
		if (*str == 0x5c)
		{
			ft_memcpy(&seq, str, 2);
			*ptr++ = escape_seq(seq);
			str = str + 2 ? str + 2 : str + 1;
		}
		else
			*ptr++ = *str++;
	}
	return (ret);
}


static void		echo_print(const char **av, t_lst *env, t_byte n, t_byte e)
{
	t_byte	global;
	char	*tmp;
	int		i;

	i = (n + e) + 1;
	while (*(av + i))
	{
		global = *(*(av + i)) == '$' ? 1 : 0;
		if (n)
			global ? print_env(*(av + i), env) : trim_entry(*(av + i));
		else if (e)
		{
			tmp = convert_bslash(*(av + i));
			global ? print_env(*(av + i), env) : trim_entry(tmp);
			ft_strdel(&tmp);
		}
		else
			global ? print_env(*(av + i), env) : trim_entry(*(av + i));
		if (*(av + (i + 1)))
			ft_putchar(' ');
		else if (!n)
			ft_putchar('\n');
		i++;
	}
}
/*
 *	check for options in av, return if error
 *	loop resting parameters
 *	if $VAR send node to print_env();
 *	else print pararam
 */
int		ft_echo(const char **av, t_lst *env, int exit_s)
{
	t_byte		n;
	t_byte		e;

	n = 0;
	e = 0;
	if (*(av + 1))
	{
		if (!ft_strcmp(*(av + 1), "-n"))
			n = 1;
		else if (!ft_strcmp(*(av + 1), "-e"))
			e = 1;
		if (!ft_strcmp(*(av + 1), "$?"))
			ft_putnbrnl(exit_s);
		else if (!ft_strcmp(*(av + 1), "-help"))
			ft_putendl("echo [OPTION]... [STRING]...");
		else
			echo_print(av, env, n, e);

	}
	else
		ft_putchar('\n');
	return (0);
}
