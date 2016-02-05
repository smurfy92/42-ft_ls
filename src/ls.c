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

void	ft_ls_r(char *dir)
{
	DIR				*dirp;
	struct dirent	*buf;
	struct stat 	bufstat;
	mode_t 			val;
	char 			*tmp;

	if ((dir[1] && dir[1] !='.') || ft_strlen(dir) > 2)
	{
		ft_putchar('\n');
		ft_putendl(dir);
	}
	dirp = opendir(dir);
	if (!dirp)
		ft_error(dir);
	while ((buf = readdir(dirp)))
	{
		if (stat(buf->d_name, &bufstat) == -1)
		{
			perror("stat");
			ft_putstr("ls -r");
		}
		else
		{
			val=(bufstat.st_mode & ~S_IFMT);
			if (S_IFDIR & bufstat.st_mode && buf->d_name[0] != '.')
			{
				printf("%s is a directory\n", buf->d_name);
				tmp = ft_strjoin(dir, "/");
				tmp = ft_strjoin(tmp, buf->d_name);
				ft_ls_r(tmp);
			}
		}
	}
	closedir(dirp);
}

void	ft_print_dir(char *dir, t_options *opt)
{
	struct stat 	bufstat;

	if (!opt->a && dir[0] == '.')
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
		while (lst != NULL)
		{
			if (opt->l)
			{
				ft_ls_l(lst, opt);
			}
			else if(opt->R)
				ft_ls_r(lst->name);
			else
			{
				if (!(!opt->a && lst->name[0] == '.'))
					ft_putendl(lst->name);
			}
			lst = lst->next;
		}
	}
	else
		ft_print_dir(dir, opt);
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
			ft_process(opt->files[i], opt);
		}
	}
	return (0);
}
