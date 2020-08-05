/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:57:25 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/07 14:57:27 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *t_s1;
	unsigned char *t_s2;

	t_s1 = (unsigned char*)s1;
	t_s2 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	if (s1 && !s2)
		return (*t_s1);
	if (s2 && !s1)
		return (*t_s2 * -1);
	while (n > 1 && *t_s1 == *t_s2)
	{
		n--;
		t_s1++;
		t_s2++;
	}
	return (*t_s1 - *t_s2);
}
