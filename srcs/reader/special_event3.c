/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_event3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:28:56 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:29:01 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void	k_home(t_key key, t_read *t_r, int *end)
{
	unsigned int k;

	k = *end;
	while (k > 0)
	{
		write(1, key.g, 3);
		--k;
	}
	*end = 0;
	ft_memset(t_r->c_key, 0, 4);
}

void	k_end(t_key key, t_read *t_r, int *end)
{
	unsigned int k;
	unsigned int len;

	k = *end;
	len = ft_strlen(t_r->tst);
	while (k < len)
	{
		write(1, key.d, 3);
		++k;
	}
	*end = ft_strlen(t_r->tst);
	ft_memset(t_r->c_key, 0, 4);
}
