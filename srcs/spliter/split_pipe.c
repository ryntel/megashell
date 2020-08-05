/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:43:26 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:43:27 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	will split all pipe in a tab
*/

static int		valid_pipeline
	(char *line, char ***p_tab, int *n_pipe, char ***attach)
{
	if (count_pipe(line) > 511)
	{
		if (!(*p_tab = malloc(1 * sizeof(char*))))
			return (0);
		*p_tab[0] = NULL;
		*attach = *p_tab;
		return (2);
	}
	*n_pipe = count_pipe(line) + 2;
	if (!(*p_tab = malloc(*n_pipe * sizeof(char*))))
		return (0);
	return (0);
}

int				split_pipe(char *line, char ***attach)
{
	char	**p_tab;
	int		n_pipe;
	int		i;
	int		j;

	if ((i = valid_pipeline(line, &p_tab, &n_pipe, attach)) == 2)
		return (2);
	j = 0;
	while (i + 1 < n_pipe)
	{
		if (check_redir_error(&line[j], '|') == 1)
		{
			p_tab[i] = NULL;
			*attach = p_tab;
			return (1);
		}
		p_tab[i] = ft_calloc(len_line(&line[j]) + 2, sizeof(char));
		copy_word(&line[j], p_tab[i]);
		j = j + len_line(&line[j]);
		++i;
	}
	p_tab[i] = NULL;
	*attach = p_tab;
	return (0);
}
