#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int run_cmd(char **av, t_lst *env)
{
	pid_t	pid;
	int		ret;

	ret = 1;
	pid = fork();
	(void)env;
	if (!av)
		return ret;
	if (pid == 0)
	{
		execvp(av[0], av);
	}
	wait(&pid);
	return (ret);
}

char		**wait_cmd(char *line, t_lst *history)
{
	char	**cmd;

	cmd = 0;
	if (get_next_line(0, &line) < 0)
	{
		ft_putendl_fd("minishell: error: reading from stdin", 2);
		exit(1);
	}
	cmd = split_blnk(line);
	(void)history;
	return (cmd);
}

t_byte		exec_builtin(const char **av, t_lst *env, t_lst *history)
{
	(void)av;
	(void)env;
	(void)history;
	return 0;
}

t_byte		exec_file(const char *filename, const char **av)
{
	(void)filename;
	(void)av;
	run_cmd((char **)av, 0);
	return 0;
}
