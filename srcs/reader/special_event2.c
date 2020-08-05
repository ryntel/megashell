/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_event2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:28:24 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:28:25 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

int		k_enter(t_env *enviro, char **line, t_read *t_r)
{
	if (is_broken_quote(t_r->tst) == 1)
	{
		t_r->brok = 'q';
		return (ft_strlen(t_r->tst));
	}
	else if (is_broken_pipe(t_r->tst) == 1
		|| (ft_strlen(t_r->tst) > 0
		&& t_r->tst[ft_strlen(t_r->tst) - 1] == '\\'))
	{
		t_r->brok = 'p';
		if (ft_strlen(t_r->tst) > 0
			&& t_r->tst[ft_strlen(t_r->tst) - 1] == '\\')
			t_r->brok = 'b';
		return (ft_strlen(t_r->tst));
	}
	put_in_histo(enviro, t_r->tst);
	*line = t_r->tst;
	return (0);
}

void	k_ctrl_c(t_env *enviro, t_read *t_r, int *end)
{
	write(1, "^C\n", 3);
	ft_memset(t_r->tst, 0, ft_strlen(t_r->tst));
	t_r->multi = 0;
	*end = 0;
	enviro->lsc = 130;
	print_new_line(enviro->lsc);
}

void	k_normal(t_read *t_r, int *end)
{
	t_r->hold = ft_strdup(t_r->tst);
	t_r->tmp = t_r->tst;
	t_r->tst = ft_calloc(ft_strlen(t_r->hold) + 3, sizeof(char));
	free(t_r->tmp);
	ft_strlcpy(t_r->tst, t_r->hold, ft_strlen(t_r->hold) + 1);
	put_char_in_str(t_r->tst, *end, t_r->t);
	++*end;
	free(t_r->hold);
}

void	k_del(t_read *t_r, int *end, t_key key)
{
	int j;

	ft_strlcpy(&t_r->tst[*end - 1], &t_r->tst[*end],
		ft_strlen(&t_r->tst[*end]) + 1);
	*end = *end - 1;
	write(1, &key.g, 3);
	write(1, &t_r->tst[*end], ft_strlen(&t_r->tst[*end]));
	write(1, " ", 1);
	j = 0;
	while ((size_t)(j) <= ft_strlen(&t_r->tst[*end]))
	{
		write(1, &key.g, 3);
		++j;
	}
}

void	write_char(t_read *t_r, int *end, t_key key)
{
	int i;

	write(1, &t_r->t, 1);
	write(1, &t_r->tst[*end], ft_strlen(&t_r->tst[*end]));
	i = 0;
	while ((size_t)(i) < ft_strlen(&t_r->tst[*end]))
	{
		write(1, &key.g, 3);
		++i;
	}
}
