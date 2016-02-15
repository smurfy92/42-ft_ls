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

void		ft_print_rights(t_lstdir *lst, t_options *opt)
{
	mode_t val;
	char *test = NULL;
	char *tmp = NULL;
	ssize_t buflen;
	acl_t a;

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
	if ((val & S_ISVTX))
		ft_putchar('t');
	else
		(val & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	tmp = ft_strjoin(opt->tmp, "/");
	buflen = listxattr(ft_strjoin(tmp,lst->name), test, 0, 0);
	a = acl_get_file(ft_strjoin(tmp,lst->name), ACL_TYPE_EXTENDED);
	if (buflen > 0)
		ft_putchar('@');
	else if (a)
		ft_putchar('+');
	else
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
	(opt->o) ? i++ : 0;
	while (i++ <= opt->max_uid)
		ft_putchar(' ');
	if (!opt->o)
	{
		ft_putstr(lst->grpname);
		i = lst->space_gid;
		while (i++ <= opt->max_gid)
			ft_putchar(' ');
	}
	i = lst->space_major;
	if (opt->max_major)
		while (i++ <= opt->max_major + 1)
			ft_putchar(' ');
	if (S_ISCHR(lst->mode) || S_ISBLK(lst->mode))
	{
		ft_putnbr(lst->major);
		ft_putstr(",");
		i = lst->space_minor;
		while (i++ < opt->max_minor)
			ft_putchar(' ');
		ft_putnbr(lst->minor);
	}
	else
	{
		i = lst->space_minor;
		if (opt->max_major)
			while (i++ <= opt->max_minor)
				ft_putchar(' ');
		else
			while (i++ <= opt->max_minor)
				ft_putchar(' ');
		ft_putnbr(lst->minor);
	}
	ft_putchar(' ');
}

void		ft_print_time(t_lstdir *lst, t_options *opt)
{
	char *tmp;
	char *tmp2;

	if (opt->actualtime - lst->mdateint <= 15724800)
	{
		tmp = ft_strsub(lst->mdate, 4, 12);
		ft_putstr(tmp);
	}
	else
	{
		tmp = ft_strsub(lst->mdate, 4, 7);
		tmp2 = ft_strsub(lst->mdate, 19, 5);
		ft_putstr(tmp);
		ft_putstr(tmp2);
	}
	ft_putchar(' ');
}

void		ft_ls_l(t_lstdir *lst, t_options *opt)
{
	char		*buf;
	char 		*tmp;
	int 		end;

	if (!opt->a && lst->name[0] == '.')
		return ;
	ft_print_rights(lst, opt);
	ft_print_links_usr_grp(lst, opt);
	ft_print_time(lst, opt);
	ft_putstr(lst->name);
	(lst->isdir && opt->p) ? ft_putchar('/') : 0;
	if (S_ISLNK(lst->mode))
	{
		buf = (char *)malloc(sizeof(char) * 255);
		ft_putstr(" -> ");
		tmp = ft_strjoin(opt->tmp, "/");
		tmp = ft_strjoin(tmp, lst->name);
		end = readlink(tmp, buf, 255);
		buf[end] = '\0';
		ft_putstr(buf);
		free(tmp);
		free(buf);
	}
	ft_putchar('\n');
}
