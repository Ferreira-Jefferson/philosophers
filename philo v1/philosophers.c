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
	ft_init_philos(argc, argv, &philos);
	ft_start(&philos);
	free(philos);
	return (0);
}

long ft_get_time_ms(const struct timeval *time)
{
	return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void *ft_monitoring(void *args) {
	t_philos *philos;

	philos = (t_philos *) args;
	int i = 0;
	struct timeval now;

	pthread_mutex_lock(&philos->action_mutex);
	usleep(500);
	i = 0;
	while (i < philos[0].number_of_philosophers)
	{	
		gettimeofday(&now, NULL);
		if (ft_get_time_ms(&now) > ft_get_time_ms(&philos[i].last_meal) + philos[i].time_to_die)
		{
			printf("%ld %d is died\n", ft_get_time_ms(&now), philos[i].id_philo);
			pthread_mutex_unlock(&philos->action_mutex);
			return ((void *) 1);
		}
		i++;
	}
	pthread_mutex_unlock(&philos->action_mutex);

	return (NULL);
}

void *ft_core(void *args)
{
	t_philos *philo;
	struct timeval now;

	philo = (t_philos *) args;
	pthread_mutex_t *forks;
	forks = philo->forks.vet;
	int i = 0;
	while (i < 10)
	{
		ft_monitoring(args);
		pthread_mutex_lock(&forks[philo->forks.left]);
		pthread_mutex_lock(&forks[philo->forks.right]);
			pthread_mutex_lock(&philo->action_mutex);
			gettimeofday(&now, NULL);
			philo->last_meal = now;
			printf("%ld %d has taken a fork\n", ft_get_time_ms(&now), philo->id_philo);
			printf("%ld %d is eating\n", ft_get_time_ms(&now), philo->id_philo);
			usleep(philo->time_to_eat * 1000);
			pthread_mutex_unlock(&philo->action_mutex);
		pthread_mutex_unlock(&forks[philo->forks.left]);
		pthread_mutex_unlock(&forks[philo->forks.right]);
	// 	pthread_mutex_lock(&philo->action_mutex);
	// 		gettimeofday(&now, NULL);
	// 		printf("%ld %d is sleeping\n", ft_get_time_ms(&now), philo->id_philo);
	// 		usleep(philo->time_to_sleep * 1000);
	// 	pthread_mutex_unlock(&philo->action_mutex);
	// 	pthread_mutex_lock(&philo->action_mutex);
	// 		gettimeofday(&now, NULL);
	// 		printf("%ld %d is thinking\n", ft_get_time_ms(&now), philo->id_philo);
	// 	pthread_mutex_unlock(&philo->action_mutex);
		i++;
	}
	return (NULL);
}

int	ft_start(t_philos **philos)
{
	int i;
	int size = (*philos)[0].number_of_philosophers;
	pthread_t		thr_philos[size];
	pthread_mutex_t	forks[size];

	ft_init_forks(size, forks);
	ft_assign_forks(philos, forks);
	i = 0;
	while (i < size)
	{
		pthread_create(&thr_philos[i], NULL, &ft_core, &(*philos)[i]);
		i++;
	}
	ft_threads_join(size, thr_philos);	
	ft_destroy_forks(size, forks);
	return (0);
}
