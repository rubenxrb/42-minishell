#include <builtin.h>

static void		putescapestr(char *str)
{
	char	*p;
	char	seq[3];

	ft_bzero(seq, 3);
	p = str;
	while (*p)
	{
		if (isEscapeSeq(p, 2))
		{
			ft_memcpy(seq, p, 2);
			ft_putchar(escape_seq(seq));
			p = p + 2 ? p + 2: p  + 1;
		}
		else
		{
			if (*p != 0x22)
				ft_putchar(*p);
			p++;
		}
	}
}

static void		echo_print(const char *av, t_lst *env, t_byte e)
{
	t_dlnode	*tmp;
	char		*quote;

	if (*av == 0x22)
		quote = ft_strsub(av, 1, ft_strlen(av) - 2);
	if ((quote && *quote == '$') || *av == '$')
	{
		tmp = dllst_findstr(env, quote + 1, 1);
		if (tmp)
			ft_putstr(ft_strchr(tmp->data, '=') + 1);
	}
	else
	{
		if (e)
			putescapestr((char *)av);
		else
			while (*av)
			{
				if ((*(av - 1) && *av != 0x22) || (*(av + 1) && *av != 0x22))
					ft_putchar(*av++);
				else
					av++;
			}
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
	size_t		i;
	t_byte		n;
	t_byte		e;

	i = 1;
	if (*(av + i))
	{
		if (!ft_strcmp(*(av + i), "-n"))
			n = 1;
		else if (!ft_strcmp(*(av + i), "-e"))
			e = 1;
		if (!ft_strcmp(*(av + i), "$?"))
			ft_putnbr(exit_s);
		else if (!ft_strcmp(*(av + i), "-help"))
			ft_putstr("echo [OPTION]... [STRING]...");
		else
			while (*(av + i + n + e))
			{
				echo_print(*(av + i + n + e), env, e);
				if (*(av + i++ + n + e))
					ft_putchar(' ');
			}
	}
	ft_putchar(!n ? '\n' : 0);
	return (0);
}
