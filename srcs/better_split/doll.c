/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doll.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:10:54 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:10:56 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	function used to replace the given environement variable for its value
*/

static void		*status_code
	(t_doll *dol, const char *str, t_env enviro, t_word *giv)
{
	dol->tmp2 = ft_itoa(enviro.lsc);
	dol->tmp = ft_strjoin(giv->word, dol->tmp2);
	if (!(dol->ret = malloc((ft_strlen(dol->tmp) + count_words(str) - 1))))
		return (NULL);
	ft_memset(dol->ret, 0, (ft_strlen(dol->tmp) + count_words(str) - 1));
	ft_strlcpy(dol->ret, dol->tmp, ft_strlen(dol->tmp) + 1);
	*giv->i = *giv->i + 1;
	*giv->dep = *giv->dep + ft_strlen(dol->tmp2);
	free(giv->word);
	free(dol->tmp);
	free(dol->tmp2);
	return (dol->ret);
}

static void		*check_env
	(t_doll *dol, const char *str, t_env enviro, t_word *giv)
{
	while (enviro.envp[++dol->penv] != NULL)
	{
		dol->len = search_the_equal(enviro.envp[dol->penv]);
		dol->lentest = find_the_end_env(&str[*giv->i + 1]);
		dol->len = (dol->len < dol->lentest) ? dol->lentest : dol->len;
		if (ft_strncmp(
			&str[*giv->i + 1], enviro.envp[dol->penv], dol->len) == 0)
		{
			dol->tmp = ft_strjoin(
				giv->word, &enviro.envp[dol->penv][dol->len + 1]);
			if (!(dol->ret = malloc((ft_strlen(dol->tmp) + count_words(str)
				- search_the_equal(enviro.envp[dol->penv])))))
				return (NULL);
			ft_memset(dol->ret, 0, (ft_strlen(dol->tmp) + count_words(str)
				- search_the_equal(enviro.envp[dol->penv])));
			ft_strlcpy(dol->ret, dol->tmp, ft_strlen(dol->tmp) + 1);
			*giv->i = *giv->i + dol->len;
			*giv->dep = *giv->dep
				+ ft_strlen(&enviro.envp[dol->penv][dol->len + 1]);
			free(giv->word);
			free(dol->tmp);
			return (dol->ret);
		}
	}
	return (NULL);
}

char			*fill_with_enviro(const char *str, t_env enviro, t_word *giv)
{
	t_doll	dol;
	char	*ret;

	dol.solo = is_only_doll(giv->word, str, *giv->i);
	dol.penv = -1;
	if (ft_strncmp(&str[*giv->i], "$?", 2) == 0)
		return (status_code(&dol, str, enviro, giv));
	ret = check_env(&dol, str, enviro, giv);
	if (ret != NULL)
		return (ret);
	if (dol.solo == 0)
	{
		free(giv->word);
		giv->word = NULL;
		--*giv->c_split;
	}
	*giv->i = *giv->i + find_the_end_env(&str[*giv->i + 1]);
	return (giv->word);
}
