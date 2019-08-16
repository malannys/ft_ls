#include "ft_ls.h"

int		main(int ac, char **av)
{
	int		options;
	int		i;

	options = 0;
	i = opt_parser(ac, av, &options);
	if (i == ac)
		ft_ls(".", options);
	else
	{
		while (i < ac)
		{
			ft_ls(av[i++], options);
		}
	}
	return (0);
}