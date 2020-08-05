/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 18:54:45 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 18:54:46 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

char		*inp_back(char *str, int pos, char *line)
{
	char	*tmp;
	int		i;

	i = pos;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '>'
			|| str[i] == '<' || str[i] == '|')
		{
			tmp = str;
			str = ft_calloc(ft_strlen(str) + ft_strlen(line) + 2, sizeof(char));
			ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
			free(tmp);
			tmp = ft_strdup(&str[i]);
			str[i] = '\\';
			ft_strlcpy(&str[i + 1], tmp, ft_strlen(tmp) + 1);
			free(tmp);
			++i;
		}
		++i;
	}
	return (str);
}

void		set_len(t_doll *dol, char *envp, char *line)
{
	dol->len = search_the_equal(envp);
	dol->lentest = find_the_end_env(line);
	if (dol->len < dol->lentest)
		dol->len = dol->lentest;
}

char		*re_back(int o, char *str, char *line, int *quote)
{
	int len;

	len = ft_strlen(str);
	while (o < len)
	{
		if (str[o] == '\\')
			++o;
		else if (str[o] == '\'')
			str = inp_back(str, o++, line);
		else if (str[o] == '\"')
			str = inp_back(str, o++, line);
		else if (str[o] == '>' && *quote == 0)
			str = inp_back(str, o++, line);
		else if (str[o] == '<' && *quote == 0)
			str = inp_back(str, o++, line);
		else if (str[o] == '|')
			str = inp_back(str, o++, line);
		++o;
	}
	return (str);
}

char		*prel_ending(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_calloc(ft_strlen(tmp) + 2, sizeof(char));
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (str);
}
