#include <builtin.h>
#include <stdio.h>
/*
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
	t_byte		quote;
	t_dlnode	*node;
	char		*name;

	quote = 0;
	name = (char *)var;
	if (*name == '"')
	{
		quote = 1;
		name = ft_strsub(name, 1, ft_strlen(name) - 2);
		printf("subname: '%s'\n", name);
	}
	if (name + 1)
	{
		if (!(node = dllst_findstr(env, name + 1, 1)))
			return ;
		else if (node->data)
			ft_putstr(node->data);
	}
	if (quote)
		ft_strdel(&name);
}

 *	Make escape sequence conversion correctly, print nl if needed

static char		*convert_bslash(const char *str)
{
	char	*ptr;
	char	*ret;
	char	seq[2];
	size_t	seq_n;

	seq_n = 0;
	ptr = (char *)str;
	while (*ptr && *(ptr + 1))
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
*/

static void		echo_print(const char *av, t_lst *env, t_byte n, t_byte e)
{
	(void)av;
	(void)env;
	(void)n;
	(void)e;
}

/*
 *	check for options in av, return if error
 *	loop resting parameters
 *	if $VAR send node to print_env();
 *	else print pararam
 */
int		ft_echo(const char **av, t_lst *env, int exit_s)
{
	size_t		i;
	t_byte		n;
	t_byte		e;

	n = 0;
	e = 0;
	i = 1;
	if (*(av + i))
	{
		if (!ft_strcmp(*(av + i), "-n"))
			n = 1;
		else if (!ft_strcmp(*(av + i), "-e"))
			e = 1;
		if (!ft_strcmp(*(av + i), "$?"))
			ft_putnbrnl(exit_s);
		else if (!ft_strcmp(*(av + i), "-help"))
			ft_putendl("echo [OPTION]... [STRING]...");
		while (*(av + i))
			echo_print(*(av + i++), env, n, e);
	}
	else
		ft_putchar('\n');
	return (0);
}
