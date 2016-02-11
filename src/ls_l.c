/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_l.c                                             :+:      :+:    :+:   */
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
	(val & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void		ft_print_links_usr_grp(t_lstdir *lst, t_options *opt)
{
	int i;

	i = lst->space_lnk;
	while (i++ <= opt->max_lnk)
		ft_putchar(' ');
	ft_putnbr(lst->links);
	ft_putchar(' ');
	ft_putstr(lst->pwname);
	ft_putchar(' ');
	i = lst->space_uid;
	while (i++ <= opt->max_uid)
		ft_putchar(' ');
	ft_putstr(lst->grpname);
	i = lst->space_gid;
	while (i++ <= opt->max_gid)
		ft_putchar(' ');
	i = lst->space_size;
	while (i++ <= opt->max_size)
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
	ft_print_links_usr_grp(lst, opt);
	ft_print_time(lst->mtime);
	ft_putendl(lst->name);
}
