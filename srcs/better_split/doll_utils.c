/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:10:49 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:10:50 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static size_t	ft_itoa_len(int n)
{
	size_t	r;

	if (n == 0)
		return (1);
	r = 0;
	if (n < 0)
		r++;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char			*ft_itoa(int n)
{
	size_t	l;
	size_t	e;
	char	*r;

	l = ft_itoa_len(n);
	if (!(r = (char *)malloc(l + 1)))
		return (NULL);
	r[l] = '\0';
	if (n < 0)
	{
		r[0] = '-';
		e = 1;
	}
	else
		e = 0;
	while (l-- > e)
	{
		r[l] = '0' + n % 10 * (n < 0 ? -1 : 1);
		n /= 10;
	}
	return (r);
}

int				find_the_end_env(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\\' && str[i] != ' '
		&& str[i] != '$' && str[i] != '\''
		&& str[i] != '\"' && str[i] != ':' && str[i] != '=')
		++i;
	return (i);
}

int				is_only_doll(char *word, const char *str, int i)
{
	int j;
	int end;

	j = 0;
	end = find_the_end_env(&str[i + 1]);
	if (ft_strlen(word) == 0
		&& (str[i + end + 1] == 0 || str[i + end + 1] == ' '))
		return (0);
	return (1);
}
