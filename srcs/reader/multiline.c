/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:27:55 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:28:03 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static void		multi_pipe(t_read *t_r, int *end)
{
	*end = ft_strlen(t_r->tst);
	write(1, "\n> ", 3);
	t_r->multi = t_r->multi - 1;
}

static void		multi_backslash(t_read *t_r, int *end)
{
	*end = ft_strlen(t_r->tst);
	t_r->t = '\0';
	*end = *end - 1;
	k_normal(t_r, end);
	--*end;
	t_r->multi = t_r->multi - 2;
	write(1, "\n> ", 3);
}

static void		multi_quote(t_read *t_r, int *end)
{
	*end = ft_strlen(t_r->tst);
	t_r->t = '\n';
	k_normal(t_r, end);
	write(1, "\n> ", 3);
}

/*
**	normal \n
**	broken pipe
**	broken backslash
**	brken quote
*/

int				multine_hub(t_read *t_r, t_env *enviro, char **line, int *end)
{
	t_r->multi = k_enter(enviro, line, t_r);
	if (t_r->multi == 0)
		return (1);
	if (t_r->brok == 'p')
		multi_pipe(t_r, end);
	else if (t_r->brok == 'b')
		multi_backslash(t_r, end);
	else
		multi_quote(t_r, end);
	return (0);
}
