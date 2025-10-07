#include "philosophers_bonus.h"

static int	ft_init_semaphores(t_common *common)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_BUTLER);
	common->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0644,
			common->number_of_philosophers);
	common->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	common->sem_butler = sem_open(SEM_BUTLER, O_CREAT, 0644,
			common->number_of_philosophers - 1);
	if (common->sem_forks == SEM_FAILED || common->sem_print == SEM_FAILED
		|| common->sem_butler == SEM_FAILED)
		return (1);
	return (0);
}

int	ft_init_common(int argc, char *argv[], t_common **common)
{
	(*common)->number_of_philosophers = ft_atoi(argv[1]);
	(*common)->time_to_die = ft_atoi(argv[2]);
	(*common)->time_to_eat = ft_atoi(argv[3]);
	(*common)->time_to_sleep = ft_atoi(argv[4]);
	(*common)->number_of_times_must_eat = -1;
	(*common)->start_time = ft_get_time_ms();
	if (argc == 6)
		(*common)->number_of_times_must_eat = ft_atoi(argv[5]);
	if ((*common)->number_of_philosophers < 1)
		return (1);
	if (ft_init_semaphores(*common))
		return (1);
	return (0);
}