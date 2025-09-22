#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_rules rules;

	if (ft_validation(argc, argv))
	{
		printf("Invalid args:\n");
		printf("Use: number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat\n");

		
		return (0);
	}
	ft_init_rules(argc, argv, &rules);
	return (0);
}
