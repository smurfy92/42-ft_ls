/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:30:30 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/16 16:30:36 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_print_rights(t_lstdir *lst)
{
	mode_t val;

	(S_ISCHR(lst->mode)) ? ft_putchar('c') : 0;
	(S_ISLNK(lst->mode)) ? ft_putchar('l') : 0;
	(S_ISDIR(lst->mode)) ? ft_putchar('d') : 0;
	(S_ISREG(lst->mode)) ? ft_putchar('-') : 0;
	(S_ISFIFO(lst->mode)) ? ft_putchar('p') : 0;
	(S_ISBLK(lst->mode)) ? ft_putchar('b') : 0;
	(S_ISSOCK(lst->mode)) ? ft_putchar('s') : 0;
	val = (lst->mode & ~S_IFMT);
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
}
