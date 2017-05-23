#include <minishell.h>

static void run_sh(t_prompt *sh)
{
	print_prompt();
	sh->agv = wait_cmd(sh->cmd, sh->history);
	if (isBuiltin(*sh->agv))
		sh->exit = exec_builtin((const char **)sh->agv, sh->env, sh->history);
	else
		sh->exit = exec_file(*sh->agv, (const char **)sh->agv, sh->env);
	free_tab(sh->agv);
	ft_strdel(&sh->cmd);
}

static void init_sh(t_prompt *sh, char **ev)
{
	t_lst		*env;

	ft_bzero(&*sh, sizeof(t_prompt));
	env = ft_memalloc(sizeof(t_lst));
	sh->history = ft_memalloc(sizeof(t_lst));
	while (*ev)
		dllst_addstr(env, *ev++);
	sh->env = env;
}

int			main(int ac, char **av, char **ev)
{
	t_prompt	sh;

	if (ac == 1)
	{
		(void)av;
		init_sh(&sh, ev);
		while (42)
			run_sh(&sh);
	}
	else
		ft_putendl_fd("minishell: usage: ./minishell", 2);
	return (0);
}
