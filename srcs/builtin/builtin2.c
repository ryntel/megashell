/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:32:49 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:32:50 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void	dynamic_pwd(char **envp)
{
	char	**c_pwd;
	char	**o_pwd;
	char	*gc_pwd;

	if ((c_pwd = get_env_variable(envp, "PWD")) != NULL)
	{
		if ((o_pwd = get_env_variable(envp, "OLDPWD")) != NULL)
		{
			free(*o_pwd);
			*o_pwd = ft_strjoin("OLDPWD", &c_pwd[0][3]);
			free(*c_pwd);
			gc_pwd = getcwd(NULL, 0);
			*c_pwd = ft_strjoin("PWD=", gc_pwd);
			free(gc_pwd);
		}
	}
}

int		cd(char **tabl, int *lsc, char **envp)
{
	int		i;

	i = 0;
	if (tabl[0] != NULL)
		i = chdir(tabl[0]);
	*lsc = 0;
	if (i == -1)
	{
		*lsc = 1;
		write(2, "mash: cd: ", 10);
		write(2, tabl[0], ft_strlen(tabl[0]));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	dynamic_pwd(envp);
	return (1);
}
