/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls-l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 03:55:50 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/05 03:55:51 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_print_rights(t_lstdir *lst)
{
	mode_t val;

	((lst->mode & S_IFCHR)) ? ft_putchar('l') : 0;
	((lst->mode & S_IFREG)) ? ft_putchar('-') : 0;
	(S_ISDIR(lst->mode)) ? ft_putchar('d') : 0;
	((lst->mode & S_IFIFO)) ? ft_putchar('f') : 0;
	//((lst->mode & S_IFLNK)) ? ft_putchar('t') : 0;
	//((lst->mode & S_IFBLK)) ? ft_putchar('b') : 0;
	//((lst->mode & S_IFSOCK)) ? ft_putchar('e') : 0;
	//((lst->mode & S_IFWHT)) ? ft_putchar('f') : 0;

	val = (lst->mode & ~S_IFMT);
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	(val & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void		ft_print_links_usr_grp(t_lstdir *lst)
{
	if (lst->links < 100)
		ft_putchar(' ');
	if (lst->links < 10)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr(lst->links);
	ft_putchar(' ');
	ft_putstr(lst->pwname);
	ft_putstr("  ");
	ft_putstr(lst->grpname);
	ft_putchar(' ');
}

void		ft_print_size(t_lstdir *lst)
{
	if (lst->size < 100000)
		ft_putchar(' ');
	if (lst->size < 10000)
		ft_putchar(' ');
	if (lst->size < 1000)
		ft_putchar(' ');
	if (lst->size < 100)
		ft_putchar(' ');
	if (lst->size < 10)
		ft_putchar(' ');
	ft_putnbr(lst->size);
	ft_putchar(' ');
}

void		ft_print_time(char *str)
{
	int i;
	int space;

	i = 0;
	space = 0;
	while (42)
	{
		if (*str == ':' && i == 1)
			break ;
		else if (*str == ':' && i == 0)
			i++;
		if (space != 0)
			ft_putchar(*str);
		if (*str == ' ')
			space++;
		str++;
	}
	ft_putchar(' ');
}

void		ft_ls_l(t_lstdir *lst, t_options *opt)
{
	if (!opt->a && lst->name[0] == '.')
		return ;
	ft_print_rights(lst);
	ft_print_links_usr_grp(lst);
	ft_print_size(lst);
	ft_print_time(lst->mtime);
	ft_putendl(lst->name);
}
