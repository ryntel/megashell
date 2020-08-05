/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:48:36 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/07 17:48:37 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int output;
	unsigned int i;
	unsigned int j;

	if (!dest || !src)
		return (ft_strlen(src));
	if (size < ft_strlen(dest))
		output = ft_strlen(src) + size;
	else
		output = ft_strlen(src) + ft_strlen(dest);
	if (size > 0 && size - 1 > ft_strlen(dest))
	{
		i = 0;
		while (dest[i] != '\0')
			i++;
		j = 0;
		while (src[j] != '\0' && i < size - 1)
		{
			dest[i] = src[j];
			j++;
			i++;
		}
		dest[i] = '\0';
	}
	return (output);
}
