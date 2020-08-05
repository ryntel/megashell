/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_read.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:54:54 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/20 16:54:55 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

void	setup_intera_mode(t_inter_read *term)
{
	tcgetattr(0, &term->backup);
	tcgetattr(0, &term->s_set);
	term->s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
}
