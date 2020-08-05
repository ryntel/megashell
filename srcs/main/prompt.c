/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:36:25 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:36:26 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void	set_color(int color, char *prompt)
{
	if (color == 0)
	{
		ft_putstr_fd("\033[0;32m", 1);
		write(1, prompt, 3);
		ft_putstr_fd("\033[0m", 1);
	}
	else
	{
		ft_putstr_fd("\033[0;31m", 1);
		write(1, prompt, 3);
		ft_putstr_fd("\033[0m", 1);
	}
}

static void	write_current_folder(int j, int i, char *str)
{
	if (j > 1)
	{
		while (str[i] != '/' && i >= 0)
			--i;
		++i;
		ft_putstr_fd("\033[1;36m", 1);
		write(1, &str[i], ft_strlen(&str[i]));
		ft_putstr_fd("\033[0m", 1);
		write(1, ": ", 2);
	}
	else
	{
		ft_putstr_fd("\033[1;31m", 1);
		write(1, str, ft_strlen(str));
		ft_putstr_fd("\033[0m", 1);
		write(1, ": ", 2);
	}
}

void		print_new_line(int lsc)
{
	char	prompt[4];
	char	*str;
	int		i;
	int		j;

	ft_strlcpy(prompt, "&> ", 4);
	set_color(lsc, prompt);
	str = getcwd(NULL, 0);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			++j;
		++i;
	}
	write_current_folder(j, i, str);
	free(str);
}
