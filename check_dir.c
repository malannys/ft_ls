#include <dirent.h>
#include <stdio.h>
#include <errno.h>

#define ERROR 1

int		main(int ac, char **av)
{
	DIR	*dirp;
	struct dirent *dp;
	int	i;

	errno = 0;
	i = 0;
	if (ac < 2)
	{
		// print current directory "."
		if (!(dirp = opendir(".")))
		{
			perror(".");
			return (1);
		}
		while ((dp = readdir(dirp)))
		{
			// do sth
		}
		closedir(dirp);
		return (0);
	}
	while (++i < ac)
	{
		//create node for each
		//sort

		if (!(dirp = opendir(av[i])))
		{
			perror(av[i]);
			return (1);
		}
		while ((dp = readdir(dirp)))
		{
			// do sth
			printf("%s %llu %hhu %d\n", dp->d_name, dp->d_ino, dp->d_type, dp->d_reclen);
		}
		closedir(dirp);
	}
	return (0);
}
