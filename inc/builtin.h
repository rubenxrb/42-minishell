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

#ifndef FT_MSHBUILTIN_H
#include <libft.h>

int		ft_cat(const char **av);
int		ft_cd(const char **av, t_lst *env);
int		ft_echo(const char **av, t_lst *env);
int		ft_env(const char **av, t_lst *env, t_byte cmd);

#endif
