/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_event1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:28:14 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:28:16 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void		k_left(t_key key, int *end, t_read *t_r)
{
	if (*end > 0)
	{
		write(1, &key.g, 3);
		--*end;
	}
	ft_memset(t_r->c_key, 0, 4);
}

void		k_right(t_key key, int *end, t_read *t_r)
{
	if ((size_t)(*end) < ft_strlen(t_r->tst))
	{
		write(1, &key.d, 3);
		++*end;
	}
	ft_memset(t_r->c_key, 0, 4);
}

void		k_up(t_env *enviro, t_read *t_r, t_key key, int *end)
{
	unsigned int k;

	if (enviro->histo[t_r->ou] != NULL)
	{
		++t_r->ou;
		k = 0;
		while (++k <= ft_strlen(t_r->tst) - ft_strlen(&t_r->tst[*end]))
			write(1, &key.g, 3);
		k = 0;
		while (++k <= ft_strlen(t_r->tst))
			write(1, " ", 1);
		k = 0;
		while (++k <= ft_strlen(t_r->tst))
			write(1, &key.g, 3);
		free(t_r->tst);
		t_r->tst = ft_strdup(enviro->histo[t_r->ou - 1]);
		write(1, t_r->tst, ft_strlen(t_r->tst));
		*end = ft_strlen(t_r->tst);
	}
	ft_memset(t_r->c_key, 0, 4);
}

static void	k_down_next(t_read *t_r, t_key key, int *end)
{
	unsigned int k;

	k = 0;
	if (t_r->ou == 2)
		--t_r->ou;
	k = 0;
	while (++k <= ft_strlen(t_r->tst) - ft_strlen(&t_r->tst[*end]))
		write(1, &key.g, 3);
	k = 0;
	while (++k <= ft_strlen(t_r->tst))
		write(1, " ", 1);
	k = 0;
	while (++k <= ft_strlen(t_r->tst))
		write(1, &key.g, 3);
	free(t_r->tst);
	t_r->tst = ft_strdup("");
	*end = 0;
}

void		k_down(t_env *enviro, t_read *t_r, t_key key, int *end)
{
	unsigned int k;

	k = 0;
	if (t_r->ou > 2)
	{
		--t_r->ou;
		k = 0;
		while (++k <= ft_strlen(t_r->tst) - ft_strlen(&t_r->tst[*end]))
			write(1, &key.g, 3);
		k = 0;
		while (++k <= ft_strlen(t_r->tst))
			write(1, " ", 1);
		k = 0;
		while (++k <= ft_strlen(t_r->tst))
			write(1, &key.g, 3);
		free(t_r->tst);
		t_r->tst = ft_strdup(enviro->histo[t_r->ou - 1]);
		write(1, t_r->tst, ft_strlen(t_r->tst));
		*end = ft_strlen(t_r->tst);
	}
	else if (t_r->ou <= 2)
		k_down_next(t_r, key, end);
	ft_memset(t_r->c_key, 0, 4);
}
