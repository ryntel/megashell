/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminar1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:54:41 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 18:54:42 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void		normal_case(char *line, t_pre *p_r)
{
	if ((line[p_r->i] == '\"' || line[p_r->i] == '\'') && p_r->quote == 0)
	{
		++p_r->quote;
		if (line[p_r->i] == '\"')
			p_r->q_type = '\"';
		else if (line[p_r->i] == '\'')
			p_r->q_type = '\'';
	}
	else if ((line[p_r->i] == '\"' || line[p_r->i] == '\'') && p_r->quote == 1)
	{
		--p_r->quote;
		p_r->q_type = 0;
	}
	p_r->str[p_r->k] = line[p_r->i];
	++p_r->i;
	++p_r->k;
}

void		setup_p_r(char *line, t_pre *p_r)
{
	p_r->i = 0;
	p_r->k = 0;
	p_r->quote = 0;
	p_r->q_type = 0;
	p_r->str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
}

void		fill_current_split
	(t_pre *p_r, char *envp, char *line, t_doll *dol)
{
	p_r->tmp = p_r->str;
	p_r->str = ft_strjoin(p_r->tmp, &envp[search_the_equal(envp) + 1]);
	free(p_r->tmp);
	p_r->tmp = p_r->str;
	p_r->str = ft_calloc(ft_strlen(p_r->tmp) + ft_strlen(line), sizeof(char));
	ft_strlcpy(p_r->str, p_r->tmp, ft_strlen(p_r->tmp) + 1);
	free(p_r->tmp);
	p_r->str = re_back(p_r->k, p_r->str, line, &p_r->quote);
	p_r->k = ft_strlen(p_r->str);
	p_r->i = p_r->i + dol->len;
}

void		rep_doll_str(t_env enviro, char *line, t_pre *p_r, t_doll *dol)
{
	int j;

	j = 0;
	while (enviro.envp[j] != NULL)
	{
		set_len(dol, enviro.envp[j], &line[p_r->i + 1]);
		if (ft_strncmp(&line[p_r->i + 1], enviro.envp[j], dol->len) == 0)
			fill_current_split(p_r, enviro.envp[j], line, dol);
		else if (enviro.envp[++j] == NULL && line[p_r->i + 1] == '?')
		{
			p_r->tmp2 = ft_itoa(enviro.lsc);
			p_r->tmp = p_r->str;
			p_r->str =
				ft_calloc(ft_strlen(p_r->tmp) + ft_strlen(line), sizeof(char));
			ft_strlcpy(p_r->str, p_r->tmp, ft_strlen(p_r->tmp) + 1);
			free(p_r->tmp);
			ft_strlcpy(&p_r->str[p_r->k], p_r->tmp2, ft_strlen(p_r->tmp2) + 1);
			p_r->k = p_r->k + ft_strlen(p_r->tmp2);
			p_r->i = p_r->i + 2;
			free(p_r->tmp2);
		}
		else if (enviro.envp[j] == NULL)
			p_r->i = p_r->i + find_the_end_env(&line[p_r->i + 1]) + 1;
	}
}

char		*preliminar_replacement(char *line, t_env enviro)
{
	t_doll	dol;
	t_pre	p_r;

	setup_p_r(line, &p_r);
	while (line[p_r.i] != '\0')
	{
		if (line[p_r.i] == '\\' && (line[p_r.i + 1] == '$'))
			++p_r.i;
		if ((p_r.i > 0 && line[p_r.i] == '$'
			&& line[p_r.i - 1] != '\\' && line[p_r.i + 1] !=
				' ' && p_r.q_type != '\'')
			|| (p_r.i == 0 && line[p_r.i] == '$'
			&& line[p_r.i + 1] != ' ' && p_r.q_type != '\''))
			rep_doll_str(enviro, line, &p_r, &dol);
		else
			normal_case(line, &p_r);
	}
	return (prel_ending(p_r.str));
}
