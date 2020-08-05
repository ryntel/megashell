/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:30:43 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/17 15:27:02 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static int			absolute_path
	(t_exec *ex, t_env *enviro, t_pipe *pip, t_r_output redir)
{
	struct stat	statbuff;

	if (ex->path_exist == 0)
		free(ex->path);
	ex->path = ex->argv[0];
	if (stat(ex->argv[0], &statbuff) == 0)
	{
		if (S_ISDIR(statbuff.st_mode) == 0)
		{
			if (statbuff.st_mode & S_IXUSR)
				exec_prog(ex, redir, pip, 0);
			else
				return (p_denied(enviro, pip, ex));
		}
		else
			return (i_directory(enviro, pip, ex));
	}
	else
		return (d_exist(enviro, pip, ex));
	return (0);
}

/*
**	ca leak ici avec pathed (peut etre)
*/

static int			relative_path
	(t_exec *ex, t_env *enviro, t_r_output redir, t_pipe *pip)
{
	struct stat	statbuff;

	ex->path = ft_str_slash_join(ex->argv, ex->c_path);
	if (stat(ex->path, &statbuff) == 0 && S_ISDIR(statbuff.st_mode) == 0)
	{
		if (statbuff.st_mode & S_IXUSR)
			exec_prog(ex, redir, pip, 0);
		else
		{
			enviro->lsc = 126;
			--pip->founded;
			pip->pid[pip->nbr] = -1;
			++pip->nbr;
			write(2, "mash: permission denied: ", 25);
			write(2, ex->argv[0], ft_strlen(ex->argv[0]));
			write(2, "\n", 1);
			return (0);
		}
		free(ex->path);
		return (0);
	}
	free(ex->path);
	return (1);
}

static int			relative_notfound(t_env *enviro, t_pipe *pip, t_exec *ex)
{
	enviro->lsc = 127;
	--pip->founded;
	pip->pid[pip->nbr] = -1;
	++pip->nbr;
	write(2, "mash: command not found: ", 25);
	write(2, ex->argv[0], ft_strlen(ex->argv[0]));
	write(2, "\n", 1);
	return (1);
}

int					search_relative
	(t_exec *ex, t_env *enviro, t_r_output redir, t_pipe *pip)
{
	char	**pathed;
	int		i;
	int		ret;

	pathed = ft_split(ex->path, ':');
	i = 0;
	while (pathed[i] != NULL)
	{
		ex->c_path = pathed[i];
		ret = relative_path(ex, enviro, redir, pip);
		if (ret == 0)
		{
			free_env(pathed);
			free(pathed);
			return (ret);
		}
		++i;
	}
	free_env(pathed);
	free(pathed);
	return (1);
}

int					search_and_exec
	(char **tabl, t_env *enviro, t_r_output redir, t_pipe *pip)
{
	t_exec		ex;

	enviro->lsc = 0;
	setup_search(&ex, enviro, tabl);
	if (ft_strchr(tabl[0], '/'))
		return (absolute_path(&ex, enviro, pip, redir));
	else
	{
		if (search_relative(&ex, enviro, redir, pip) == 0)
			return (0);
	}
	if (ex.path_exist == 0)
		free(ex.path);
	relative_notfound(enviro, pip, &ex);
	return (1);
}
