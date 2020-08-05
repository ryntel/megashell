/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:43:12 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/16 13:43:14 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *lst;
	tmp2 = tmp;
	if (tmp && (*del) && *lst && lst)
	{
		while (tmp->next != NULL)
		{
			tmp = tmp2;
			(*del)(tmp->content);
			tmp2 = tmp->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
