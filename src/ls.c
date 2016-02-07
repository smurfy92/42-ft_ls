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

void	ft_ls_R(char *dir)
{
	DIR				*dirp;
	struct dirent	*buf;
	struct stat 	bufstat;
	char 			*tmp;

	if ((dir[1] && dir[1] !='.') || ft_strlen(dir) > 2)
	{
		ft_putchar('\n');
		ft_putendl(dir);
	}
	dirp = opendir(dir);
	if (!dirp)
		ft_error(dir, 0);
	while ((buf = readdir(dirp)))
	{
		if (stat(buf->d_name, &bufstat) == -1)
		{
			ft_error(buf->d_name, 0);
		}
		else
		{
			if (S_IFDIR & bufstat.st_mode && buf->d_name[0] != '.')
			{
				printf("%s is a directory\n", buf->d_name);
				tmp = ft_strjoin(dir, "/");
				tmp = ft_strjoin(tmp, buf->d_name);
				ft_ls_R(tmp);
			}
		}
	}
	closedir(dirp);
}

void	ft_print_dir(char *dir, t_options *opt)
{
	struct stat 	bufstat;

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
		ft_print_rights(bufstat);
		ft_print_links_usr_grp(bufstat);
		ft_print_size(bufstat);
		ft_print_time(ctime(&bufstat.st_mtime));
		ft_putendl(dir);
	}
	else
		ft_putendl(dir);
}

void	ft_process(char *dir, t_options *opt)
{
	t_lstdir *lst;

	if ((lst = ft_read_dir(dir)) != NULL)
	{
		if (opt->r)
			lst = ft_ls_r(lst);
		while (lst)
		{
			if (opt->l)
				ft_ls_l(lst, opt);
			else if(opt->R)
				ft_ls_R(lst->name);
			else
				if (!(!opt->a && lst->name[0] == '.'))
					ft_putendl(lst->name);
			lst = lst->next;
		}
	}
	else
		ft_print_dir(dir, opt);
}

int 	ft_is_dir(char *dir)
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
	int i;

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
