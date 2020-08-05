/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:10:12 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:10:14 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void		advance_skip_colon(int *i, const char *str)
{
	++*i;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\"')
			++*i;
		++*i;
	}
}

/*
**	used to reach the next word
*/

int				advance(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		++i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"')
			advance_skip_colon(&i, str);
		else if (str[i] == '\'')
		{
			++i;
			while (str[i] != '\'' && str[i] != '\0')
				++i;
		}
		else if (str[i] == '\\')
			++i;
		++i;
	}
	return (i);
}
