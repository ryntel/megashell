/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_r_in_out1_part1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:43:40 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:43:41 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	main function for the < > >> spliter will remove the character
**	and fill a structure with a fd refering to the i/o file
*/

int				split_r_in_out(char *line, t_r_output *redir, t_env *enviro)
{
	int			i;
	int			j;
	int			quotes;
	t_etup_i_o	giv;

	giv.ret = 0;
	i = 0;
	giv.i = &i;
	quotes = 0;
	giv.quotes = &quotes;
	j = 0;
	redir->out = 1;
	redir->in = 0;
	redir->ret = ft_calloc(ft_strlen(line) + 3, sizeof(char));
	while (line[i] != '\0')
	{
		giv.ret = fd_checker(line, &giv, redir, enviro);
		if (giv.ret > 0)
			return (giv.ret);
		redir->ret[j] = line[i];
		j++;
		i++;
	}
	return (0);
}
