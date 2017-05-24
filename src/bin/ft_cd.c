#include <builtin.h>
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
	(void)av;
	(void)env;
	return (0);
}
