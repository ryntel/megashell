/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:19:49 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/08 15:19:50 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_set(char s, const char *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

static int		trim_calc(const char *s1, const char *set)
{
	int i;
	int k;
	int ret;

	i = 0;
	ret = 0;
	k = 0;
	while (is_set(s1[i], set) == 1 && s1[i] != '\0')
		i++;
	while (s1[k] != '\0')
		k++;
	k--;
	while (k >= 0 && is_set(s1[k], set) == 1)
		k--;
	if (k - i < -1)
		return (-1);
	return (k - i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	if (!(str = malloc((trim_calc(s1, set) + 2) * sizeof(char))))
		return (NULL);
	i = 0;
	k = 0;
	while (is_set(s1[i], set) == 1 && s1[i] != '\0')
		i++;
	j = i + trim_calc(s1, set);
	while (i <= j)
	{
		str[k] = s1[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (&str[0]);
}
