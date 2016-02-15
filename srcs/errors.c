/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 05:26:56 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/01 17:06:51 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_error_message(char *str)
{
	ft_putendl(str);
	exit(0);
}

void		ft_error(char *str, int error)
{
	if (error == 20)
		return ;
	else
	{
		ft_putstr("ls: ");
		ft_putstr(str);
		ft_putstr(": ");
		ft_error_message(strerror(error));
	}
}

int			ft_compare_date(char *s1, char *s2)
{
	if (ft_strncmp((s1 + 20), (s2 + 20), 4) > 0)
		return (0);
	(s1[9] == ' ') ? s1++ : 0;
	(s2[9] == ' ') ? s2++ : 0;
	if (ft_strncmp((s1 + 8), (s2 + 8), 10) < 0)
		return (0);
	return (1);
}

int			ft_check_cols(int tmp)
{
	int i;

	i = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}


void		ft_illegal_opt(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putchar('\n');
	ft_error_message("usage: ft_ls [-lartRo] [file ...]");
}
