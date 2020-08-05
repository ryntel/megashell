/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:28:07 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:28:09 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	setup the arrow key
*/

void	fill_key(t_key *key)
{
	key->g[0] = 27;
	key->g[1] = 91;
	key->g[2] = 68;
	key->g[3] = 0;
	key->d[0] = 27;
	key->d[1] = 91;
	key->d[2] = 67;
	key->d[3] = 0;
	key->h[0] = 27;
	key->h[1] = 91;
	key->h[2] = 65;
	key->h[3] = 0;
	key->b[0] = 27;
	key->b[1] = 91;
	key->b[2] = 66;
	key->b[3] = 0;
	key->home[0] = 27;
	key->home[1] = 91;
	key->home[2] = 72;
	key->home[3] = 0;
	key->end[0] = 27;
	key->end[1] = 91;
	key->end[2] = 70;
	key->end[3] = 0;
}

/*
**	put the given line in the historic
*/

void	put_in_histo(t_env *enviro, char *tst)
{
	int		i;

	i = NCMD - 2;
	enviro->histo[0] = tst;
	while (i >= 0)
	{
		enviro->histo[i + 1] = enviro->histo[i];
		--i;
	}
	if (enviro->histo[NCMD - 1] != NULL)
	{
		free(enviro->histo[NCMD - 1]);
		enviro->histo[NCMD - 1] = NULL;
	}
}

/*
**	put the given caracter at the right place in the string
*/

void	put_char_in_str(char *tst, int len, char c)
{
	char	*tmp;

	tmp = ft_strdup(&tst[len]);
	tst[len] = c;
	ft_strlcpy(&tst[len + 1], tmp, ft_strlen(tmp) + 1);
	free(tmp);
}
