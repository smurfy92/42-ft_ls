/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/28 17:17:49 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/03 22:14:55 by jtranchi         ###   ########.fr       */
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

void	process(t_lstdir *lst)
{
	while (lst->next)
	{
		ft_ls_l(lst);
		lst = lst->next;
	}
}

void	ft_parse_options(int argc, char **argv)
{
	int i;
	int	files;

	i = 0;
	files = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' && files == 0)
		{
			files = 1;
			printf("file %s \n", argv[i]);
		}
		else if (argv[i][0] == '-' && files == 0)
		{
			int j = 0;
			while (argv[i][++j])
			{
				ft_putstr("options : ");
				ft_putchar(argv[i][j]);
				ft_putchar('\n');
			}
		}
		else
			printf("file %s \n", argv[i]);
	}
}

int		main(int argc, char **argv)
{
	t_lstdir *lst;

	if (argc == 1)
	{
		lst = ft_read_dir(".");
		process(lst);
	}
	else
		ft_parse_options(argc, argv);
	return (0);
}
