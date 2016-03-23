/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 17:19:18 by jtranchi          #+#    #+#             */
/*   Updated: 2016/03/19 17:19:20 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_print_ino(t_lstdir *lst, t_options *opt)
{
	if (!(!opt->a && lst->name[0] == '.') && opt->i)
	{
		ft_putnbr(lst->ino);
		ft_putchar(' ');
	}
}

void			ft_print_rights_begin(t_lstdir *lst)
{
	(S_ISCHR(lst->mode)) ? ft_putchar('c') : 0;
	(S_ISLNK(lst->mode)) ? ft_putchar('l') : 0;
	(S_ISDIR(lst->mode)) ? ft_putchar('d') : 0;
	(S_ISREG(lst->mode)) ? ft_putchar('-') : 0;
	(S_ISFIFO(lst->mode)) ? ft_putchar('p') : 0;
	(S_ISBLK(lst->mode)) ? ft_putchar('b') : 0;
	(S_ISSOCK(lst->mode)) ? ft_putchar('s') : 0;
	return ;
}
