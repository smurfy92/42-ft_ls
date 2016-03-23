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

	j = 0;
	if (argv[i][0] == '-' && opt->nbfile == 0 && !ft_is_dir(argv[i]))
	{
		(!argv[i][1]) ? ft_error(argv[i], 2) : 0;
		while (argv[i][++j])
			opt = ft_add_option(argv[i][j], opt);
	}
	else
	{
		if (lstat(argv[i], &bufstat) != -1)
			opt->files[opt->nbfile++] = ft_strdup(argv[i]);
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
		if (!(!S_ISDIR(bufstat1.st_mode) && S_ISDIR(bufstat2.st_mode)))
		{
			if (bufstat1.st_mtime < bufstat2.st_mtime)
			{
				tmp = ft_strdup(opt->files[i]);
				opt->files[i] = opt->files[i - 1];
				opt->files[i - 1] = ft_strdup(tmp);
				i = 0;
			}
		}
	}
	return (opt);
}

t_options		*ft_order_reverse(t_options *opt)
{
	int				i;
	char			*tmp;
	struct stat		bufstat1;
	struct stat		bufstat2;

	i = -1;
	while (++i < opt->nbfile / 2)
	{
		lstat(opt->files[i], &bufstat1);
		lstat(opt->files[i + 1], &bufstat2);
		if (S_ISDIR(bufstat1.st_mode) && S_ISDIR(bufstat2.st_mode))
		{
			tmp = opt->files[i];
			opt->files[i] = opt->files[opt->nbfile - 1 - i];
			opt->files[opt->nbfile - 1 - i] = tmp;
		}
	}
	return (opt);
}

void			ft_print_rights(t_lstdir *lst, t_options *opt)
{
	mode_t			val;
	char			*tmp;

	ft_print_rights_begin(lst);
	val = (lst->mode & ~S_IFMT);
	tmp = ft_strjoin(ft_strjoin(opt->tmp, "/"), lst->name);
	(val & S_IRUSR) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWUSR) ? ft_putchar('w') : ft_putchar('-');
	if (val & S_ISUID)
		(access(tmp, X_OK) == -1) ? ft_putchar('S') : ft_putchar('s');
	else
		(val & S_IXUSR) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IRGRP) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWGRP) ? ft_putchar('w') : ft_putchar('-');
	if (val & S_ISGID)
		(access(tmp, X_OK) == -1) ? ft_putchar('S') : ft_putchar('s');
	else
		(val & S_IXGRP) ? ft_putchar('x') : ft_putchar('-');
	(val & S_IROTH) ? ft_putchar('r') : ft_putchar('-');
	(val & S_IWOTH) ? ft_putchar('w') : ft_putchar('-');
	ft_print_acl(lst, opt);
}
