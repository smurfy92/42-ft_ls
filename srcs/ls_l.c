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

void		ft_print_acl(t_lstdir *lst, t_options *opt)
{
	ssize_t	buflen;
	char	*tmp;
	acl_t	a;

	tmp = NULL;
	if (((lst->mode & ~S_IFMT) & S_ISVTX))
		ft_putchar('t');
	else
		((lst->mode & ~S_IFMT) & S_IXOTH) ? ft_putchar('x') : ft_putchar('-');
	tmp = ft_strjoin(opt->tmp, "/");
	(S_ISLNK(lst->mode)) ? (buflen = listxattr(ft_strjoin(tmp, lst->name),\
	(char*)NULL, 0, XATTR_NOFOLLOW)) : (buflen = listxattr(ft_strjoin(tmp,\
	lst->name), (char*)NULL, 0, 0));
	(S_ISLNK(lst->mode)) ? (a = acl_get_link_np(ft_strjoin(tmp, lst->name),\
	ACL_TYPE_EXTENDED)) : (a = acl_get_file(ft_strjoin(tmp, lst->name),\
	ACL_TYPE_EXTENDED));
	if (buflen > 0)
		ft_putchar('@');
	else if (a)
		ft_putchar('+');
	else
		ft_putchar(' ');
	ft_print_links_usr_grp(lst, opt);
}

void		ft_print_links_usr_grp(t_lstdir *lst, t_options *opt)
{
	int i;

	i = lst->space_lnk;
	while (i++ <= opt->max_lnk)
		ft_putchar(' ');
	ft_putnbr(lst->links);
	if (!opt->g)
	{
		ft_putchar(' ');
		ft_putstr(lst->pwname);
		ft_putchar(' ');
	}
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
	ft_print_sizes(lst, opt);
	ft_putchar(' ');
}

void		ft_print_sizes(t_lstdir *lst, t_options *opt)
{
	int i;

	i = lst->space_major;
	if (opt->max_major)
		while (i++ <= opt->max_major + 2)
			ft_putchar(' ');
	i = lst->space_minor;
	if (S_ISCHR(lst->mode) || S_ISBLK(lst->mode))
	{
		ft_putnbr(lst->major);
		ft_putstr(",");
		while (i++ < opt->max_minor)
			ft_putchar(' ');
		ft_putnbr(lst->minor);
	}
	else
	{
		if (opt->max_major)
			while (i++ <= opt->max_minor)
				ft_putchar(' ');
		else
			while (i++ <= opt->max_minor)
				ft_putchar(' ');
		ft_putnbr(lst->minor);
	}
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
	ft_putstr(lst->name);
}

void		ft_ls_l(t_lstdir *lst, t_options *opt)
{
	char		*buf;
	char		*tmp;
	int			end;

	if (!opt->a && lst->name[0] == '.')
		return ;
	tmp = ft_strjoin(opt->tmp, "/");
	tmp = ft_strjoin(tmp, lst->name);
	((access(tmp, R_OK) == -1) && (access(tmp, W_OK) == -1) &&\
	(access(tmp, X_OK) == -1) && ft_is_dir(tmp)) ? perror(lst->name) : 0;
	ft_print_rights(lst, opt);
	ft_print_time(lst, opt);
	(lst->isdir && opt->p) ? ft_putchar('/') : 0;
	if (S_ISLNK(lst->mode))
	{
		buf = (char *)malloc(sizeof(char) * 255);
		ft_putstr(" -> ");
		end = readlink(tmp, buf, 255);
		buf[end] = '\0';
		ft_putstr(buf);
		free(tmp);
		free(buf);
	}
	ft_putchar('\n');
}
