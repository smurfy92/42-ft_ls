/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 03:55:31 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/05 03:55:33 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		ft_ls_rec(t_lstdir *lst, t_options *opt, char *dir)
{
	char		*tmp;

	while (lst)
	{
		if (lst->isdir && (!(!opt->a && lst->name[0] == '.')) &&
		ft_strcmp(lst->name, ".") != 0 && ft_strcmp(lst->name, "..") != 0)
		{
			if (ft_strcmp(dir, "/") != 0)
			{
				tmp = ft_strjoin(dir, "/");
				tmp = ft_strjoin(tmp, lst->name);
			}
			else
				tmp = ft_strjoin(dir, lst->name);
			opt->tmp = ft_strdup(tmp);
			ft_putchar('\n');
			ft_putstr(opt->tmp);
			ft_putendl(":");
			ft_process(tmp, opt);
		}
		lst = lst->next;
	}
}

void		ft_print_dir(char *dir, t_options *opt)
{
	struct stat		bufstat;
	t_lstdir		*lst;

	if (!dir)
		return ;
	if (opt->a == 0 && dir[0] == '.')
		return ;
	if (stat(dir, &bufstat) == -1)
		perror(dir);
	if (opt->l)
	{
		lst = (t_lstdir*)malloc(sizeof(t_lstdir));
		lst->name = ft_strdup(dir);
		lst->next = NULL;
		lst = ft_add_stats(lst, bufstat, opt);
		ft_print_rights(lst, opt);
		ft_print_links_usr_grp(lst, opt);
		ft_print_time(lst, opt);
	}
	ft_putendl(dir);
}

void		ft_process(char *dir, t_options *opt)
{
	t_lstdir *lst;
	t_lstdir *tmp;

	opt = ft_refresh_opt(opt);
	if ((lst = ft_read_dir(dir, opt)) != NULL)
	{
		(opt->t) ? lst = ft_ls_t(lst) : 0;
		(opt->r) ? lst = ft_ls_r(lst) : 0;
		tmp = lst;
		(opt->l) ? ft_print_total(opt->total) : 0;
		while (lst)
		{
			if ((opt->l || opt->o || opt->p || opt->g) &&
			(!(!opt->a && lst->name[0] == '.')))
				ft_ls_l(lst, opt);
			else
				(!(!opt->a && lst->name[0] == '.')) ?
				ft_putendl(lst->name) : 0;
			lst = lst->next;
		}
		(opt->rec) ? ft_ls_rec(tmp, opt, dir) : 0;
	}
	else
		(!opt->rec) ? ft_print_dir(dir, opt) : 0;
}

int			ft_is_dir(char *dir)
{
	struct stat		bufstat;

	if (stat(dir, &bufstat) == -1)
		return (0);
	else
	{
		if (S_IFDIR & bufstat.st_mode)
			return (1);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_options	*opt;

	opt = NULL;
	opt = ft_init_opt(opt);
	opt = ft_parse_options(argc, argv, opt);
	if (opt->nbfile == 0 && opt->errors == 0)
	{
		opt->tmp = ft_strdup(".");
		ft_process(".", opt);
	}
	while (++opt->actual < opt->nbfile)
	{
		opt->tmp = ft_strdup(opt->files[opt->actual]);
		(opt->actual != 0 && ft_is_dir(opt->files[opt->actual]))
		? ft_putchar('\n') : 0;
		if (opt->nbfile > 1 && ft_is_dir(opt->files[opt->actual]))
		{
			ft_putstr(opt->files[opt->actual]);
			ft_putstr(":\n");
		}
		ft_process(opt->files[opt->actual], opt);
	}
	return (0);
}
