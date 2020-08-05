/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:09:19 by delacourt         #+#    #+#             */
/*   Updated: 2020/07/05 01:24:22 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void	setup_shell
	(t_env *enviro, char **envp, t_inter_read *term, int *error)
{
	int j;

	write(1, "  _______   ___  ___  _____  ___  ___________  _______  ___       \n", 67);
	write(1, " /\"      \\ |\"  \\/\"  |(\\\"   \\|\"  \\(\"     _   \")/\"     \"||\"  |      \n", 67);
	write(1, "|:        | \\   \\  / |.\\\\   \\    |)__/  \\\\__/(: ______)||  |      \n", 67);
	write(1, "|_____/   )  \\\\  \\/  |: \\.   \\\\  |   \\\\_ /    \\/    |  |:  |      \n", 67);
	write(1, " //      /   /   /   |.  \\    \\. |   |.  |    // ___)_  \\  |___   \n", 67);
	write(1, "|:  __   \\  /   /    |    \\    \\ |   \\:  |   (:      \"|( \\_|:  \\  \n", 67);
	write(1, "|__|  \\___)|___/      \\___|\\____\\)    \\__|    \\_______) \\_______) \n", 67);
	write(1, "                                                                  \n", 67);
	enviro->ctrld = 0;
	enviro->lsc = 0;
	enviro->envp = new_env(envp);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	setup_intera_mode(term);
	print_new_line(enviro->lsc);
	j = 0;
	while (j < NCMD)
	{
		enviro->histo[j] = NULL;
		++j;
	}
	*error = 0;
}

static int	get_trough_pipe
	(t_main *hub, t_pipe *pip, t_env *enviro, t_r_output *redir)
{
	while (hub->error < 3 && hub->p_tab[hub->n_pipe] != NULL)
	{
		hub->error = split_r_in_out(hub->p_tab[hub->n_pipe], redir, enviro);
		split_r_in_out_error(&hub->error, enviro, pip);
		if (hub->error == 0)
		{
			hub->error = parse_exec(redir->ret, *redir, enviro, pip);
			if (hub->error == 3)
				return (perfect_exit(redir, pip, enviro, hub) + 1);
		}
		close_redirect(redir);
		++hub->n_pipe;
	}
	return (0);
}

int			main(int argc, char **argv, char **envp)
{
	t_env			enviro;
	t_pipe			pip;
	t_main			hub;
	t_r_output		redir;
	t_inter_read	term;

	setup_shell(&enviro, envp, &term, &hub.error);
	while (1)
	{
		get_line_split_semi_colon(&term, &hub, &enviro);
		while (hub.tabl[hub.i] != NULL && hub.error != 5)
		{
			if (is_empty_line(hub.tabl[hub.i], ' ') == 1)
			{
				hub.error = setup_pipe_split(&hub, &enviro, &pip);
				if ((hub.error =
					get_trough_pipe(&hub, &pip, &enviro, &redir)) != 0)
					return (enviro.lsc);
				close_and_wait(&pip, &enviro, &hub);
			}
			++hub.i;
		}
		setup_new_input(&hub, &enviro, argc, argv);
	}
	return (0);
}
