/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enhanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:11:06 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:11:07 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	quite basic ft_split but will split ' " and escape the \ etc
*/

void		*free_arr(char **tabl, int j)
{
	while (j >= 0)
	{
		free(tabl[j]);
		j--;
	}
	free(tabl);
	return (NULL);
}

void		*word_setup(const char *str, t_word *giv)
{
	if (!(giv->word = malloc(((count_words(str) + 2) * sizeof(char)))))
		return (NULL);
	ft_memset(giv->word, 0, count_words(str) + 1);
	*giv->i = 0;
	*giv->dep = 0;
	skip_space(str, giv->i);
	return (giv->word);
}

char		**ft_enhanced_split(char const *str, t_env *enviro)
{
	char	**tabl;
	char	*tmp;
	int		i;
	int		c_split;
	int		o;

	i = 0;
	o = 0;
	if (!(tabl = malloc((count_split(str) + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	c_split = 0;
	while (o < count_split(str))
	{
		tmp = fill_word(&str[i], enviro, &c_split, 0);
		if (tmp == NULL)
			tabl[c_split + 1] = tmp;
		else
			tabl[c_split] = tmp;
		c_split++;
		i = i + advance(&str[i]);
		++o;
	}
	tabl[c_split] = NULL;
	return (tabl);
}
