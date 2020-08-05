/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:49:36 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/07 17:49:38 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_here(size_t i, size_t len, const char *hay, const char *needle)
{
	size_t j;

	j = 0;
	while (hay[i] == needle[j] && needle[j] && i < len)
	{
		i++;
		j++;
	}
	if (!(needle[j]))
		return (1);
	return (0);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 0;
	if (!haystack && !needle)
		return (NULL);
	if (*needle == '\0')
		return ((char*)haystack);
	if (needle[0] == '\0' && needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		if (is_here(i, len, haystack, needle))
			return ((char*)&haystack[i]);
		i++;
	}
	return (NULL);
}
