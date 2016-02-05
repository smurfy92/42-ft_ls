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

void		ft_print_rights(struct stat bufstat)
{

	mode_t val;

	val=(bufstat.st_mode & ~S_IFMT);
	(S_IFDIR & (bufstat.st_mode)) ? ft_putchar('d') : ft_putchar('-');
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

void		ft_print_links_usr_grp(struct stat bufstat)
{
	struct passwd *user;
	struct group *usergroup;

	if (bufstat.st_nlink < 100)
		ft_putchar(' ');
	if (bufstat.st_nlink < 10)
		ft_putchar(' ');
	ft_putchar(' ');
	ft_putnbr(bufstat.st_nlink);
	user = getpwuid(bufstat.st_uid);
	ft_putchar(' ');
	ft_putstr(user->pw_name);
	ft_putchar(' ');
	usergroup = getgrgid(bufstat.st_gid);
	ft_putchar(' ');
	ft_putstr(usergroup->gr_name);
	ft_putchar(' ');
}

void		ft_print_size(struct stat bufstat)
{
	if (bufstat.st_size < 100000)
		ft_putchar(' ');
	if (bufstat.st_size < 10000)
		ft_putchar(' ');
	if (bufstat.st_size < 1000)
		ft_putchar(' ');
	if (bufstat.st_size < 100)
		ft_putchar(' ');
	if (bufstat.st_size < 10)
		ft_putchar(' ');
	ft_putnbr(bufstat.st_size);
	ft_putchar(' ');
}

void		ft_print_time(char *str)
{
	int i;

	i = 0;
	while (42)
	{
		if (*str == ':' && i == 1)
			break;
		else if(*str == ':' && i == 0)
			i++;
		ft_putchar(*str++);
	}
	ft_putchar(' ');
}

void		ft_ls_l(t_lstdir *lst, t_options *opt)
{
	struct stat 	bufstat;

	if (!opt->a && lst->name[0] == '.')
		return ;
	if (stat(lst->name, &bufstat) == -1)
	{
		//perror("stat");
		//ft_putstr("ls -r");
	}
	ft_print_rights(bufstat);
	ft_print_links_usr_grp(bufstat);
	ft_print_size(bufstat);
	ft_print_time(ctime(&bufstat.st_mtime));
	ft_putendl(lst->name);
}
