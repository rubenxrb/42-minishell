/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rromero <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:31:26 by rromero             #+#    #+#           */
/*   Updated: 2017/04/23 09:40:58 by rromero            ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <libft.h>

int		ft_cat(const char **av);
int 	change_dir(const char *dir, t_lst *env);
int		ft_cd(const char **av, t_lst *env);
int		ft_echo(const char **av, t_lst *env, int exit_s);
int		ft_env(const char **av, t_lst *env, char cmd);
int		ft_up(const char **av, t_lst *env);
int		ft_history(const char **av, t_lst *env);

#endif
