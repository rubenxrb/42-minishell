#include <builtin.h>
#include <unistd.h>
#include <stdlib.h>

static void update_pwd(const char *dir, t_lst *env)
{
	(void)dir;
	(void)env;
}

static int change_dir(const char *dir, t_lst *env)
{
	int	res;

	res = chdir(dir);
	if (!res)
	{
		update_pwd(dir, env);
		return (0);
	}
	else if (res == EACCESS)
		printf("minishell: cd: %s: Permission denied\n", (char *)dir);
	else if (res == EIO)
		ft_putendl_fd("minishell: cd: File input/output error");
	else if (res == ENAMETOOLONG)
		printf("minishell: cd: %s: Filename too long\n", (char *)dir);
	else if (res == ENOTDIR)
		printf("minishell: cd: %s: Not a directory\n", (char *)dir);
	else if (res == ENOENT)
		printf("minishell: cd: %s: No such file or directory\n", (char *)dir);
	return (res);
}

static int cd_env(const char av, t_lst *env)
{
	t_dlnode	*node;
	char		*ptr;
	int			ret;

	if (av == '-')
	{
		if (!(node = dllst_findstr(env, "OLDPWD=", 1)))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set");
			return (1);
		}
	}
	else if (!av || av == '~')
	{
		if (!(node = dllst_findstr(env, "HOME=", 1)))
		{
			ft_putendl_fd("minishell: cd: HOME not set");
			return (1);
		}
	}
	ptr = node ? ft_strchr(node->data, '=') : 0;
	if (*ptr)
		ptr++;
	return (change_dir(ptr, env));
}

static int cd_agv(const char *agv, t_lst *env)
{
	(void)agv;
	(void)env;
	return 0;
}

/*
 * if tablen is > 2, return 0
 * if -, look OLDPWD path, minishell: cd: OLDPWD not set
 * if ~ or (none) look HOME path, minishell: cd: HOME not set
 * make path to changing directory, check if dir exists, permissions, if is dir
 * update PWD and OLDPWD (print working directory)
 * access(F_OK, X_OK), open(O_DIRECTORY)
 */
int		ft_cd(const char **av, t_lst *env)
{
	size_t	i;

	i = 0;
	while (*(av + i))
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if ((i == 1) || (*(*(av + 1)) == '~') || (*(*(av + 1)) == '-'))
		return (cd_env(*(*(av + 1)), env));
	return (cd_agv(*(av + 1), env));
}
