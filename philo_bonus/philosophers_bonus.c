#include "philosophers_bonus.h"

static int	ft_is_only_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_validation(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
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

int	main(int argc, char *argv[])
{
	t_common	*common;

	if (ft_validation(argc, argv))
	{
		printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
		printf("%snumber_of_philosophers time_to_die ", YELLOW);
		printf("time_to_eat time_to_sleep %s", END_COLOR);
		printf("%s[number_of_times_each_philosopher_must_eat]", BLUE);
		printf("%s\n", END_COLOR);
		return (0);
	}
	common = (t_common *)malloc(sizeof(t_common));
	if (common == NULL)
		return (1);
	if (ft_init_common(argc, argv, &common))
	{
		free(common);
		return (1);
	}
	ft_start(common);
	free(common);;
	return (0);
}
