#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philos *philos;

	if (ft_validation(argc, argv))
	{
		printf("%sInvalid args:%s ", RED_BOLD, END_COLOR);
		printf("%snumber_of_philosophers time_to_die time_to_eat time_to_sleep %s", YELLOW, END_COLOR);
		printf("%s[number_of_times_each_philosopher_must_eat]%s\n", BLUE, END_COLOR);		
		return (0);
	}
	ft_init_philos(argc, argv, philos);
	ft_start(&philos);
	free(philos);
	return (0);
}