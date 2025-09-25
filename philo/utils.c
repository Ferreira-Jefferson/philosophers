#include "philosophers.h"

int ft_validation(int argc, char *argv[])
{
	int i;

	if (argc == 1 || (argc < 5 || argc > 6))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!ft_is_only_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
