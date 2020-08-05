/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_problem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:52:24 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:52:25 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

int			p_denied(t_env *enviro, t_pipe *pip, t_exec *ex)
{
	enviro->lsc = 126;
	--pip->founded;
	pip->pid[pip->nbr] = -1;
	++pip->nbr;
	write(2, "mash: permission denied: ", 25);
	write(2, ex->argv[0], ft_strlen(ex->argv[0]));
	write(2, "\n", 1);
	return (1);
}

int			i_directory(t_env *enviro, t_pipe *pip, t_exec *ex)
{
	enviro->lsc = 126;
	--pip->founded;
	pip->pid[pip->nbr] = -1;
	++pip->nbr;
	write(2, "mash: ", 6);
	write(2, ex->argv[0], ft_strlen(ex->argv[0]));
	write(2, ": Is a directory\n", 17);
	return (1);
}

int			d_exist(t_env *enviro, t_pipe *pip, t_exec *ex)
{
	enviro->lsc = 127;
	--pip->founded;
	pip->pid[pip->nbr] = -1;
	++pip->nbr;
	write(2, "mash: no such file or directory: ", 33);
	write(2, ex->argv[0], ft_strlen(ex->argv[0]));
	write(2, "\n", 1);
	return (1);
}
