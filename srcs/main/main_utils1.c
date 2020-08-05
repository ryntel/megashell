/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:52:51 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/20 16:52:52 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

int		perfect_exit(t_r_output *redir, t_pipe *pip, t_env *enviro, t_main *hub)
{
	int p;

	close_redirect(redir);
	p = pip->total - 2;
	while (p >= 0)
	{
		close(pip->pipefd[p][0]);
		close(pip->pipefd[p][1]);
		free(pip->pipefd[p]);
		--p;
	}
	free(pip->pipefd);
	free_env(hub->p_tab);
	free(hub->p_tab);
	free_env(hub->tabl);
	free(hub->tabl);
	free_env(enviro->envp);
	free(enviro->envp);
	free_env(&enviro->histo[1]);
	free(pip->pid);
	return (0);
}

void	setup_new_input(t_main *hub, t_env *enviro, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	free_env(hub->tabl);
	free(hub->tabl);
	print_new_line(enviro->lsc);
	hub->error = 0;
}

void	get_line_split_semi_colon
	(t_inter_read *term, t_main *hub, t_env *enviro)
{
	int i;

	i = 0;
	get_the_line(term, &hub->line, enviro);
	hub->tabl = split_semi_colon(hub->line);
	skip_space(hub->line, &i);
	if (hub->line[i] == ';')
	{
		hub->error = 5;
		write(2, "mash: syntax error, unexpected token ';'\n", 41);
		enviro->lsc = 2;
	}
	hub->i = 0;
}

int		setup_pipe_split(t_main *hub, t_env *enviro, t_pipe *pip)
{
	hub->error = split_pipe(hub->tabl[hub->i], &hub->p_tab);
	hub->n_pipe = 0;
	if (split_pipe_error(&hub->error, enviro, pip, hub->p_tab) == 1)
		return (5);
	return (0);
}
