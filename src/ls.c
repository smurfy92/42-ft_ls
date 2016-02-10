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

void	ft_ls_rec(t_lstdir *lst, t_options *opt, char *dir)
{
	char 			*tmp;

	while (lst)
	{
		if (lst->isdir && lst->name[0] != '.')
		{
			tmp = ft_strjoin(dir, "/");
			tmp = ft_strjoin(tmp, lst->name);
			ft_putchar('\n');
			ft_putstr(tmp);
			ft_putendl(":");
			if (tmp[1] == '/')
				tmp = (tmp + 1);
			opt->tmp = ft_strdup(tmp);
			ft_process(tmp, opt);
		}
		lst = lst->next;
	}
}

void	ft_print_dir(char *dir, t_options *opt)
{
	struct stat 	bufstat;
	t_lstdir		*lst;

	if (!dir)
		return ;
	if (opt->a == 0 && dir[0] == '.')
		return ;
	if (stat(dir, &bufstat) == -1)
	{
		//perror("stat");
		//ft_putstr("ls -r");
	}
	if (opt->l)
	{
		lst = (t_lstdir*)malloc(sizeof(t_lstdir));
		lst->name = ft_strdup(dir);
		lst->next = NULL;
		lst = ft_add_stats(lst, bufstat);
		ft_print_rights(lst);
		ft_print_links_usr_grp(lst);
		ft_print_size(lst);
		ft_print_time(lst->mtime);
	}
	ft_putendl(dir);
}

void	ft_process(char *dir, t_options *opt)
{
	t_lstdir *lst;
	t_lstdir *tmp;

	if ((lst = ft_read_dir(dir, opt)) != NULL)
	{
		if (opt->t)
			lst = ft_ls_t(lst);
		if (opt->r)
			lst = ft_ls_r(lst);
		tmp = lst;
		if (opt->l)
		{
			ft_putstr("total ");
			ft_putnbr(opt->total);
			ft_putchar('\n');
		}
		while (lst)
		{
			if (opt->l && (!(!opt->a && lst->name[0] == '.')))
			{
				ft_ls_l(lst, opt);
			}
			else
				if (!(!opt->a && lst->name[0] == '.'))
					ft_putendl(lst->name);
			lst = lst->next;
		}
		if (opt->R)
			ft_ls_rec(tmp, opt, dir);
	}
	else
		if (!opt->R)
			ft_print_dir(dir, opt);
}

int		ft_is_dir(char *dir)
{
	struct stat 	bufstat;

	if (stat(dir, &bufstat) == -1)
		return (0);
	else
		if (S_IFDIR & bufstat.st_mode)
			return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_options	*opt;

	opt = NULL;
	opt = ft_init_opt(opt);
	if (argc == 1)
		ft_process(".", opt);
	else
	{
		opt = ft_parse_options(argc, argv, opt);
		if (opt->nbfile == 0)
		{
			opt->tmp = ft_strdup(".");
			ft_process(".", opt);
		}
		while (++opt->actual < opt->nbfile)
		{
			opt->tmp = ft_strdup(opt->files[opt->actual]);
			if (opt->actual != 0)
				ft_putchar('\n');
			if (ft_is_dir(opt->files[opt->actual]) && opt->nbfile > 1)
			{
				ft_putstr(opt->files[opt->actual]);
				ft_putstr(" : \n");
			}
			ft_process(opt->files[opt->actual], opt);
		}
	}
	return (0);
}
