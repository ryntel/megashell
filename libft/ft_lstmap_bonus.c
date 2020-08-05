/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:02:15 by avan-pra          #+#    #+#             */
/*   Updated: 2019/10/16 14:02:16 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list *maille;

	if (!lst || (*f))
		return (NULL);
	if (!(maille = ft_lstnew((*f)(lst->content))))
		return (NULL);
	maille->next = ft_lstmap(lst->next, (*f));
	return (maille);
}
