
#include "../includes/ft_ls.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int	main(int argc, char **argv)
{
	DIR				*dirp;
	struct dirent	*buf;

	dirp = opendir(argv[1]);
	if (!dirp)
		ft_putendl("error");
	while ((buf = readdir(dirp)))
		ft_putendl(buf->d_name);
}