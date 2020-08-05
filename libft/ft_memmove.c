/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:44:32 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/07 13:44:34 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*t_src;
	char			*t_dest;
	size_t			i;

	if (!dest || !src)
		return (NULL);
	t_src = (char*)src;
	t_dest = (char*)dest;
	if (t_dest > t_src)
	{
		i = n;
		while (i > 0)
		{
			t_dest[i - 1] = t_src[i - 1];
			i--;
		}
	}
	else if (t_dest < t_src)
		ft_memcpy(t_dest, t_src, n);
	return (dest);
}
