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
			while (argv[i][++j])
				opt = ft_add_option(argv[i][j], opt);
		else
		{
			opt->files = (char**)malloc(sizeof(char*) * 1000);
			opt->files[files] = ft_strdup(argv[i]);
			opt->nbfile = files + 1;
			files++;
		}
	}
	return (opt);
}
