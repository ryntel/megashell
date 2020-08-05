/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_exec_prog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:03:18 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 18:03:19 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

int			exec_prog(t_exec *ex, t_r_output redir, t_pipe *pip, int i)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (pip->total > 1 && pip->nbr != 0)
			dup2(pip->pipefd[pip->nbr - 1][0], 0);
		if (pip->total > 1 && pip->nbr + 1 < pip->total)
			dup2(pip->pipefd[pip->nbr][1], 1);
		if (redir.out != 1)
			dup2(redir.out, 1);
		if (redir.in != 0)
			dup2(redir.in, 0);
		i = pip->total - 2;
		while (i >= 0)
		{
			close(pip->pipefd[i][0]);
			close(pip->pipefd[i][1]);
			--i;
		}
		exit(execve(ex->path, ex->argv, ex->envp));
	}
	pip->pid[pip->nbr] = pid;
	++pip->nbr;
	return (pid);
}
