/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:34:19 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:34:45 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

char	**get_env_variable(char **envp, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(str, envp[i], len) == 0)
			return (&envp[i]);
		++i;
	}
	return (NULL);
}
