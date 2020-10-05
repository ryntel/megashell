/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:38:37 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:38:39 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void	close_pipe(t_pipe *pip)
{
	int	p;

	p = pip->total - 2;
	while (p >= 0)
	{
		close(pip->pipefd[p][0]);
		close(pip->pipefd[p][1]);
		free(pip->pipefd[p]);
		--p;
	}
}

static void	free_close(t_pipe *pip, t_main *hub)
{
	free(pip->pipefd);
	free_env(hub->p_tab);
	free(hub->p_tab);
	free(pip->pid);
}

void		close_and_wait(t_pipe *pip, t_env *enviro, t_main *hub)
{
	int		v;
	int		pid;

	pid = 0;
	close_pipe(pip);
	v = 0;
	while (v < pip->total)
	{
		while (pip->pid[v] == -1)
			++v;
		waitpid(pip->pid[v], &pid, 0);
		if (enviro->lsc == 0)
		{
			if (WTERMSIG(pid) == 2)
			{
				write(1, "\n", 1);
				enviro->lsc = 130;
				hub->error = 5;
			}
			else if (WTERMSIG(pid) == 3)
			{
				write(1, "Quit\n", 5);
				enviro->lsc = 131;
				hub->error = 5;
			}
			else if (hub->error == 0)
				enviro->lsc = pid / 256;
		}
		++v;
	}
	free_close(pip, hub);
}
