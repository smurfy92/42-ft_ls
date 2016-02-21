/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 03:55:41 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/05 03:55:42 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_lstdir		*ft_ls_t_init(t_lstdir *lst)
{
	t_lstdir *tmp2;

	tmp2 = (t_lstdir*)malloc(sizeof(t_lstdir));
	tmp2->name = ft_strdup(lst->name);
	tmp2->mdate = ft_strdup(lst->mdate);
	tmp2->mdateint = lst->mdateint;
	tmp2->links = lst->links;
	tmp2->mode = lst->mode;
	tmp2->pwname = ft_strdup(lst->pwname);
	tmp2->grpname = ft_strdup(lst->grpname);
	tmp2->space_lnk = lst->space_lnk;
	tmp2->space_uid = lst->space_uid;
	tmp2->space_gid = lst->space_gid;
	tmp2->space_major = lst->space_major;
	tmp2->space_minor = lst->space_minor;
	tmp2->major = lst->major;
	tmp2->minor = lst->minor;
	tmp2->mtime = ft_strdup(lst->mtime);
	tmp2->isdir = lst->isdir;
	tmp2->next = NULL;
	return (tmp2);
}

t_options		*ft_init_opt(t_options *opt)
{
	opt = (t_options*)malloc(sizeof(t_options));
	opt->l = 0;
	opt->r = 0;
	opt->a = 0;
	opt->rec = 0;
	opt->errors = 0;
	opt->t = 0;
	opt->o = 0;
	opt->p = 0;
	opt->g = 0;
	opt->max_lnk = 0;
	opt->max_uid = 0;
	opt->max_gid = 0;
	opt->max_major = 0;
	opt->max_minor = 0;
	opt->total = 0;
	opt->nbfile = 0;
	opt->actualtime = time(0);
	opt->actual = -1;
	opt->tmp = NULL;
	opt->files = NULL;
	return (opt);
}

t_options		*ft_add_option(char c, t_options *opt)
{
	if (c == 'a')
		opt->a = 1;
	else if (c == 'r')
		opt->r = 1;
	else if (c == 'l')
		opt->l = 1;
	else if (c == 'R')
		opt->rec = 1;
	else if (c == 't')
		opt->t = 1;
	else if (c == 'o')
		opt->o = 1;
	else if (c == 'p')
		opt->p = 1;
	else if (c == 'g')
		opt->g = 1;
	else
		ft_illegal_opt(c);
	return (opt);
}

t_options		*ft_order(t_options *opt)
{
	int			i;
	char		*tmp;

	i = 0;
	while (++i < opt->nbfile)
	{
		if (ft_strcmp(opt->files[i], opt->files[i - 1]) > 0)
		{
			tmp = opt->files[i];
			opt->files[i] = opt->files[i - 1];
			opt->files[i - 1] = tmp;
			i = 0;
		}
	}
	(opt->t) ? (opt = ft_order_by_date(opt)) : 0;
	(opt->r) ? (opt = ft_order_reverse(opt)) : 0;
	return (opt);
}

t_options		*ft_parse_options(int argc, char **argv, t_options *opt)
{
	int i;

	opt->files = (char**)malloc(sizeof(char*) * 1000);
	i = 0;
	while (++i < argc)
		opt = ft_parse(opt, i, argv);
	opt = ft_order(opt);
	return (opt);
}
