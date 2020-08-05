/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:40:48 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/08 15:40:49 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_arr(char **tabl, int j)
{
	while (j >= 0)
	{
		free(tabl[j]);
		j--;
	}
	free(tabl);
	return (NULL);
}

static int	is_charset(char myl, char c)
{
	if (myl == c)
		return (1);
	return (0);
}

static int	count_split(const char *str, char c)
{
	int i;
	int ret;

	i = 0;
	ret = 1;
	while (is_charset(str[i], c) == 1)
		i++;
	while (str[i] != '\0')
	{
		if (is_charset(str[i], c) == 1)
		{
			ret++;
			while (is_charset(str[i], c) == 1)
				i++;
		}
		else
			i++;
	}
	if (i > 0 && is_charset(str[i - 1], c) == 1)
		ret--;
	return (ret);
}

static int	count_words(const char *str, char c)
{
	int ret;

	ret = 0;
	while (is_charset(str[ret], c) == 0 && str[ret] != '\0')
		ret++;
	return (ret);
}

char		**ft_split(char const *s, char c)
{
	char	**tabl;
	int		i;
	int		j;
	int		k;

	if (!(tabl = malloc((count_split(s, c) + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_split(s, c) && s[0] != '\0' && s != NULL)
	{
		k = 0;
		while (is_charset(s[i], c) == 1)
			i++;
		if (!(tabl[j] = malloc((count_words(&s[i], c) + 1) * sizeof(char))))
			return (free_arr(tabl, j));
		while (s[i] != '\0' && is_charset(s[i], c) == 0)
			tabl[j][k++] = s[i++];
		tabl[j][k] = '\0';
		j++;
	}
	tabl[j] = NULL;
	return (tabl);
}
