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

int ft_init_mutex(t_common **common)
{
	int	i;
	int error;

	error = pthread_mutex_init(&(*common)->shutdown_mutex, NULL);
	if (error)
		return (1);
	error = pthread_mutex_init(&(*common)->printf_mutex, NULL);
	if (error)
		return (pthread_mutex_destroy(&(*common)->shutdown_mutex) + 1);
	i = 0;
	while (i < (*common)->number_of_philosophers)
	{
		error += pthread_mutex_init(&(*common)->forks_mutex[i], NULL);
		if (error)
			break ;
		i++;
	}
	if (error)
	{
		while (i--)
			pthread_mutex_destroy(&(*common)->forks_mutex[i]);
		pthread_mutex_destroy(&(*common)->shutdown_mutex);
		pthread_mutex_destroy(&(*common)->printf_mutex);	
	}
	return (error);
}

int ft_init_common(int argc, char *argv[], t_common **common)
{
	int error;

	*common = (t_common *) malloc(sizeof(t_common));
	if (*common == NULL)
		return (1);
	(*common)->number_of_philosophers = ft_atoi(argv[1]);
	(*common)->time_to_die = ft_atoi(argv[2]);
	(*common)->time_to_eat = ft_atoi(argv[3]);
	(*common)->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*common)->number_of_times_must_eat = ft_atoi(argv[5]);
	(*common)->shutdown = 0;
	(*common)->forks_mutex = (pthread_mutex_t *) malloc((*common)->number_of_philosophers * sizeof(pthread_mutex_t));
	if ((*common)->forks_mutex == NULL)
	{
		free(*common);
		return (1);
	}
	error = ft_init_mutex(common);
	if (error)
	{
		free((*common)->forks_mutex);
		free(*common);
	}
	return (error);
}
