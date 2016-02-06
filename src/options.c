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

t_options	*ft_init_opt(t_options *opt)
{
	opt = (t_options*)malloc(sizeof(t_options));
	opt->l = 0;
	opt->r = 0;
	opt->a = 0;
	opt->R = 0;
	opt->t = 0;
	opt->nbfile = 0;
	opt->files = NULL;
	return (opt);
}

t_options	*ft_add_option(char c, t_options *opt)
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
		ft_error_message("./ft_ls: illegal option");
	return (opt);
}

t_options	*ft_parse_options(int argc, char **argv, t_options *opt)
{
	int i;
	int j;
	int	files;

	i = 0;
	files = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][0] == '-' && files == 0)
		{
			if (!argv[i][1])
			{
				ft_error_nofile(argv[i]);
				exit(0);
			}
			while (argv[i][++j])
				opt = ft_add_option(argv[i][j], opt);
		}
		else
		{
			if (!opt->files)
				opt->files = (char**)malloc(sizeof(char*) * 1000);
			opt->files[files] = ft_strdup(argv[i]);
			printf("opt->filename : %s\n", opt->files[files]);
			opt->nbfile = files + 1;
			files++;
		}
	}
	return (opt);
}
