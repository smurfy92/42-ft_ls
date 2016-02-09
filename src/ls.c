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
	char			*tmpstat;
	struct stat 	bufstat;

	while (lst)
	{
		if (opt->tmp)
		{

			tmpstat = ft_strjoin(opt->tmp, "/");
			tmpstat = ft_strjoin(tmpstat, lst->name);
			if (stat(tmpstat, &bufstat) == -1)
			{
				//ft_putendl(tmpstat);
				//ft_error(tmpstat, 2);
			}
		}
		else
		{
			if (stat(lst->name, &bufstat) == -1)
			{
				//ft_putendl(dir);
				//ft_error(dir, 2);
			}
		}
		if ((S_IFDIR & bufstat.st_mode) && lst->name[0] != '.')
		{
			tmp = ft_strjoin(dir, "/");
			tmp = ft_strjoin(tmp, lst->name);
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
	if (opt->l && ((lst = ft_read_dir(dir, opt)) != NULL))
	{
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

	if (opt->R && opt->tmp)
	{
		ft_putchar('\n');
		ft_putendl(opt->tmp);
	}
	if ((lst = ft_read_dir(dir, opt)) != NULL)
	{
		if (opt->t)
			lst = ft_ls_t(lst);
		if (opt->r)
			lst = ft_ls_r(lst);
		tmp = lst;
		while (lst)
		{
			if (opt->l && (!(!opt->a && lst->name[0] == '.')))
				ft_ls_l(lst, opt);
			else
				if (!(!opt->a && lst->name[0] == '.'))
					ft_putendl(lst->name);
			lst = lst->next;
		}
		if (opt->R)
			ft_ls_rec(tmp, opt, dir);
	}
	else
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
	t_options *opt = NULL;
	int 	i;

	i = -1;
	opt = ft_init_opt(opt);
	if (argc == 1)
		ft_process(".", opt);
	else
	{
		opt = ft_parse_options(argc, argv, opt);
		if (opt->nbfile == 0)
			ft_process(".", opt);
		while (++i < opt->nbfile)
		{
			if (i != 0)
				ft_putchar('\n');
			if (ft_is_dir(opt->files[i]) && opt->nbfile > 1)
			{
				ft_putstr(opt->files[i]);
				ft_putstr(" : \n");
			}
			opt->actual = i;
			ft_process(opt->files[i], opt);
		}
	}
	return (0);
}
