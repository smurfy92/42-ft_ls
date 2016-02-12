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

t_lstdir		*ft_ls_t(t_lstdir *lst)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

	tmp = NULL;
	while (lst)
	{
		tmp2 = (t_lstdir*)malloc(sizeof(t_lstdir));
		tmp2->name = ft_strdup(lst->name);
		tmp2->mdate = ft_strdup(lst->mdate);
		tmp2->next = NULL;
		tmp = ft_add_lst_by_date(tmp2, tmp);
		lst = lst->next;
	}
	return (tmp);
}

t_lstdir		*ft_ls_r(t_lstdir *lst)
{
	t_lstdir *tmp;
	t_lstdir *tmp2;

	tmp = NULL;
	while (lst)
	{
		tmp2 = lst->next;
		lst->next = tmp;
		tmp = lst;
		lst = tmp2;
	}
	return (tmp);
}

t_options		*ft_init_opt(t_options *opt)
{
	opt = (t_options*)malloc(sizeof(t_options));
	opt->l = 0;
	opt->r = 0;
	opt->a = 0;
	opt->R = 0;
	opt->t = 0;
	opt->max_lnk = 0;
	opt->max_uid = 0;
	opt->max_gid = 0;
	opt->max_major = 0;
	opt->max_minor = 0;
	opt->total = 0;
	opt->nbfile = 0;
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
		opt->R = 1;
	else if (c == 't')
		opt->t = 1;
	else
		ft_illegal_opt(c);
	return (opt);
}

t_options		*ft_parse_options(int argc, char **argv, t_options *opt)
{
	int i;
	int j;
	int	files;

	opt->files = (char**)malloc(sizeof(char*) * 1000);
	i = 0;
	files = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] == '-' && files == 0)
		{
			if (!argv[i][1])
				ft_error(argv[i], 2);
			while (argv[i][++j])
				opt = ft_add_option(argv[i][j], opt);
		}
		else
		{
			opt->files[files] = ft_strdup(argv[i]);
			opt->nbfile = files + 1;
			files++;
		}
	}
	return (opt);
}
