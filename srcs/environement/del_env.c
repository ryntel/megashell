/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:34:59 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:35:00 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

/*
**	locate and delete the give environement variable
*/

static char	**del_env_variable(int len, char **envp)
{
	char	**newenvp;
	int		i;
	int		j;

	if (!(newenvp = malloc((len + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] != NULL)
		{
			if (!(newenvp[j] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char))))
				return (NULL);
			ft_strlcpy(newenvp[j], envp[i], ft_strlen(envp[i]) + 1);
			free(envp[i]);
			++j;
		}
		++i;
	}
	newenvp[j] = NULL;
	free(envp);
	return (newenvp);
}

char		**unset_new(char **arg, t_env *enviro)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	enviro->lsc = 0;
	while (arg[i] != NULL)
	{
		j = 0;
		len = env_len(enviro->envp);
		while (enviro->envp[j] != NULL)
		{
			if (ft_strncmp(arg[i], enviro->envp[j], ft_strlen(arg[i])) == 0)
			{
				free(enviro->envp[j]);
				enviro->envp[j] = NULL;
			}
			++j;
		}
		if (len != env_len(enviro->envp))
			enviro->envp = del_env_variable(len, enviro->envp);
		++i;
	}
	return (enviro->envp);
}
