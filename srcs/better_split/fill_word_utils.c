/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_word_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:21:49 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:21:51 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void	d_quote_normal_case(t_word *giv, const char *str)
{
	giv->word[*giv->dep] = str[*giv->i];
	++*giv->dep;
	++*giv->i;
}
