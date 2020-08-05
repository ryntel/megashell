/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:04:19 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/07 12:04:21 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	if (!src)
		return (dest);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < n && (dest || src))
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return (dest);
}
