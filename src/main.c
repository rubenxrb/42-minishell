#include <minishell.h>

static void run_sh(t_prompt *sh)
{
	print_prompt();
	sh->agv = wait_cmd(sh->cmd, sh->history);
	if (isBuiltin(*sh->agv))
		sh->exit = exec_builtin((const char **)sh->agv, sh->env, sh->history);
	else
		sh->exit = exec_file(*sh->agv, (const char **)sh->agv);
	free_tab(sh->agv);
	ft_strdel(&sh->cmd);
}

static void init_sh(t_prompt *sh, char **ev)
{
	ft_bzero(&*sh, sizeof(t_prompt));
	sh->env = make_env(ev);
	if (sh->env)
		sh->exit = 1;
}

int		main(int ac, char **av, char **ev)
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
