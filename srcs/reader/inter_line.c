/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 11:27:40 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/04 11:27:47 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/megashell.h"

static int		fake_exit(t_read *t_r, t_env *enviro)
{
	enviro->ctrld = 1;
	write(1, "exit", 4);
	free(t_r->tst);
	if (!(t_r->tst = malloc(5 * sizeof(char))))
		return (0);
	ft_strlcpy(t_r->tst, "exit", 5);
	return (3);
}

/*
**	check all special keyin order, this function will check:
**
**		ctrl D		exit() tention
**		ctrl C
**		ctrl backslash (ne fait rien actuellement)
**		fleche gauche
**		fleche droite
**		fleche du haut
**		fleche du bas
**		touche delete
**		marquer le caractere si il est ok
*/

static int		check_key_next(t_read *t_r, int *end, t_key key)
{
	if (ft_strncmp(t_r->c_key, key.home, 4) == 0 && t_r->multi == 0)
		k_home(key, t_r, end);
	else if (ft_strncmp(t_r->c_key, key.end, 4) == 0 && t_r->multi == 0)
		k_end(key, t_r, end);
	else if (t_r->t == 127 && *end > 0
		&& (t_r->multi == 0 || *end - 1 > t_r->multi))
		k_del(t_r, end, key);
	else if (ft_strlen(t_r->c_key) == 0 && (t_r->t >= 32 && t_r->t <= 126))
		write_char(t_r, end, key);
	return (0);
}

static int		check_key(t_env *enviro, t_read *t_r, int *end, t_key key)
{
	if (t_r->t == 4 && ft_strlen(t_r->tst) == 0)
		return (fake_exit(t_r, enviro));
	else if (t_r->t == 3)
		k_ctrl_c(enviro, t_r, end);
	else if (t_r->t == 28)
		;
	else if (ft_strncmp(t_r->c_key, key.g, 4) == 0
		&& (t_r->multi == 0 || *end - 1 > t_r->multi))
		k_left(key, end, t_r);
	else if (ft_strncmp(t_r->c_key, key.d, 4) == 0
		&& ((size_t)(*end) < (t_r->multi - ft_strlen(t_r->tst))))
		k_right(key, end, t_r);
	else if (ft_strncmp(t_r->c_key, key.h, 4) == 0 && t_r->multi == 0)
		k_up(enviro, t_r, key, end);
	else if (ft_strncmp(t_r->c_key, key.b, 4) == 0 && t_r->multi == 0)
		k_down(enviro, t_r, key, end);
	else
		return (check_key_next(t_r, end, key));
	return (0);
}

/*
**	setup function for the read
*/

static void		setup_read(t_key *key, t_read *t_r, char c_key[4], int *end)
{
	*end = 0;
	t_r->c_key = c_key;
	ft_memset(t_r->c_key, 0, 4);
	t_r->ou = 1;
	t_r->multi = 0;
	fill_key(key);
	t_r->tst = ft_calloc(2, sizeof(char));
	t_r->multi = 0;
}

/*
**	main function for the read()
**	check for normal key (abcdef/etc...)
**	fill directionnal key if one was pressed
**	enter key
**	check for all other key
**	reset special key (to not segfault (shift + directionnal key))
*/

int				inter_line(char **line, t_env *enviro)
{
	t_read	t_r;
	t_key	key;
	int		end;
	char	c_key[4];

	setup_read(&key, &t_r, c_key, &end);
	while (1)
	{
		t_r.t = 0;
		read(0, &t_r.t, 1);
		if ((t_r.t >= 32 && t_r.t <= 126) && ft_strlen(c_key) == 0)
			k_normal(&t_r, &end);
		if (t_r.t == 27 || ft_strlen(c_key) > 0)
			c_key[ft_strlen(c_key)] = t_r.t;
		if (t_r.t == '\n' && multine_hub(&t_r, enviro, line, &end) == 1)
			return (1);
		else
		{
			if (check_key(enviro, &t_r, &end, key) == 3)
				return (k_enter(enviro, line, &t_r));
		}
		if (ft_strlen(c_key) >= 3)
			ft_memset(c_key, 0, 4);
	}
}
