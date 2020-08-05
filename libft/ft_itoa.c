/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:12:45 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/09 10:12:46 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*next(char *str, long n, int len)
{
	int i;
	int neg;

	if (n < 0)
	{
		str[len + 1] = '\0';
		str[0] = '-';
	}
	else
		str[len + 1] = '\0';
	i = len;
	if (n < 0)
		neg = 1;
	else
		neg = 0;
	n < 0 ? n = n * -1 : n;
	while (i >= neg)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

static void	ft_setup(int n, long *k, int *len, long *nb)
{
	*nb = (long)n;
	*len = 1;
	*k = *nb;
}

char		*ft_itoa(int n)
{
	long	k;
	int		len;
	char	*str;
	long	nb;

	ft_setup(n, &k, &len, &nb);
	k < 0 ? k = k * -1 : k;
	while (k >= 10)
	{
		k = k / 10;
		len = len + 1;
	}
	if (nb < 0)
	{
		if (!(str = malloc((len + 2) * sizeof(char))))
			return (NULL);
	}
	else
	{
		if (!(str = malloc((len + 1) * sizeof(char))))
			return (NULL);
		len = len - 1;
	}
	return (next(str, nb, len));
}
