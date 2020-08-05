/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:10:38 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:10:39 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void	go_next_double_colon(int *ret, int *i, const char *str)
{
	++*i;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] == '\"')
			++*i;
		++*i;
		++*ret;
	}
}

static void	go_next_single_colon(int *ret, int *i, const char *str)
{
	++*i;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		++*i;
		++*ret;
	}
}

/*
**	count the len of the word for the given split (skip the \ " ' etc)
*/

int			count_words(const char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	skip_space(str, &i);
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"')
			go_next_double_colon(&ret, &i, str);
		else if (str[i] == '\'')
			go_next_single_colon(&ret, &i, str);
		else if (str[i] == '\\')
		{
			++i;
			++ret;
		}
		else
			++ret;
		++i;
	}
	return (ret);
}
