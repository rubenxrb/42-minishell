#include <minishell.h>
#include <stdio.h>
#include <unistd.h> //getcwd
#include <limits.h>

void	print_prompt(void)
{
	char	cwd[PATH_MAX];
	//char	host[HOST_NAME_MAX];

	/*
	ft_putchar('[');

	gethostname(host, HOST_NAME_MAX);
	ft_putstr(host);

	ft_putstr("]-[");

	getcwd(cwd, PATH_MAX);
	ft_putstr(ft_strrchr(cwd, '/'));

	ft_putstr("] ");
	*/
	getcwd(cwd, PATH_MAX);
	putcstr(ft_strrchr(cwd, '/'), 93);
	ft_putchar('\n');
	putcstr(" > ", 92);
}
