#include <minishell.h>
#include <builtin.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


/*
	return array of paths, extracted from env node
*/
static char	**env_path(t_lst *env)
{
	char		**path;
	t_dlnode	*node;
	char		*p;

	path = 0;
	node = dllst_findstr(env, "PATH=", 1);
	p = node ? ft_strchr(node->data, '=') : 0;
	if (!node || !p)
		return (0);
	else if (*++p)
		path = ft_strsplit(p, ':');
	return (path);
}

/*
	loop through paths, create full path
	check file permissions, error and exit if no permissions
	exec if found, error if bin not found
*/
static int	lookup_path(const char *fn, char **av, char **path)
{
	char	*full;
	char	*dir;
	int		ret;
	int		i;

	ret = -1;
	if (ft_strnequ(fn, "./", 2))
	{
		full = ft_strjoin("./", fn);
		ret = execv(full, av);
		ft_strdel(&full);
	}
	else if (path)
	{
		i = 0;
		while (*(path + i))
		{
			dir = ft_strjoin(*(path + i++), "/");
			full = ft_strjoin(dir, fn);
			ret = execv(full, av);
			ft_strdel(&dir);
			ft_strdel(&full);
		}
	}
	return (ret);
}

char		**wait_cmd(char **line, t_lst *history)
{
	char	**cmd;

	cmd = 0;
	if (get_next_line(0, line) < 0)
	{
		ft_putendl_fd("minishell: error: reading from stdin", 2);
		exit(1);
	}
	if (!ft_strncmp(*line, "\n", 1))
	{
		ft_strdel(line);
		return (0);
	}
	if (*line && **line)
	{

		cmd = split_blnk(*line);
		update_history(history, *line);
	}
	return (cmd);
}

int		exec_builtin(char **av, t_lst *env, t_lst *history, int exit_s)
{
	if (!ft_strcmp(*av, "cd"))	//need - handle: cd ~, -, update $HOME call pwd
		return (ft_cd((const char **)av, env));
	else if (!ft_strcmp(*av, "clear"))
		ft_putstr("\e[1;1H\e[2J");
	else if (!ft_strcmp(*av, "exit"))
		exit(0);
	else if (!ft_strcmp(*av, "echo")) //need handle -n, -e (escape seq), -E (def)
		return (ft_echo((const char **)av, env, exit_s));
	else if (!ft_strcmp(*av, "env")) //needs work - filter vars, -i/-(start new nev)
		return (ft_env((const char **)av, env, 0));
	else if (!ft_strcmp(*av, "setenv")) //needs work -0(0 instead of '\n')u
		return (ft_env((const char **)av, env, 1));
	else if (!ft_strcmp(*av, "unsetenv")) //needs -u(--unset=NAME)
		return (ft_env((const char **)av, env, -1));
	else if (!ft_strcmp(*av, "cat")) //need - !file(stdin), -n("   %d %line"), -e($)
		return (ft_cat((const char **)av));
	else if (!ft_strcmp(*av, "up")) //need - up [num]
		return (ft_up((const char **)av, env));
	else if (!ft_strcmp(*av, "history")) //needs -c(delete lst)
		return (ft_history((const char **)av, history));
	return (0);
}

/*
	get array of strings of all paths
	fork, as parent - wait for child
	as child look up path for bin
		exit child if bin not found in path, else execute
	BONUS ($? env): save exit status, 127 if not found, -1 error, etc
*/
int		exec_file(const char *filename, char **av, t_lst *env)
{
	char	**paths;
	int		status;
	pid_t	pid;

	paths = 0;
	pid = fork();
	status = 0;
	if (pid)
		wait(&pid);
	else if (!pid)
	{
		paths = env_path(env);
		status = lookup_path(filename, av, paths);
		if (status < 0)
			not_found(filename);
	}
	if (paths)
		free_tab(paths);
	return (WEXITSTATUS(pid));
}
