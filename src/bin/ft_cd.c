#include <builtin.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

static void update_pwd(t_lst *env)
{
	t_dlnode	*opwd;
	t_dlnode	*pwd;
	char		*full;

	full = getcwd(0, 0);
	opwd = dllst_findstr(env, "OLDPWD=", 1);
	if (opwd && (pwd = dllst_findstr(env, "PWD=", 1)))
	{
		ft_strdel((char **)&opwd->data);
		opwd->data = ft_strnew(ft_strlen(pwd->data) + 7);
		ft_strcat(opwd->data, "OLDPWD=");
		ft_strcat(opwd->data, pwd->data + 4);
	}
	else if (!pwd)
		if (!(pwd = dllst_findstr(env, "PWD=", 1)))
			return ;
	ft_strdel((char **)&pwd->data);
	pwd->data = ft_strnew(ft_strlen(full) + 4);
	ft_strcat(pwd->data, "PWD=");
	ft_strcat(pwd->data + 4, full);
	ft_strdel(&full);
}

int change_dir(const char *dir, t_lst *env)
{
	int			res;

	res = chdir(dir);
	if (!res)
	{
		update_pwd(env);
		return (0);
	}
	else if (errno == EACCES)
		printf("minishell: cd: %s: Permission denied\n", (char *)dir);
	else if (errno == EIO)
		ft_putendl_fd("minishell: cd: File input/output error", 2);
	else if (errno == ENAMETOOLONG)
		printf("minishell: cd: %s: Filename too long\n", (char *)dir);
	else if (errno == ENOTDIR)
		printf("minishell: cd: %s: Not a directory\n", (char *)dir);
	else if (errno == ENOENT)
		printf("minishell: cd: %s: No such file or directory\n", (char *)dir);
	return (1);
}

static int cd_env(const char av, t_lst *env)
{
	t_dlnode	*node;
	char		*ptr;

	if (av == '-')
	{
		if (!(node = dllst_findstr(env, "OLDPWD=", 1)))
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
	}
	else if (!av || av == '~')
	{
		if (!(node = dllst_findstr(env, "HOME=", 1)))
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	ptr = node ? ft_strchr(node->data, '=') : 0;
	if (*ptr)
		ptr++;
	return (change_dir(ptr, env));
}

/*
 * if tablen is > 2, return 1
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
	return (change_dir(*(av + 1), env));
}
