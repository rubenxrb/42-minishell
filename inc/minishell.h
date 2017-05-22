/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rromero <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:31:26 by rromero             #+#    #+#           */
/*   Updated: 2017/04/23 09:40:58 by rromero            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
#include <libft.h>

# define HSTRY_L 50


typedef struct prompt
{
	char	*cmd;
	char	**agv;
	t_byte	exit;
	t_lst	*env;
	t_lst	*history; /*numeric arguments required */
}			t_prompt;

/* prompt */
void		print_prompt(void);

/* cmd */
char		**wait_cmd(char *line, t_lst *history);
t_byte		exec_builtin(const char **av, t_lst *env, t_lst *history);
t_byte		exec_file(const char *filename, const char **av);

/* background */
t_lst	*make_env(char **ev);


/* utils */
t_byte		isBuiltin(const char *cmd);

#endif
