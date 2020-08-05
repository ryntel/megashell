/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:10:24 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:10:25 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void		skip_space(const char *str, int *i)
{
	while (str[*i] != '\0' && str[*i] == ' ')
		++*i;
}

static void	go_next_double_colon(int *ret, int *i, const char *str)
{
	++*ret;
	++*i;
	while (str[*i] != '\"' && str[*i] != '\0')
	{
		if (str[*i] == '\\')
			++*i;
		++*i;
	}
	if (str[*i + 1] != ' ' && str[*i + 1] != '\0')
		--*ret;
}

static void	go_next_single_colon(int *ret, int *i, const char *str)
{
	++*ret;
	++*i;
	while (str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '\\' && str[*i + 1] != '\'')
			++*i;
		++*i;
	}
	if (str[*i + 1] != ' ' && str[*i + 1] != '\0')
		--*ret;
}

static void	go_next_split(int *ret, int *i, const char *str)
{
	++*ret;
	while (str[*i] != ' ' && str[*i] != '\"'
		&& str[*i] != '\'' && str[*i] != '\0')
	{
		if (str[*i] == '\\')
			++*i;
		++*i;
	}
	if (str[*i] == '\"' || str[*i] == '\'')
		--*ret;
	--*i;
}

/*
**	return the total number of split needed (arguments)
*/

int			count_split(const char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	skip_space(str, &i);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			skip_space(str, &i);
			--i;
		}
		else if (str[i] == '\"')
			go_next_double_colon(&ret, &i, str);
		else if (str[i] == '\'')
			go_next_single_colon(&ret, &i, str);
		else
			go_next_split(&ret, &i, str);
		i++;
	}
	return (ret);
}
