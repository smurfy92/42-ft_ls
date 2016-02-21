/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:30:30 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/16 16:30:36 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_options		*ft_parse(t_options *opt, int i, char **argv)
{
	int				j;
	struct stat		bufstat;
	int				files;

	files = 0;
	j = 0;
	if (argv[i][0] == '-' && files == 0 && !ft_is_dir(argv[i]))
	{
		(!argv[i][1]) ? ft_error(argv[i], 2) : 0;
		while (argv[i][++j])
			opt = ft_add_option(argv[i][j], opt);
	}
	else
	{
		if (lstat(argv[i], &bufstat) != -1)
		{
			opt->files[files] = ft_strdup(argv[i]);
			opt->nbfile = ++files;
		}
		else
			perror(argv[i]);
		opt->errors++;
	}
	return (opt);
}

int				ft_check_cols(int tmp)
{
	int i;

	i = 1;
	while (tmp > 9)
	{
		tmp /= 10;
		i++;
	}
	return (i);
}

t_options		*ft_order_by_date(t_options *opt)
{
	int				i;
	struct stat		bufstat1;
	struct stat		bufstat2;
	char			*tmp;

	i = 0;
	while (++i < opt->nbfile)
	{
		lstat(opt->files[i - 1], &bufstat1);
		lstat(opt->files[i], &bufstat2);
		if (bufstat1.st_mtime < bufstat2.st_mtime)
		{
			tmp = ft_strdup(opt->files[i]);
			opt->files[i] = opt->files[i - 1];
			opt->files[i - 1] = ft_strdup(tmp);
			i = 0;
		}
	}
	return (opt);
}

t_options		*ft_order_reverse(t_options *opt)
{
	int				i;
	char			*tmp;

	i = -1;
	while (++i < opt->nbfile / 2)
	{
		tmp = opt->files[i];
		opt->files[i] = opt->files[opt->nbfile - 1 - i];
		opt->files[opt->nbfile - 1 - i] = tmp;
	}
	return (opt);
}

void			ft_print_rights(t_lstdir *lst, t_options *opt)
{
	mode_t val;

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
	if (val & S_ISUID)
		ft_putchar('s');
	else
		(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if (val & S_ISGID)
		ft_putchar('s');
	else
		(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	ft_print_acl(lst, opt);
}
