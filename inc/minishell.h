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
# define FT_MINISHELL_H
# include <libft.h>
# include <builtin.h>

# define HISTORY_MAX 5
# define NOT_FOUND 127
# define NO_FILE 2


typedef struct prompt
{
	char	*cmd;
	char	**agv;
	int		exit;
	t_lst	*env;
	t_lst	*history; /*numeric arguments required */
}			t_prompt;

/* prompt */
void		print_prompt(void);

/* cmd */
char		**wait_cmd(char **line, t_lst *history);
int		exec_builtin(char **av, t_lst *env, t_lst *history, int exit_s);
int		exec_file(const char *filename, char **av, t_lst *env);

/* background */
t_lst	*make_env(char **ev);


/* utils */
t_byte		isBuiltin(const char *cmd);
void		update_history(t_lst *history, char *line);
void		not_found(const char *cmd);

#endif
