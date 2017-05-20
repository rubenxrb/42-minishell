#include <stdio.h>
#include <libft.h>
#include <minishell.h>
#include <stdlib.h>
#include <sys/wait.h>

int		main(int ac, char **av, char **ev)
{
	char	*line;

	(void)av;
	(void)ev;
	(void)ac;
	line = 0;
	while (1)
	{
		printf("minishell >");
		if (!get_next_line(0, &line))
			return (0);
		if (!ft_strcmp(line, "exit"))
			exit(1);
	//	free(line);
		wait(0);
	}
}
