/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:20:01 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/17 14:20:02 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	utils for the split pipe funtion
*/

int		fill_t_pipe(t_pipe *pip, char **p_tab)
{
	int n_pipe;

	pip->nbr = 0;
	pip->total = env_len(p_tab);
	n_pipe = 0;
	pip->total = pip->total == 0 ? 1 : pip->total;
	if (!(pip->pipefd = malloc((pip->total) * sizeof(int*))))
		return (0);
	pip->pipefd[0] = NULL;
	if (pip->total < 2)
		return (0);
	while (n_pipe + 1 < pip->total)
	{
		pip->pipefd[n_pipe] = ft_calloc(2, sizeof(int));
		pipe(pip->pipefd[n_pipe]);
		++n_pipe;
	}
	pip->pipefd[n_pipe] = NULL;
	return (0);
}

int		count_pipe(char *line)
{
	int i;
	int n_pipe;
	int quotes;
	int q_type;

	i = 0;
	quotes = 0;
	n_pipe = 0;
	q_type = 0;
	while (line[i] != '\0')
	{
		if (count_quote(&quotes, &i, line, &q_type) == 1)
			;
		else if (((i == 0 && line[i] == '|')
			|| (i > 0 && line[i] == '|'
			&& line[i - 1] != '\\')) && quotes == 0)
			++n_pipe;
		i++;
	}
	return (n_pipe);
}

int		len_line(char *line)
{
	int i;
	int l_line;
	int quotes;
	int q_type;

	i = 0;
	quotes = 0;
	l_line = 0;
	q_type = 0;
	while (line[i] != '\0')
	{
		if (count_quote(&quotes, &i, line, &q_type) == 1)
			;
		else if (((i == 0 && line[i] == '|')
			|| (i > 0 && line[i] == '|'
			&& line[i - 1] != '\\')) && quotes == 0)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

void	copy_word(char *src, char *dest)
{
	int i;
	int quotes;
	int q_type;

	i = 0;
	quotes = 0;
	q_type = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if (count_quote(&quotes, &i, src, &q_type) == 1)
			;
		else if (((i == 0 && src[i] == '|')
			|| (i > 0 && src[i] == '|'
			&& src[i - 1] != '\\')) && quotes == 0)
			break ;
		i++;
	}
	dest[i] = '\0';
}
