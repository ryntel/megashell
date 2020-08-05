/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 16:47:34 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/17 16:47:35 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	leak si le path est pas trouve
*/

int			setup_search(t_exec *ex, t_env *enviro, char **tabl)
{
	int i;

	i = 0;
	ex->envp = enviro->envp;
	ex->argv = tabl;
	ex->path_exist = 1;
	while (enviro->envp[i] != NULL)
	{
		if (ft_strncmp(enviro->envp[i], "PATH=", 5) == 0)
		{
			ex->path = &enviro->envp[i][5];
			return (0);
		}
		++i;
	}
	if (enviro->envp[i] == NULL)
	{
		ex->path_exist = 0;
		if (!(ex->path = malloc(1 * sizeof(char))))
			return (0);
		ex->path[0] = '\0';
	}
	return (0);
}

char		*ft_str_slash_join(char **tabl, char *pathed)
{
	int		j;
	int		k;
	char	*try;

	if (!(try = malloc(ft_strlen(tabl[0]) + ft_strlen(pathed) + 2)))
		return (NULL);
	j = 0;
	k = 0;
	while (pathed[j] != '\0')
	{
		try[k] = pathed[j];
		++k;
		++j;
	}
	try[k] = '/';
	++k;
	j = 0;
	while (tabl[0][j] != '\0')
	{
		try[k] = tabl[0][j];
		++k;
		++j;
	}
	try[k] = '\0';
	return (try);
}
