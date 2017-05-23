#include <minishell.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

char		**wait_cmd(char *line, t_lst *history)
{
	char	**cmd;

	cmd = 0;
	if (get_next_line(0, &line) < 0)
	{
		ft_putendl_fd("minishell: error: reading from stdin", 2);
		exit(1);
	}
	if (line)
	{
		cmd = split_blnk(line);
		update_history(history, line);
	}
	return (cmd);
}

t_byte		exec_builtin(const char **av, t_lst *env, t_lst *history)
{
	if (!ft_strcmp(*av, "cd"))	//need - handle: cd ~, -, update $HOME call pwd
		return (ft_cd(av, env));
	else if (!ft_strcmp(*av, "clear"))
		ft_putstr("\e[1;1H\e[2J");
	else if (!ft_strcmp(*av, "exit"))
		exit(1);
	else if (!ft_strcmp(*av, "echo")) //need handle -n, -e (escape seq), -E (def)
		return (ft_echo(av, env));
	else if (!ft_strcmp(*av, "env")) //needs work - filter vars, -i/-(start new nev)
		return (ft_env(av, env, 0));
	else if (!ft_strcmp(*av, "setenv")) //needs work -0(0 instead of '\n')u
		return (ft_env(av, env, 1));
	else if (!ft_strcmp(*av, "unsetenv")) //needs -u(--unset=NAME)
		return (ft_env(av, env, -1));
	else if (!ft_strcmp(*av, "cat")) //need - !file(stdin), -n("   %d %line"), -e($)
		return (ft_cat(av));
	else if (!ft_strcmp(*av, "up")) //need - up [num]
		return (ft_up(av, env));
	else if (!ft_strcmp(*av, "history")) //needs -c(delete lst)
		return (ft_history(av, history));
	return (0);
}

/* split paths, look binaries in paths, run if found */
//get path node in lst
//split paths and search bin in paths
//fork process
//parent wait child, loop and search paths in child process
//execute binary in child, exit status for $? env
//exit child if bin not found in path
t_byte		exec_file(const char *filename, const char **av, t_lst *env)
{
	(void)filename;
	(void)av;
	(void)env;
	return 1;
}
