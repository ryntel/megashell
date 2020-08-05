/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:43:09 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:43:10 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

int		is_broken_pipe(char *str)
{
	int quote;
	int i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			++i;
		else if ((str[i] == '\"' || str[i] == '\'') && quote == 0)
			++quote;
		else if ((str[i] == '\"' || str[i] == '\'') && quote == 1)
			--quote;
		else if (str[i] == '|' && quote == 0
			&& is_empty_line(&str[i + 1], ' ') == 0)
			return (1);
		++i;
	}
	return (0);
}
